/*************************************************************************
    > File Name: maopao.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年04月19日 星期四 19时51分55秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int i = 0;
	int temp = 0;
	int j = 0;
	int str[10] ={0,1,3,2,5,4,7,6,8,9};
	for (i=0;i<10-1; i++) {
		for (j=0; j<10-i+1; j++) {
			if (str[i]>str[i+1]) {
				temp = str[i+1];
				str[i+1] = str[i];
				str[i] = temp;
			}
		}
	}
	for (i=0; i<10; i++) {
		printf("str[%d]: %d\n",i,str[i]);
	}
	return 0;
}
