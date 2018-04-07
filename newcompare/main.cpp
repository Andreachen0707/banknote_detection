#include <opencv2/opencv.hpp>
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

double mindistance(int rows,vector< DMatch > matches, double min_dist);
vector< DMatch > Matches(string moneyclass, string moneyregion, Mat descriptors_img);
int MatchNumber(int rows, vector< DMatch > matches,double min_dist, vector< DMatch > good_matches);

/*//检测器
SurfFeatureDetector detector(10.0);
//提取器
SurfDescriptorExtractor extractor;
//第一个以及第二个最近邻之间的最大比率
float ratio=0.65f;
//是否再次优化F矩阵
bool refineF=true;
//到极线的最小矩离
double distance=3.0;
//置信等级（概率）
double confidence=0.95;*/


int main( int argc, char** argv )
{

	//载入源图片利用SURF检测器检测的关键点，计算描述符
	Mat img = imread("E:\\ZJU\\SURF\\5.jpg", 1 );
	if( !img.data ) { printf("读取图片image错误~！ \n"); return false; }  
	int minHessian = 700;
	SURF detector( minHessian );
	vector<KeyPoint> keypoints_img;
	detector.detect( img, keypoints_img );
	SURF extractor;
	Mat descriptors_img;
	extractor.compute( img, keypoints_img, descriptors_img ); 

	Mat imgtest = imread("E:\\ZJU\\SURF\\2.jpg", 1 );
	if( !imgtest.data ) { printf("读取图片image错误~！ \n"); return false; }  
	int minHessian = 700;
	SURF detector( minHessian );
	vector<KeyPoint> keypoints;
	detector.detect( imgtest, keypoints );
	SURF extractor;
	Mat descriptors;
	extractor.compute( imgtest, keypoints, descriptors ); 
	
	BruteForceMatcher< L2<float> > matcher;
	std::vector< DMatch > matches1;
	std::vector< DMatch > matches2;
	matcher.knnMatch(descriptors, descriptors_img, matches1, 2);
	matcher.knnMatch(descriptors_img, descriptors, matches2, 2);
 
	ratioTest(matches1);
	ratioTest(matches2);
 
	symmetryTest(matches1, matches2, symMatches);


	system("pause");
	return 0;
}



vector< DMatch > Matches(string moneyclass, string moneyregion, Mat descriptors_img) 
{
	
	//载入类间参考区域的描述子
	string fileFolder_descriptions = "E:\\ZJU\\Grade 3Summer\\SURF\\txt\\descriptorsnew\\descriptors"+ moneyclass + "_" + moneyregion + ".xml";
	FileStorage fs_descriptors(fileFolder_descriptions, FileStorage::READ);
	Mat descriptors;
	FileNode descriptors_list = fs_descriptors["descriptors"+ moneyclass + "_" + moneyregion];read(descriptors_list, descriptors);

	/*string fileFolder_descriptions2 = "E:\\ZJU\\Grade 3Summer\\SURF\\txt\\descriptorsnew\\descriptors"+ moneyclass + "_" + moneyregion+"2" + ".xml";
	FileStorage fs_descriptors2(fileFolder_descriptions2, FileStorage::READ);
	Mat descriptors2;
	FileNode descriptors_list2 = fs_descriptors2["descriptors"+ moneyclass + "_" + moneyregion];read(descriptors_list2, descriptors2);*/

	/*string fileFolder_keypoints = "E:\\ZJU\\Grade 3Summer\\SURF\\txt\\keypointsnew\\keypoints"+ moneyclass + "_" + moneyregion + ".xml";
	FileStorage fs_keypoints(fileFolder_keypoints, FileStorage::READ);
	Mat keypoints;
	FileNode keypoints_list = fs_keypoints["keypoints"+ moneyclass + "_" + moneyregion];read(keypoints_list, keypoints);*/

	//采用FLANN算法匹配描述符向量
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors_img, descriptors, matches );

	return matches;
}



/*double mindistance(int rows, vector< DMatch > matches, double min_dist)
{
	//快速计算关键点之间的最大和最小距离
	for( int i = 0; i < rows; i++ )
	{
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		//cout<<min_dist<<endl;
	}
	return min_dist;
}

int MatchNumber(int rows, vector< DMatch > matches, double min_dist, vector< DMatch > good_matches)
{
	int num = 0;
	
		for( int i = 0; i < rows; i++ )
			{ 
				if( matches[i].distance < 2*min_dist )
					{ 
						good_matches.push_back( matches[i]);
				}
			}		
	return good_matches.size();
}*/



int ratioTest(vector<vector<DMatch>> &matches){
  float ratio = 0.8f;
  int removed=0;
  // for all matches
  for (std::vector<std::vector<DMatch>>::iterator matchIterator= matches.begin();matchIterator != matches.end(); ++matchIterator)
  {
	// if 2 NN has been identified
	if (matchIterator->size() > 1)
	{
	  // check distance ratio
	  if ((*matchIterator)[0].distance/(*matchIterator)[1].distance > ratio) {
		  matchIterator->clear(); // remove match
		  removed++;
	  }
	} else { // does not have 2 neighbours
	  matchIterator->clear(); // remove match
	  removed++;
	}
  }
  return removed;
}


void symmetryTest( const vector<vector<DMatch>> matches1,const vector<vector<DMatch>> matches2,vector<DMatch>& symMatches )
{
  // for all matches image 1 -> image 2
  for (std::vector<std::vector<DMatch>>::const_iterator matchIterator1= matches1.begin(); matchIterator1!= matches1.end(); ++matchIterator1)
  {
	// ignore deleted matches
	if (matchIterator1->size() < 2)
	  continue;
 
	// for all matches image 2 -> image 1
	for (std::vector<std::vector<DMatch>>::const_iterator matchIterator2= matches2.begin();
	  matchIterator2!= matches2.end();
	  ++matchIterator2)
	{
	  // ignore deleted matches
	  if (matchIterator2->size() < 2)
		continue;
	  // Match symmetry test
	  if ((*matchIterator1)[0].queryIdx ==(*matchIterator2)[0].trainIdx &&(*matchIterator2)[0].queryIdx ==(*matchIterator1)[0].trainIdx)
		{
		 // add symmetrical match
		 symMatches.push_back(
		   cv::DMatch((*matchIterator1)[0].queryIdx,
		   (*matchIterator1)[0].trainIdx,
		   (*matchIterator1)[0].distance));
		 break; // next match in image 1 -> image 2
	  }
	}
  }
}
