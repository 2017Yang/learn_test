/*************************************************************************
    > File Name: test_lstat.c
    > Author: yangyong 
    > Created Time: 2018年06月07日 星期四 18时57分06秒
	>判断某个目录是否存在
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	struct stat st;

	memset(&st, 0, sizeof(st));
	if (lstat(argv[1], &st) == 0) {
		printf("#########\n");
	} else {
		printf("@@@@@@@@@@\n");
	}
	return 0;
}
