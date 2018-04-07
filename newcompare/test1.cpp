// RobustMatch.cpp : Defines the entry point for the console application.
//
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\legacy\legacy.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*********************公共变量*************************/
//检测器
SurfFeatureDetector detector(10.0);
//提取器
SurfDescriptorExtractor extractor;
//第一个以及第二个最近邻之间的最大比率
float ratio=1.0f;
//是否再次优化F矩阵
bool refineF=true;
//到极线的最小矩离
double distance=3.0;
//置信等级（概率）
double confidence=0.99;



/**********************************************************************
* 函数名:ratioTest
* 参  数:matches
* 返  回:移除的匹配数量
* 说  明:对当前匹配进行筛选，最优匹配和次优匹配响应强度大于ratio的匹配以及
*  孤立的匹配。
***********************************************************************/
int ratioTest(std::vector<std::vector<cv::DMatch>>& matches)
{
        int removed = 0;
        std::vector<std::vector<cv::DMatch>>::iterator matchIt = matches.begin();
        for (; matchIt != matches.end();matchIt++)
        {
                if (matchIt->size()  > 1)
                {
                        //移除不合格比率的匹配（问题出现在这里）
                        if ((*matchIt)[0].distance / (*matchIt)[1].distance > ratio)
                        {
                                matchIt->clear();
                                removed++;
                        }
                }
                else
                {
                        //移除孤立的匹配
                        matchIt->clear();
                        removed++;
                }
        }
        return removed;
}
/**********************************************************************
* 函数名:symmetryTest
* 参  数:matches1:左匹配
*       matches2:右匹配
*       symMatche:输出的对称匹配
* 返  回:无
* 说  明:对左、右匹配进行检查，输出对称的匹配。
***********************************************************************/
void symmetryTest(std::vector<std::vector<cv::DMatch>>& matches1,
        std::vector<std::vector<cv::DMatch>>& matches2, std::vector<cv::DMatch>& symMatches)
{
        //遍历左匹配
        for (auto &leftMatchRef : matches1)
        {
                if (leftMatchRef.size() < 2)
                        continue;
                //遍历右匹配
                for (auto &rightMatchRef : matches2)
                {
                        if (rightMatchRef.size() < 2)
                                continue;
                        //对称性测试
                        if ((leftMatchRef[0].queryIdx == rightMatchRef[0].trainIdx) &&
                                (leftMatchRef[0].trainIdx == rightMatchRef[0].queryIdx))
                        {
                                symMatches.push_back(cv::DMatch(leftMatchRef[0].queryIdx, leftMatchRef[0].trainIdx,
                                        leftMatchRef[0].distance));
                                break;
                        }
                }
        }
}

/**********************************************************************
* 函数名:ransacTest
* 参  数:matches:当前匹配（输入）
*       keypoints1:图像1检测到的关键点（输入）
*       keypoints2:图像2检测到的关键点（输入）
*       outMatches:完成测试的匹配（输出）
* 返  回:基础矩阵
* 说  明:对当前匹配进行RANSAC测试，计算基础矩阵，同时返回通过测试的匹配
***********************************************************************/
cv::Mat ransacTest(
        const std::vector<cv::DMatch>& matches, const std::vector<cv::KeyPoint>& keypoints1,
        const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches)
{
        //将Keypoints转换到Point2f
        std::vector<cv::Point2f>points1, points2;
        for (auto &matchesRef : matches)
        {
                //左图像关键点
                float x = keypoints1[matchesRef.queryIdx].pt.x;
                float y = keypoints1[matchesRef.queryIdx].pt.y;
                points1.push_back(cv::Point2f(x, y));
                //右图像关键点
                x = keypoints2[matchesRef.trainIdx].pt.x;
                y = keypoints2[matchesRef.trainIdx].pt.y;
                points2.push_back(cv::Point2f(x, y));
        }
        //基于RANSAC计算F矩阵
        std::vector<uchar>inlines(points1.size(), 0);
        cv::Mat fundemental = cv::findFundamentalMat(
                cv::Mat(points1),
                cv::Mat(points2),
                inlines,
                CV_FM_RANSAC,
                3.0,
                confidence
                );
        //提取通过的匹配
        std::vector<uchar>::const_iterator itIn = inlines.begin();
        std::vector<cv::DMatch>::const_iterator itM = matches.begin();
        for (; itIn != inlines.end(); itIn++, itM++)
        {
                if (*itIn)
                {
                        outMatches.push_back(*itM);
                }
        }
        //二次拟合
        if (refineF)
        {
                points1.clear();
                points2.clear();
                for (auto &matchRef : outMatches)
                {
                        float x = keypoints1[matchRef.queryIdx].pt.x;
                        float y = keypoints1[matchRef.queryIdx].pt.y;
                        points1.push_back(cv::Point2f(x, y));

                        x = keypoints2[matchRef.trainIdx].pt.x;
                        y = keypoints2[matchRef.trainIdx].pt.y;
                        points2.push_back(cv::Point2f(x, y));
                }
                fundemental = cv::findFundamentalMat(
                        cv::Mat(points1),
                        cv::Mat(points2),
                        CV_FM_8POINT
                        );
        }
        return fundemental;
}
/**********************************************************************
* 函数名:match
* 参  数:image1 :图像1（输入）
*        image2:图像2（输入）
*        matches:经过多重测试剩下的高质量的匹配（输出）
*        keypoints1:用于保存图像1检测到的关键点（输出）
*        keypoints2:用于保存图像2检测到的关键点（输出）
* 返  回:基础矩阵
* 说  明:对输出的两幅图像进行特征检测、计算描述子，进而使用BruteForceMatcher
* 进行匹配，对初始得到的匹配关系再依次进行比率测试、对称测试最后进行Ransac
* 验证，并得到两个相机的基础矩阵。
***********************************************************************/
cv::Mat match(cv::Mat &image1, cv::Mat &image2, std::vector<cv::DMatch>&matches,
        std::vector<cv::KeyPoint>&keypoints1, std::vector<cv::KeyPoint>&keypoints2)
{
        //1.a 检测SURF特征
        detector.detect(image1, keypoints1);
        detector.detect(image2, keypoints2);
        //1.b 计算SURF描述子
        cv::Mat descriptors1, descriptors2;
        extractor.compute(image1, keypoints1, descriptors1);
        extractor.compute(image2, keypoints2, descriptors2);
        //2 匹配两幅图像的描述子
        //2.a创建匹配器
        cv::BruteForceMatcher<cv::L2<float>>matcher;
        //2.b计算图1->图2，图2->图1 的k最近邻（k=2）
        std::vector<std::vector<cv::DMatch>>matcher1;
        std::vector<std::vector<cv::DMatch>>matcher2;
        //这里调用了knnMatch
        matcher.knnMatch(descriptors1, descriptors2, matcher1, 2);
        matcher.knnMatch(descriptors2, descriptors1, matcher2, 2);

        //3.比率测试
        int removed = ratioTest(matcher1);
        removed = ratioTest(matcher2);
        //4.对称性测试
        std::vector<cv::DMatch>symMatches;
        symmetryTest(matcher1, matcher2, symMatches);
        //5.RANSAC最终验证
        cv::Mat fundemental = ransacTest(symMatches, keypoints1, keypoints2, matches);
        return fundemental;
}

int main(int argc, char** argv)
{
        //1.读取图像
        Mat image1 = imread("E:\\ZJU\\SURF\\standard\\100(01).jpg", 0);
		/*Mat image2 = imread("E:\\ZJU\\SURF\\standard\\50(01).jpg", 0);
		Mat image3 = imread("E:\\ZJU\\SURF\\standard\\20(01).jpg", 0);
		Mat image4 = imread("E:\\ZJU\\SURF\\standard\\10(01).jpg", 0);
		Mat image5 = imread("E:\\ZJU\\SURF\\standard\\5(01).jpg", 0);
		Mat image6 = imread("E:\\ZJU\\SURF\\standard\\1(01).jpg", 0);*/
        //Mat image2 = imread("E:\\ZJU\\SURF\\data\\50\\50.5.jpg", 0);
		Mat image = imread("E:\\ZJU\\SURF\\data\\100\\100.32.jpg", 0);
        /*if (!image1.data || !image2.data)
        {
                return 1;
        }*/
        //2.检测
        vector<DMatch> matches1;
        vector<KeyPoint> keypoints1, keypoints;
        match(image1, image, matches1, keypoints1, keypoints);

		/*vector<DMatch> matches2;
        vector<KeyPoint> keypoints2;
        match(image2, image, matches2, keypoints2, keypoints);
		
		vector<DMatch> matches3;
        vector<KeyPoint> keypoints3;
        match(image3, image, matches3, keypoints3, keypoints);

		vector<DMatch> matches4;
        vector<KeyPoint> keypoints4;
        match(image4, image, matches4, keypoints4, keypoints);

		vector<DMatch> matches5;
        vector<KeyPoint> keypoints5;
        match(image5, image, matches5, keypoints5, keypoints);

		vector<DMatch> matches6;
        vector<KeyPoint> keypoints6;
        match(image6, image, matches6, keypoints6, keypoints);*/



		cout<<"100 = "<<matches1.size()<<endl;
		/*cout<<"50 = "<<matches2.size()<<endl;
		cout<<"20 = "<<matches3.size()<<endl;
		cout<<"10 = "<<matches4.size()<<endl;
		cout<<"5 = "<<matches5.size()<<endl;
		cout<<"1 = "<<matches6.size()<<endl;*/
        //3.绘制效果图
        Mat imgMatch;
        drawMatches(image1, keypoints1, image, keypoints, matches1, imgMatch);
        imshow("效果图", imgMatch);
		waitKey(0);
		system("pause");
        
        return 0;
}
