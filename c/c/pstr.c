/*************************************************************************
    > File Name: pstr.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年04月20日 星期五 09时32分40秒
 ************************************************************************/

#include<stdio.h>

int main()
{
	int a = 1;
	char *p = (char *)&a;
	printf("%d\n",*p);
	return 0;
}
