#include <opencv2/opencv.hpp>
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/legacy/legacy.hpp>
#include <iostream>


using namespace cv;
using namespace std;

double mindistance(int rows,vector< DMatch > matches, double min_dist);
vector< DMatch > Matches(string moneyclass, string moneyregion, Mat descriptors_img);
int MatchNumber(int rows, vector< DMatch > matches,double min_dist, vector< DMatch > good_matches);

int main( int argc, char** argv )
{

	//载入小分辨率的图片利用SURF检测器检测的关键点，计算描述符
	Mat img = imread("E:\\ZJU\\template\\1\\region7\\5.jpg", 1 );
	if( !img.data ) { printf("读取图片image错误~！ \n"); return false; }  
	int minHessian = 300;
	SURF detector( minHessian );
	vector<KeyPoint> keypoints_img;
	detector.detect( img, keypoints_img );
	SURF extractor;
	Mat descriptors_img;
	extractor.compute( img, keypoints_img, descriptors_img ); 
	/*vector< DMatch > matches1_1 = Matches("1","1", descriptors_img);
	vector< DMatch > matches1_2 = Matches("1","2", descriptors_img);
	vector< DMatch > matches1_3 = Matches("1","3", descriptors_img);
	vector< DMatch > matches1_4 = Matches("1","4", descriptors_img);
	vector< DMatch > matches1_5 = Matches("1","5", descriptors_img);
	vector< DMatch > matches1_6 = Matches("1","6", descriptors_img);
	vector< DMatch > matches1_7 = Matches("1","7", descriptors_img);*/
	/*vector< DMatch > matches5_1 = Matches("5","1", descriptors_img);
	vector< DMatch > matches5_2 = Matches("5","2", descriptors_img);
	vector< DMatch > matches5_3 = Matches("5","3", descriptors_img);
	vector< DMatch > matches5_4 = Matches("5","4", descriptors_img);
	vector< DMatch > matches5_5 = Matches("5","5", descriptors_img);
	vector< DMatch > matches5_6 = Matches("5","6", descriptors_img);
	vector< DMatch > matches5_7 = Matches("5","7", descriptors_img);*/
	/*vector< DMatch > matches10_1 = Matches("10","1", descriptors_img);
	vector< DMatch > matches10_2 = Matches("10","2", descriptors_img);
	vector< DMatch > matches10_3 = Matches("10","3", descriptors_img);
	vector< DMatch > matches10_4 = Matches("10","4", descriptors_img);
	vector< DMatch > matches10_5 = Matches("10","5", descriptors_img);
	vector< DMatch > matches10_6 = Matches("10","6", descriptors_img);
	vector< DMatch > matches10_7 = Matches("10","7", descriptors_img);*/
	/*vector< DMatch > matches20_1 = Matches("20","1", descriptors_img);
	vector< DMatch > matches20_2 = Matches("20","2", descriptors_img);
	vector< DMatch > matches20_3 = Matches("20","3", descriptors_img);
	vector< DMatch > matches20_4 = Matches("20","4", descriptors_img);
	vector< DMatch > matches20_5 = Matches("20","5", descriptors_img);
	vector< DMatch > matches20_6 = Matches("20","6", descriptors_img);
	vector< DMatch > matches20_7 = Matches("20","7", descriptors_img);*/
	/*vector< DMatch > matches50_1 = Matches("5001","5", descriptors_img);
	vector< DMatch > matches50_2 = Matches("5001","2", descriptors_img);
	vector< DMatch > matches50_3 = Matches("5001","3", descriptors_img);
	vector< DMatch > matches50_4 = Matches("5001","4", descriptors_img);
	vector< DMatch > matches50_5 = Matches("5001","5", descriptors_img);
	vector< DMatch > matches50_6 = Matches("5001","6", descriptors_img);
	vector< DMatch > matches50_7 = Matches("5001","7", descriptors_img);
	vector< DMatch > matches50_8 = Matches("5001","8", descriptors_img);*/

	/*vector< DMatch > matches50_1 = Matches("5002","1", descriptors_img);
	vector< DMatch > matches50_2 = Matches("5002","2", descriptors_img);
	vector< DMatch > matches50_3 = Matches("5002","3", descriptors_img);
	vector< DMatch > matches50_4 = Matches("5002","4", descriptors_img);
	vector< DMatch > matches50_5 = Matches("5002","5", descriptors_img);
	vector< DMatch > matches50_6 = Matches("5002","6", descriptors_img);
	vector< DMatch > matches50_7 = Matches("5002","7", descriptors_img);
	vector< DMatch > matches50_8 = Matches("5002","8", descriptors_img);*/

	/*vector< DMatch > matches50_1 = Matches("50","1", descriptors_img);
	vector< DMatch > matches50_2 = Matches("50","2", descriptors_img);
	vector< DMatch > matches50_3 = Matches("50","3", descriptors_img);
	vector< DMatch > matches50_4 = Matches("50","4", descriptors_img);
	vector< DMatch > matches50_5 = Matches("50","5", descriptors_img);
	vector< DMatch > matches50_6 = Matches("50","6", descriptors_img);
	vector< DMatch > matches50_7 = Matches("50","7", descriptors_img);
	vector< DMatch > matches50_8 = Matches("50","8", descriptors_img);*/
	/*vector< DMatch > matches100_1 = Matches("100","1", descriptors_img);
	vector< DMatch > matches100_2 = Matches("100","2", descriptors_img);
	vector< DMatch > matches100_3 = Matches("100","3", descriptors_img);
	vector< DMatch > matches100_4 = Matches("100","4", descriptors_img);
	vector< DMatch > matches100_5 = Matches("100","5", descriptors_img);
	vector< DMatch > matches100_6 = Matches("100","6", descriptors_img);
	vector< DMatch > matches100_7 = Matches("100","7", descriptors_img);*/
	vector< DMatch > matches100new_1 = Matches("1","7", descriptors_img);
	/*vector< DMatch > matches100new_2 = Matches("100new","2", descriptors_img);
	vector< DMatch > matches100new_3 = Matches("100new","3", descriptors_img);
	vector< DMatch > matches100new_4 = Matches("100new","4", descriptors_img);
	vector< DMatch > matches100new_5 = Matches("100new","5", descriptors_img);
	vector< DMatch > matches100new_6 = Matches("100new","6", descriptors_img);
	vector< DMatch > matches100new_7 = Matches("100new","7", descriptors_img);
	vector< DMatch > matches100new_8 = Matches("100new","8", descriptors_img);*/
	double min_dist = 0.3;
	/*min_dist = mindistance(matches1_1.size(), matches1_1, min_dist);
	min_dist = mindistance(matches1_2.size(), matches1_2, min_dist);
	min_dist = mindistance(matches1_3.size(), matches1_3, min_dist);
	min_dist = mindistance(matches1_4.size(), matches1_4, min_dist);
	min_dist = mindistance(matches1_5.size(), matches1_5, min_dist);
	min_dist = mindistance(matches1_6.size(), matches1_6, min_dist);
	min_dist = mindistance(matches1_7.size(), matches1_7, min_dist);*/
	/*min_dist = mindistance(matches5_1.size(), matches5_1, min_dist);
	min_dist = mindistance(matches5_2.size(), matches5_2, min_dist);
	min_dist = mindistance(matches5_3.size(), matches5_3, min_dist);
	min_dist = mindistance(matches5_4.size(), matches5_4, min_dist);
	min_dist = mindistance(matches5_5.size(), matches5_5, min_dist);
	min_dist = mindistance(matches5_6.size(), matches5_6, min_dist);
	min_dist = mindistance(matches5_7.size(), matches5_7, min_dist);*/
	/*min_dist = mindistance(matches10_1.size(), matches10_1, min_dist);
	min_dist = mindistance(matches10_2.size(), matches10_2, min_dist);
	min_dist = mindistance(matches10_3.size(), matches10_3, min_dist);
	min_dist = mindistance(matches10_4.size(), matches10_4, min_dist);
	min_dist = mindistance(matches10_5.size(), matches10_5, min_dist);
	min_dist = mindistance(matches10_6.size(), matches10_6, min_dist);
	min_dist = mindistance(matches10_7.size(), matches10_7, min_dist);*/
	/*min_dist = mindistance(matches20_1.size(), matches20_1, min_dist);
	min_dist = mindistance(matches20_2.size(), matches20_2, min_dist);
	min_dist = mindistance(matches20_3.size(), matches20_3, min_dist);
	min_dist = mindistance(matches20_4.size(), matches20_4, min_dist);
	min_dist = mindistance(matches20_5.size(), matches20_5, min_dist);
	min_dist = mindistance(matches20_6.size(), matches20_6, min_dist);
	min_dist = mindistance(matches20_7.size(), matches20_7, min_dist);*/
	/*min_dist = mindistance(matches50_1.size(), matches50_1, min_dist);
	min_dist = mindistance(matches50_2.size(), matches50_2, min_dist);
	min_dist = mindistance(matches50_3.size(), matches50_3, min_dist);
	min_dist = mindistance(matches50_4.size(), matches50_4, min_dist);
	min_dist = mindistance(matches50_5.size(), matches50_5, min_dist);
	min_dist = mindistance(matches50_6.size(), matches50_6, min_dist);
	min_dist = mindistance(matches50_7.size(), matches50_7, min_dist);
	min_dist = mindistance(matches50_8.size(), matches50_8, min_dist);*/
	/*min_dist = mindistance(matches100_1.size(), matches100_1, min_dist);
	min_dist = mindistance(matches100_2.size(), matches100_2, min_dist);
	min_dist = mindistance(matches100_3.size(), matches100_3, min_dist);
	min_dist = mindistance(matches100_4.size(), matches100_4, min_dist);
	min_dist = mindistance(matches100_5.size(), matches100_5, min_dist);
	min_dist = mindistance(matches100_6.size(), matches100_6, min_dist);
	min_dist = mindistance(matches100_7.size(), matches100_7, min_dist);*/
	min_dist = mindistance(matches100new_1.size(), matches100new_1, min_dist);
	/*min_dist = mindistance(matches100new_2.size(), matches100new_2, min_dist);
	min_dist = mindistance(matches100new_3.size(), matches100new_3, min_dist);
	min_dist = mindistance(matches100new_4.size(), matches100new_4, min_dist);
	min_dist = mindistance(matches100new_5.size(), matches100new_5, min_dist);
	min_dist = mindistance(matches100new_6.size(), matches100new_6, min_dist);
	min_dist = mindistance(matches100new_7.size(), matches100new_7, min_dist);
	min_dist = mindistance(matches100new_8.size(), matches100new_8, min_dist);*/
	/*vector< DMatch > good_matches1_1,good_matches1_2,good_matches1_3,good_matches1_4,good_matches1_5,good_matches1_6,good_matches1_7;
	int money1_1 = MatchNumber( matches1_1.size(), matches1_1, min_dist, good_matches1_1);
	int money1_2 = MatchNumber( matches1_2.size(), matches1_2, min_dist, good_matches1_2);
	int money1_3 = MatchNumber( matches1_3.size(), matches1_3, min_dist, good_matches1_3);
	int money1_4 = MatchNumber( matches1_4.size(), matches1_4, min_dist, good_matches1_4);
	int money1_5 = MatchNumber( matches1_5.size(), matches1_5, min_dist, good_matches1_5);
	int money1_6 = MatchNumber( matches1_6.size(), matches1_6, min_dist, good_matches1_6);
	int money1_7 = MatchNumber( matches1_7.size(), matches1_7, min_dist, good_matches1_7);*/
	/*vector< DMatch > good_matches5_1,good_matches5_2,good_matches5_3,good_matches5_4,good_matches5_5,good_matches5_6,good_matches5_7;
	int money5_1 = MatchNumber( matches5_1.size(), matches5_1, min_dist, good_matches5_1);
	int money5_2 = MatchNumber( matches5_2.size(), matches5_2, min_dist, good_matches5_2);
	int money5_3 = MatchNumber( matches5_3.size(), matches5_3, min_dist, good_matches5_3);
	int money5_4 = MatchNumber( matches5_4.size(), matches5_4, min_dist, good_matches5_4);
	int money5_5 = MatchNumber( matches5_5.size(), matches5_5, min_dist, good_matches5_5);
	int money5_6 = MatchNumber( matches5_6.size(), matches5_6, min_dist, good_matches5_6);
	int money5_7 = MatchNumber( matches5_7.size(), matches5_7, min_dist, good_matches5_7);*/
	/*vector< DMatch > good_matches10_1,good_matches10_2,good_matches10_3,good_matches10_4,good_matches10_5,good_matches10_6,good_matches10_7;
	int money10_1 = MatchNumber( matches10_1.size(), matches10_1, min_dist, good_matches10_1);
	int money10_2 = MatchNumber( matches10_2.size(), matches10_2, min_dist, good_matches10_2);
	int money10_3 = MatchNumber( matches10_3.size(), matches10_3, min_dist, good_matches10_3);
	int money10_4 = MatchNumber( matches10_4.size(), matches10_4, min_dist, good_matches10_4);
	int money10_5 = MatchNumber( matches10_5.size(), matches10_5, min_dist, good_matches10_5);
	int money10_6 = MatchNumber( matches10_6.size(), matches10_6, min_dist, good_matches10_6);
	int money10_7 = MatchNumber( matches10_7.size(), matches10_7, min_dist, good_matches10_7);*/
	/*vector< DMatch > good_matches20_1,good_matches20_2,good_matches20_3,good_matches20_4,good_matches20_5,good_matches20_6,good_matches20_7;
	int money20_1 = MatchNumber( matches20_1.size(), matches20_1, min_dist, good_matches20_1);
	int money20_2 = MatchNumber( matches20_2.size(), matches20_2, min_dist, good_matches20_2);
	int money20_3 = MatchNumber( matches20_3.size(), matches20_3, min_dist, good_matches20_3);
	int money20_4 = MatchNumber( matches20_4.size(), matches20_4, min_dist, good_matches20_4);
	int money20_5 = MatchNumber( matches20_5.size(), matches20_5, min_dist, good_matches20_5);
	int money20_6 = MatchNumber( matches20_6.size(), matches20_6, min_dist, good_matches20_6);
	int money20_7 = MatchNumber( matches20_7.size(), matches20_7, min_dist, good_matches20_7);*/
	/*vector< DMatch > good_matches50_1,good_matches50_2,good_matches50_3,good_matches50_4,good_matches50_5,good_matches50_6,good_matches50_7,good_matches50_8;
	int money50_1 = MatchNumber( matches50_1.size(), matches50_1, min_dist, good_matches50_1);
	int money50_2 = MatchNumber( matches50_2.size(), matches50_2, min_dist, good_matches50_2);
	int money50_3 = MatchNumber( matches50_3.size(), matches50_3, min_dist, good_matches50_3);
	int money50_4 = MatchNumber( matches50_4.size(), matches50_4, min_dist, good_matches50_4);
	int money50_5 = MatchNumber( matches50_5.size(), matches50_5, min_dist, good_matches50_5);
	int money50_6 = MatchNumber( matches50_6.size(), matches50_6, min_dist, good_matches50_6);
	int money50_7 = MatchNumber( matches50_7.size(), matches50_7, min_dist, good_matches50_7);
	int money50_8 = MatchNumber( matches50_8.size(), matches50_8, min_dist, good_matches50_8);*/
	/*vector< DMatch > good_matches100_1,good_matches100_2,good_matches100_3,good_matches100_4,good_matches100_5,good_matches100_6,good_matches100_7;
	int money100_1 = MatchNumber( matches100_1.size(), matches100_1, min_dist, good_matches100_1);
	int money100_2 = MatchNumber( matches100_2.size(), matches100_2, min_dist, good_matches100_2);
	int money100_3 = MatchNumber( matches100_3.size(), matches100_3, min_dist, good_matches100_3);
	int money100_4 = MatchNumber( matches100_4.size(), matches100_4, min_dist, good_matches100_4);
	int money100_5 = MatchNumber( matches100_5.size(), matches100_5, min_dist, good_matches100_5);
	int money100_6 = MatchNumber( matches100_6.size(), matches100_6, min_dist, good_matches100_6);
	int money100_7 = MatchNumber( matches100_7.size(), matches100_7, min_dist, good_matches100_7);*/
	vector< DMatch > good_matches100new_1,good_matches100new_2,good_matches100new_3,good_matches100new_4,good_matches100new_5,good_matches100new_6,good_matches100new_7,good_matches100new_8;
	int money100new_1 = MatchNumber( matches100new_1.size(), matches100new_1, min_dist, good_matches100new_1);
	//int money100new_2 = MatchNumber( matches100new_2.size(), matches100new_2, min_dist, good_matches100new_2);
	//int money100new_3 = MatchNumber( matches100new_3.size(), matches100new_3, min_dist, good_matches100new_3);
	//int money100new_4 = MatchNumber( matches100new_4.size(), matches100new_4, min_dist, good_matches100new_4);
	//int money100new_5 = MatchNumber( matches100new_5.size(), matches100new_5, min_dist, good_matches100new_5);
	//int money100new_6 = MatchNumber( matches100new_6.size(), matches100new_6, min_dist, good_matches100new_6);
	//int money100new_7 = MatchNumber( matches100new_7.size(), matches100new_7, min_dist, good_matches100new_7);
	//int money100new_8 = MatchNumber( matches100new_8.size(), matches100new_8, min_dist, good_matches100new_8,100,8);

	/*cout<<"50元1    "<<money50_1<<endl;cout<<"50元2    "<<money50_2<<endl;
	cout<<"50元3    "<<money50_3<<endl;cout<<"50元4    "<<money50_4<<endl;cout<<"50元5    "<<money50_5<<endl;
	cout<<"50元6    "<<money50_6<<endl;cout<<"50元7    "<<money50_7<<endl;cout<<"50元8    "<<money50_8<<endl;*/
	/*cout<<"1元1     "<<money1_1<<endl;cout<<"1元2     "<<money1_2<<endl;cout<<"1元3     "<<money1_3<<endl;
	cout<<"1元4     "<<money1_4<<endl;cout<<"1元5     "<<money1_5<<endl;cout<<"1元6     "<<money1_6<<endl;
	cout<<"1元7     "<<money1_7<<endl;*/
	/*cout<<"5元1     "<<money5_1<<endl;cout<<"5元2     "<<money5_2<<endl;
	cout<<"5元3     "<<money5_3<<endl;cout<<"5元4     "<<money5_4<<endl;cout<<"5元5     "<<money5_5<<endl;
	cout<<"5元6     "<<money5_6<<endl;cout<<"5元7     "<<money5_7<<endl;*/
	/*cout<<"10元1    "<<money10_1<<endl;
	cout<<"10元2    "<<money10_2<<endl;cout<<"10元3    "<<money10_3<<endl;cout<<"10元4    "<<money10_4<<endl;
	cout<<"10元5    "<<money10_5<<endl;cout<<"10元6    "<<money10_6<<endl;cout<<"10元7    "<<money10_7<<endl;*/
	/*cout<<"20元1    "<<money20_1<<endl;cout<<"20元2    "<<money20_2<<endl;cout<<"20元3    "<<money20_3<<endl;
	cout<<"20元4    "<<money20_4<<endl;cout<<"20元5    "<<money20_5<<endl;cout<<"20元6    "<<money20_6<<endl;
	cout<<"20元7    "<<money20_7<<endl;*/
	/*cout<<"50元1    "<<money50_1<<endl;cout<<"50元2    "<<money50_2<<endl;
	cout<<"50元3    "<<money50_3<<endl;cout<<"50元4    "<<money50_4<<endl;cout<<"50元5    "<<money50_5<<endl;
	cout<<"50元6    "<<money50_6<<endl;cout<<"50元7    "<<money50_7<<endl;cout<<"50元8    "<<money50_8<<endl;*/
	/*cout<<"100元1   "<<money100_1<<endl;cout<<"100元2   "<<money100_2<<endl;cout<<"100元3   "<<money100_3<<endl;
	cout<<"100元4   "<<money100_4<<endl;cout<<"100元5   "<<money100_5<<endl;cout<<"100元6   "<<money100_6<<endl;
	cout<<"100元7   "<<money100_7<<endl;*/
	
	cout<<"新100元1 "<<money100new_1<<endl;
	/*cout<<"新100元2 "<<money100new_2<<endl;
	cout<<"新100元3 "<<money100new_3<<endl;cout<<"新100元4 "<<money100new_4<<endl;cout<<"新100元5 "<<money100new_5<<endl;
	cout<<"新100元6 "<<money100new_6<<endl;cout<<"新100元7 "<<money100new_7<<endl;//cout<<"新100元8 "<<money100new_8<<endl;*/

	//system("pause");
	return 0;
}



vector< DMatch > Matches(string moneyclass, string moneyregion, Mat descriptors_img) 
{
	
	//载入类间参考区域的描述子
	string fileFolder_descriptions = "E:\\ZJU\\template\\descriptors\\" + moneyclass + "\\descriptors"+ moneyclass + "_" + moneyregion + ".xml";
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


	//输出最终模板
	FILE *fp1,*fp2;
	int n;
	int count = 0; // 数字计数
	fp1 = fopen ("E:\\ZJU\\template\\point\\1\\region7\\resultall.txt","r");   //重复点的序号

	int i=0;
	int data[50000];
	while(fscanf(fp1, "%d\n", &data[i])!=EOF){	i++; count++;}
	fclose(fp1);

	FileStorage fs("E:\\ZJU\\template\\final\\1\\descriptors_region7.xml",FileStorage::WRITE); //模板文件
	fs<< "data"<<"[";		
	for (i=0;i <count;i++){
		
		fs <<descriptors.row(data[i]);
		//fprintf(fp2,"%le\n",descriptors.row(data[i]));
		
	}
	fs<< "]";
	return matches;
}
double mindistance(int rows, vector< DMatch > matches, double min_dist)
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
		/*FileStorage fs("E:\\ZJU\\SURF\\test.xml",FileStorage::WRITE);

		fs<< "data"<<"[";
		for(num = 0;num<good_matches.size();num++)
		{
			
			//good_matches[num].queryIdx,;
			//output[num][2] = good_matches[num].trainIdx;
			fs <<good_matches[num].queryIdx;
		//fs <<good_matches[num].trainIdx;
		//cout<<"goodmatches queryIdx = "<<good_matches[num].queryIdx<<endl;
		//cout<<"goodmatches trainIdx = "<<good_matches[num].trainIdx<<endl;
	
	}
		fs<<"]";*/

	//输出匹配的序号值

	/*FILE *fp;
	fp = fopen ("E:\\ZJU\\template\\point\\1\\region7\\match.txt","w+");
	for(num = 0;num<good_matches.size();num++)
		{
			fprintf(fp,"%d\n",good_matches[num].trainIdx);
	}*/
		
	return good_matches.size();
}

