/*************************************************************************
    > File Name: endia_test.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年03月29日 星期四 14时50分38秒
 ************************************************************************/

#include<stdio.h>
int main()  
{
	int a = 1;  
	char * p = (char*)&a;  
	if (*p == 1) {
		printf("little-endian\n");  
	} else  {
		printf("big-endian\n");  
	}
	return 0;
}
