/*************************************************************************
    > File Name: dir.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2017年10月28日 星期六 14时16分45秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>

int socket_ls()
{
	DIR* dir;
	struct dirent* rd;
	dir = opendir("../test");
	if (NULL == dir) {
		perror("opendir fail");
		return -1;
	}
	
	while(1){
		rd = readdir(dir);
		if (NULL == rd) {
			printf("\n");
			return -1;
		} else {
			printf(" %s\t",rd->d_name);
		}
	}
	closedir(dir);
	return 0;
}
