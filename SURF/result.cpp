#include <stdio.h>

struct numCountStruct {
    int num;
    int count;
} number[10000];

void result_txt(char *fileread, char *filewrite,char *fileresult){
	int countnum1 = 0; // ���ּ���
	int n;
		FILE *fp;
		fp = fopen(fileread, "r");
		fseek(fp,0,0);
    	while (fscanf(fp, "%d\n", &n)!=EOF) { // �����ļ�ĩβ
       	 int i;
       	 for (i = 0; i < countnum1; i++) 
			{
            if (number[i].num == n) {  // �����Ѿ����ֹ�����������1
                number[i].count++;
				break;
				}
        	}
       		if (i == countnum1) { 		// �µ����֣���ӵ�����ĩβ
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
	result_txt("E:\\ZJU\\template\\point\\100new\\region2\\matchall.txt","E:\\ZJU\\template\\point\\100new\\region2\\resultall.txt","E:\\ZJU\\template\\point\\100new\\region2\\repeat.txt");
}
