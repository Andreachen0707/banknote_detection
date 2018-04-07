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

/*********************��������*************************/
//�����
SurfFeatureDetector detector(10.0);
//��ȡ��
SurfDescriptorExtractor extractor;
//��һ���Լ��ڶ��������֮���������
float ratio=1.0f;
//�Ƿ��ٴ��Ż�F����
bool refineF=true;
//�����ߵ���С����
double distance=3.0;
//���ŵȼ������ʣ�
double confidence=0.99;



/**********************************************************************
* ������:ratioTest
* ��  ��:matches
* ��  ��:�Ƴ���ƥ������
* ˵  ��:�Ե�ǰƥ�����ɸѡ������ƥ��ʹ���ƥ����Ӧǿ�ȴ���ratio��ƥ���Լ�
*  ������ƥ�䡣
***********************************************************************/
int ratioTest(std::vector<std::vector<cv::DMatch>>& matches)
{
        int removed = 0;
        std::vector<std::vector<cv::DMatch>>::iterator matchIt = matches.begin();
        for (; matchIt != matches.end();matchIt++)
        {
                if (matchIt->size()  > 1)
                {
                        //�Ƴ����ϸ���ʵ�ƥ�䣨������������
                        if ((*matchIt)[0].distance / (*matchIt)[1].distance > ratio)
                        {
                                matchIt->clear();
                                removed++;
                        }
                }
                else
                {
                        //�Ƴ�������ƥ��
                        matchIt->clear();
                        removed++;
                }
        }
        return removed;
}
/**********************************************************************
* ������:symmetryTest
* ��  ��:matches1:��ƥ��
*       matches2:��ƥ��
*       symMatche:����ĶԳ�ƥ��
* ��  ��:��
* ˵  ��:������ƥ����м�飬����ԳƵ�ƥ�䡣
***********************************************************************/
void symmetryTest(std::vector<std::vector<cv::DMatch>>& matches1,
        std::vector<std::vector<cv::DMatch>>& matches2, std::vector<cv::DMatch>& symMatches)
{
        //������ƥ��
        for (auto &leftMatchRef : matches1)
        {
                if (leftMatchRef.size() < 2)
                        continue;
                //������ƥ��
                for (auto &rightMatchRef : matches2)
                {
                        if (rightMatchRef.size() < 2)
                                continue;
                        //�Գ��Բ���
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
* ������:ransacTest
* ��  ��:matches:��ǰƥ�䣨���룩
*       keypoints1:ͼ��1��⵽�Ĺؼ��㣨���룩
*       keypoints2:ͼ��2��⵽�Ĺؼ��㣨���룩
*       outMatches:��ɲ��Ե�ƥ�䣨�����
* ��  ��:��������
* ˵  ��:�Ե�ǰƥ�����RANSAC���ԣ������������ͬʱ����ͨ�����Ե�ƥ��
***********************************************************************/
cv::Mat ransacTest(
        const std::vector<cv::DMatch>& matches, const std::vector<cv::KeyPoint>& keypoints1,
        const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches)
{
        //��Keypointsת����Point2f
        std::vector<cv::Point2f>points1, points2;
        for (auto &matchesRef : matches)
        {
                //��ͼ��ؼ���
                float x = keypoints1[matchesRef.queryIdx].pt.x;
                float y = keypoints1[matchesRef.queryIdx].pt.y;
                points1.push_back(cv::Point2f(x, y));
                //��ͼ��ؼ���
                x = keypoints2[matchesRef.trainIdx].pt.x;
                y = keypoints2[matchesRef.trainIdx].pt.y;
                points2.push_back(cv::Point2f(x, y));
        }
        //����RANSAC����F����
        std::vector<uchar>inlines(points1.size(), 0);
        cv::Mat fundemental = cv::findFundamentalMat(
                cv::Mat(points1),
                cv::Mat(points2),
                inlines,
                CV_FM_RANSAC,
                3.0,
                confidence
                );
        //��ȡͨ����ƥ��
        std::vector<uchar>::const_iterator itIn = inlines.begin();
        std::vector<cv::DMatch>::const_iterator itM = matches.begin();
        for (; itIn != inlines.end(); itIn++, itM++)
        {
                if (*itIn)
                {
                        outMatches.push_back(*itM);
                }
        }
        //�������
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
* ������:match
* ��  ��:image1 :ͼ��1�����룩
*        image2:ͼ��2�����룩
*        matches:�������ز���ʣ�µĸ�������ƥ�䣨�����
*        keypoints1:���ڱ���ͼ��1��⵽�Ĺؼ��㣨�����
*        keypoints2:���ڱ���ͼ��2��⵽�Ĺؼ��㣨�����
* ��  ��:��������
* ˵  ��:�����������ͼ�����������⡢���������ӣ�����ʹ��BruteForceMatcher
* ����ƥ�䣬�Գ�ʼ�õ���ƥ���ϵ�����ν��б��ʲ��ԡ��ԳƲ���������Ransac
* ��֤�����õ���������Ļ�������
***********************************************************************/
cv::Mat match(cv::Mat &image1, cv::Mat &image2, std::vector<cv::DMatch>&matches,
        std::vector<cv::KeyPoint>&keypoints1, std::vector<cv::KeyPoint>&keypoints2)
{
        //1.a ���SURF����
        detector.detect(image1, keypoints1);
        detector.detect(image2, keypoints2);
        //1.b ����SURF������
        cv::Mat descriptors1, descriptors2;
        extractor.compute(image1, keypoints1, descriptors1);
        extractor.compute(image2, keypoints2, descriptors2);
        //2 ƥ������ͼ���������
        //2.a����ƥ����
        cv::BruteForceMatcher<cv::L2<float>>matcher;
        //2.b����ͼ1->ͼ2��ͼ2->ͼ1 ��k����ڣ�k=2��
        std::vector<std::vector<cv::DMatch>>matcher1;
        std::vector<std::vector<cv::DMatch>>matcher2;
        //���������knnMatch
        matcher.knnMatch(descriptors1, descriptors2, matcher1, 2);
        matcher.knnMatch(descriptors2, descriptors1, matcher2, 2);

        //3.���ʲ���
        int removed = ratioTest(matcher1);
        removed = ratioTest(matcher2);
        //4.�Գ��Բ���
        std::vector<cv::DMatch>symMatches;
        symmetryTest(matcher1, matcher2, symMatches);
        //5.RANSAC������֤
        cv::Mat fundemental = ransacTest(symMatches, keypoints1, keypoints2, matches);
        return fundemental;
}

int main(int argc, char** argv)
{
        //1.��ȡͼ��
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
        //2.���
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
        //3.����Ч��ͼ
        Mat imgMatch;
        drawMatches(image1, keypoints1, image, keypoints, matches1, imgMatch);
        imshow("Ч��ͼ", imgMatch);
		waitKey(0);
		system("pause");
        
        return 0;
}
