/*************************************************************************
    > File Name: test_system.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年03月26日 星期一 19时50分36秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{
	int  status;
	status = system("lc");
	if (-1 == status) {
		printf("system error\n");
	} else {
		printf("exit status value = [0x%x]\n",status);
		if (WIFEXITED(status)){
			if(0 == WEXITSTATUS(status)) {
				printf("run shell script successfully.\n");
			} else {
				printf("run shell scriptfail, script exit code: %d\n",WEXITSTATUS(status));
				return -1;
			} 
		} else {
			printf("exit status = [%d]\n",WEXITSTATUS(status));
		}
	}
	return 0;
}
