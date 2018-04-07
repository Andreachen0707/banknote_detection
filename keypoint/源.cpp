#include <opencv2/opencv.hpp>
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{ 

	//【1】载入源图片并显示
	Mat srcImage1 = imread("E:\\ZJU\\Grade 3Summer\\SURF\\pic2\\region\\50\\1.jpg", 1 );
	Mat srcImage2 = imread("E:\\ZJU\\SURF\\1.jpg", 1 );
	if( !srcImage1.data || !srcImage2.data )//检测是否读取成功
	{ printf("读取图片错误，请确定目录下是否有imread函数指定名称的图片存在~！ \n"); return false; } 
	//imshow("原始图1",srcImage1);
	//imshow("原始图2",srcImage2);

	//【2】使用SURF算子检测关键点
	int minHessian = 700;//SURF算法中的hessian阈值
	SurfFeatureDetector detector( minHessian );//定义一个SurfFeatureDetector（SURF） 特征检测类对象  
	std::vector<KeyPoint> keyPoint1, keyPoints2;//vector模板类，存放任意类型的动态数组

	//【3】调用detect函数检测出SURF特征关键点，保存在vector容器中
	detector.detect( srcImage1, keyPoint1 );
	detector.detect( srcImage2, keyPoints2 );

	//【4】计算描述符（特征向量）
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute( srcImage1, keyPoint1, descriptors1 );
	extractor.compute( srcImage2, keyPoints2, descriptors2 );

	//【5】使用BruteForce进行匹配
	// 实例化一个匹配器
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors1, descriptors2, matches );

	//【6】绘制从两个图像中匹配出的关键点
	Mat imgMatches;
	drawMatches( srcImage1, keyPoint1, srcImage2, keyPoints2, matches, imgMatches );//进行绘制

	//【7】显示效果图
	imshow("匹配图", imgMatches );

	waitKey(0);
	return 0;
}
