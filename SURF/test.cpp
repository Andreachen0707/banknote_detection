#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
//#include <iostream>

struct numCountStruct {
    int num;
    int count;
} numCount[1000],number[1000];


void updatetxt(char *fileread, char *filewrite){
	int countnum = 0; // 数字计数
    int n;
    FILE *fp;
	fp = fopen(fileread, "r+");

    while (fscanf(fp, "%d\n", &n)!=EOF) { // 处理到文件末尾
        int i;
        for (i = 0; i < countnum; i++) {
            if (numCount[i].num == n) { // 发现已经出现过，出现数＋1
                numCount[i].count++;
				break; 
            }
        }
       if (i == countnum) { // 新的数字，添加到数组末尾
		numCount[countnum++] = {n,1}; 
        }
    }
    fclose(fp);
    
    
    FILE *fp1;
    fp1 = fopen(filewrite, "a");
    
    for (int i = 0; i < countnum; i++) {
		fprintf(fp1,"%d\n",numCount[i].num);
        //printf("%d presents %d times.\n", numCount[i].num, numCount[i].count);
    }
}

void result_txt(char *fileread, char *filewrite,char *fileresult){
	int countnum1 = 0; // 数字计数
	int n;
		FILE *fp;
		fp = fopen(fileread, "r");
		fseek(fp,0,0);
    	while (fscanf(fp, "%d\n", &n)!=EOF) { // 处理到文件末尾
       	 int i;
       	 for (i = 0; i < countnum1; i++) 
			{
            if (number[i].num == n) {  // 发现已经出现过，出现数＋1
                number[i].count++;
				break;
				}
        	}
       		if (i == countnum1) { 		// 新的数字，添加到数组末尾
				number[countnum1++] = {n,1}; 
        		}
    	}
    	fclose(fp);
    	
		FILE *fpresult, *fprepeat;
   		fpresult = fopen(filewrite, "w");
    	fprepeat = fopen(fileresult, "w");
		for (int i = 0; i < countnum1; i++) {
			fprintf(fpresult,"%d\n",number[i].num);
			if(number[i].count!=1)
			fprintf(fprepeat,"%d   %d\n",number[i].num, number[i].count);
        //printf("%d presents %d times.\n", numCount[i].num, numCount[i].count);
    	}
    	fclose(fpresult);
    	fclose(fprepeat);
}

int main(int argc, char** argv ) 
{ 
	updatetxt("E:\\ZJU\\template\\point\\1\\region6\\match1.txt","E:\\ZJU\\template\\point\\1\\region6\\matchall.txt"); 
	updatetxt("E:\\ZJU\\template\\point\\1\\region6\\match2.txt","E:\\ZJU\\template\\point\\1\\region6\\matchall.txt");
	updatetxt("E:\\ZJU\\template\\point\\1\\region6\\match3.txt","E:\\ZJU\\template\\point\\1\\region6\\matchall.txt");
	updatetxt("E:\\ZJU\\template\\point\\1\\region6\\match4.txt","E:\\ZJU\\template\\point\\1\\region6\\matchall.txt");
	updatetxt("E:\\ZJU\\template\\point\\1\\region6\\match5.txt","E:\\ZJU\\template\\point\\1\\region6\\matchall.txt");
	//updatetxt("E:\\ZJU\\template\\point\\1\\region6\\match6.txt","E:\\ZJU\\template\\point\\1\\region6\\matchall.txt");
	//updatetxt("E:\\ZJU\\template\\point\\1\\region6\\match7.txt","E:\\ZJU\\template\\point\\1\\region6\\matchall.txt");
	//updatetxt("E:\\ZJU\\template\\point\\5\\region6\\match8.txt","E:\\ZJU\\template\\point\\5\\region6\\matchall.txt");
	//Sleep(1);
	result_txt("E:\\ZJU\\template\\point\\1\\region6\\matchall.txt",
	"E:\\ZJU\\template\\point\\1\\region6\\resultall.txt",
	"E:\\ZJU\\template\\point\\1\\region6\\repeat.txt");
	
   
}
