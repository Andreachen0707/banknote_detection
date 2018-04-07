#include <opencv2/opencv.hpp>
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{ 

	//��1������ԴͼƬ����ʾ
	Mat srcImage1 = imread("E:\\ZJU\\Grade 3Summer\\SURF\\pic2\\region\\50\\1.jpg", 1 );
	Mat srcImage2 = imread("E:\\ZJU\\SURF\\1.jpg", 1 );
	if( !srcImage1.data || !srcImage2.data )//����Ƿ��ȡ�ɹ�
	{ printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ�����Ƶ�ͼƬ����~�� \n"); return false; } 
	//imshow("ԭʼͼ1",srcImage1);
	//imshow("ԭʼͼ2",srcImage2);

	//��2��ʹ��SURF���Ӽ��ؼ���
	int minHessian = 700;//SURF�㷨�е�hessian��ֵ
	SurfFeatureDetector detector( minHessian );//����һ��SurfFeatureDetector��SURF�� ������������  
	std::vector<KeyPoint> keyPoint1, keyPoints2;//vectorģ���࣬����������͵Ķ�̬����

	//��3������detect��������SURF�����ؼ��㣬������vector������
	detector.detect( srcImage1, keyPoint1 );
	detector.detect( srcImage2, keyPoints2 );

	//��4������������������������
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute( srcImage1, keyPoint1, descriptors1 );
	extractor.compute( srcImage2, keyPoints2, descriptors2 );

	//��5��ʹ��BruteForce����ƥ��
	// ʵ����һ��ƥ����
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors1, descriptors2, matches );

	//��6�����ƴ�����ͼ����ƥ����Ĺؼ���
	Mat imgMatches;
	drawMatches( srcImage1, keyPoint1, srcImage2, keyPoints2, matches, imgMatches );//���л���

	//��7����ʾЧ��ͼ
	imshow("ƥ��ͼ", imgMatches );

	waitKey(0);
	return 0;
}
