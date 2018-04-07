#include <opencv2/opencv.hpp>
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace cv;
using namespace std;

double mindistance(int rows,vector< DMatch > matches, double min_dist);
vector< DMatch > goodmatches(int rows, vector< DMatch > matches, double min_dist, vector< DMatch > good_matches);
int ReadXML(string moneyclass, string moneyregion, Mat descriptors_img, double min_dist);

int main( int argc, char** argv )
{

	//载入源图片利用SURF检测器检测的关键点，计算描述符
	Mat img = imread("C:\\Users\\zyvanilla\\Desktop\\SURF\\pic2\\test\\1.1.jpg", 1 );
	if( !img.data ) { printf("读取图片image错误~！ \n"); return false; }  
	int minHessian = 700;
	SURF detector( minHessian );
	vector<KeyPoint> keypoints_img;
	detector.detect( img, keypoints_img );
	SURF extractor;
	Mat descriptors_img;
	extractor.compute( img, keypoints_img, descriptors_img );

	double min_dist = 100;
	int money1_1 = ReadXML("1","1", descriptors_img,min_dist);
	int money1_2 = ReadXML("1","2", descriptors_img,min_dist);
	int money1_3 = ReadXML("1","3", descriptors_img,min_dist);
	int money1_4 = ReadXML("1","4", descriptors_img,min_dist);
	int money1_5 = ReadXML("1","5", descriptors_img,min_dist);
	int money1_6 = ReadXML("1","6", descriptors_img,min_dist);
	int money1_7 = ReadXML("1","7", descriptors_img,min_dist);
	int money5_1 = ReadXML("5","1", descriptors_img,min_dist);
	int money5_2 = ReadXML("5","2", descriptors_img,min_dist);
	int money5_3 = ReadXML("5","3", descriptors_img,min_dist);
	int money5_4 = ReadXML("5","4", descriptors_img,min_dist);
	int money5_5 = ReadXML("5","5", descriptors_img,min_dist);
	int money5_6 = ReadXML("5","6", descriptors_img,min_dist);
	int money5_7 = ReadXML("5","7", descriptors_img,min_dist);
	int money10_1 = ReadXML("10","1", descriptors_img,min_dist);
	int money10_2 = ReadXML("10","2", descriptors_img,min_dist);
	int money10_3 = ReadXML("10","3", descriptors_img,min_dist);
	int money10_4 = ReadXML("10","4", descriptors_img,min_dist);
	int money10_5 = ReadXML("10","5", descriptors_img,min_dist);
	int money10_6 = ReadXML("10","6", descriptors_img,min_dist);
	int money10_7 = ReadXML("10","7", descriptors_img,min_dist);
	int money20_1 = ReadXML("20","1", descriptors_img,min_dist);
	int money20_2 = ReadXML("20","2", descriptors_img,min_dist);
	int money20_3 = ReadXML("20","3", descriptors_img,min_dist);
	int money20_4 = ReadXML("20","4", descriptors_img,min_dist);
	int money20_5 = ReadXML("20","5", descriptors_img,min_dist);
	int money20_6 = ReadXML("20","6", descriptors_img,min_dist);
	int money20_7 = ReadXML("20","7", descriptors_img,min_dist);
	int money50_1 = ReadXML("50","1", descriptors_img,min_dist);
	int money50_2 = ReadXML("50","2", descriptors_img,min_dist);
	int money50_3 = ReadXML("50","3", descriptors_img,min_dist);
	int money50_4 = ReadXML("50","4", descriptors_img,min_dist);
	int money50_5 = ReadXML("50","5", descriptors_img,min_dist);
	int money50_6 = ReadXML("50","6", descriptors_img,min_dist);
	int money50_7 = ReadXML("50","7", descriptors_img,min_dist);
	int money50_8 = ReadXML("50","8", descriptors_img,min_dist);
	int money100_1 = ReadXML("100","1", descriptors_img,min_dist);
	int money100_2 = ReadXML("100","2", descriptors_img,min_dist);
	int money100_3 = ReadXML("100","3", descriptors_img,min_dist);
	int money100_4 = ReadXML("100","4", descriptors_img,min_dist);
	int money100_5 = ReadXML("100","5", descriptors_img,min_dist);
	int money100_6 = ReadXML("100","6", descriptors_img,min_dist);
	int money100_7 = ReadXML("100","7", descriptors_img,min_dist);
	int money100old_1 = ReadXML("100old","1", descriptors_img,min_dist);
	int money100old_2 = ReadXML("100old","2", descriptors_img,min_dist);
	int money100old_3 = ReadXML("100old","3", descriptors_img,min_dist);
	int money100old_4 = ReadXML("100old","4", descriptors_img,min_dist);
	int money100old_5 = ReadXML("100old","5", descriptors_img,min_dist);
	int money100old_6 = ReadXML("100old","6", descriptors_img,min_dist);
	int money100old_7 = ReadXML("100old","7", descriptors_img,min_dist);
	int money100old_8 = ReadXML("100old","8", descriptors_img,min_dist);
	cout<<money1_1<<endl;cout<<money1_2<<endl;cout<<money1_3<<endl;
	cout<<money1_4<<endl;cout<<money1_5<<endl;cout<<money1_6<<endl;
	cout<<money1_7<<endl;cout<<money5_1<<endl;cout<<money5_2<<endl;
	cout<<money5_3<<endl;cout<<money5_4<<endl;cout<<money5_5<<endl;
	cout<<money5_6<<endl;cout<<money5_7<<endl;cout<<money10_1<<endl;
	cout<<money10_2<<endl;cout<<money10_3<<endl;cout<<money10_4<<endl;
	cout<<money10_5<<endl;cout<<money10_6<<endl;cout<<money10_7<<endl;
	cout<<money20_1<<endl;cout<<money20_2<<endl;cout<<money20_3<<endl;
	cout<<money20_4<<endl;cout<<money20_5<<endl;cout<<money20_6<<endl;
	cout<<money20_7<<endl;cout<<money50_1<<endl;cout<<money50_2<<endl;
	cout<<money50_3<<endl;cout<<money50_4<<endl;cout<<money50_5<<endl;
	cout<<money50_6<<endl;cout<<money50_7<<endl;cout<<money50_8<<endl;
	cout<<money100_1<<endl;cout<<money100_2<<endl;cout<<money100_3<<endl;
	cout<<money100_4<<endl;cout<<money100_5<<endl;cout<<money100_6<<endl;
	cout<<money100_7<<endl;cout<<money100old_1<<endl;cout<<money100old_2<<endl;
	cout<<money100old_3<<endl;cout<<money100old_4<<endl;cout<<money100old_5<<endl;
	cout<<money100old_6<<endl;cout<<money100old_7<<endl;cout<<money100old_8<<endl;
	waitKey();
	return 0;
}

double mindistance(int rows, vector< DMatch > matches, double min_dist)
{
	//快速计算关键点之间的最大和最小距离
	for( int i = 0; i < rows; i++ )
	{
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
	}
	return min_dist;
}

vector< DMatch > goodmatches(int rows, vector< DMatch > matches, double min_dist, vector< DMatch > good_matches)
{
	for( int i = 0; i < rows; i++ )
	{ 
		if( matches[i].distance < 2*min_dist )
		{ good_matches.push_back( matches[i]); }
	}
	return good_matches;
}

int ReadXML(string moneyclass, string moneyregion, Mat descriptors_img, double min_dist) 
{
	//载入类间参考区域的关键点
	string fileFolderPath = "C:\\Users\\zyvanilla\\Desktop\\SURF\\txt\\";  
    string fileExtension = ".xml";
    string fileFolder_keypoints = fileFolderPath + "keypoints\\keypoints"+ moneyclass + "_" + moneyregion + fileExtension;
	FileStorage fs_keypoints(fileFolder_keypoints, FileStorage::READ);
	vector<KeyPoint> keypoints;
	FileNode keypoints_list = fs_keypoints["keypoints"+ moneyclass + "_" + moneyregion ];read(keypoints_list, keypoints);
	
	//载入类间参考区域的描述子
	string fileFolder_descriptions = fileFolderPath + "descriptors\\descriptors"+ moneyclass + "_" + moneyregion + fileExtension;
	FileStorage fs_descriptors(fileFolder_descriptions, FileStorage::READ);
	Mat descriptors;
	FileNode descriptors_list = fs_descriptors["descriptors"+ moneyclass + "_" + moneyregion];read(descriptors_list, descriptors);

	//采用FLANN算法匹配描述符向量
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors, descriptors_img, matches );

	//快速计算关键点之间的最小距离
	min_dist = mindistance(descriptors.rows, matches, min_dist);

	//存下符合条件的匹配结果（即其距离小于2* min_dist的），使用radiusMatch同样可行
	vector< DMatch > good_matches;
	good_matches = goodmatches(descriptors.rows, matches, min_dist, good_matches);

	return good_matches.size();
}