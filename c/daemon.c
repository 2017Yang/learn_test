/*************************************************************************
    > File Name: daemon.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年03月24日 星期六 11时43分51秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>

void init_daemon(void) {
	pid_t pid;
	int i = 0;
	pid = fork();
	if(pid > 0) {
		exit(0);
	} else if (pid < 0) {
		perror("创建子进程失败\n");
		exit(1);
	} else if(pid == 0) {
		setsid(); //子进程中创建新会话
		chdir("/tmp"); //改变工作目录到tmp
		umask(0); //重设文件掩码
		for (i=0; i<NOFILE; ++i) {
			close(i);
		}
		return ;
	}
}
int main()
{
	FILE *fp;
	time_t t;
	init_daemon();
	while(1) {
		sleep(10);
		if ((fp=fopen("log.txt","a+")) >= 0) {
			t = time(0);
			fprintf(fp,"守护进程正在运行, 时间是: %s", asctime(localtime(&t)));
			fclose(fp);
		}
	}
	return 0;
}
