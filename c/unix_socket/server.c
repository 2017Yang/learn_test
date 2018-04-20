/*************************************************************************
    > File Name: server.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年03月31日 星期六 10时12分34秒
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>

const char path[] = "./server";
int main()
{
	int ret = 0;
	int server_fd = 0;
	int client_fd = 0;
	struct sockaddr_un server;
	char buff[512] = {0};
	unlink(path);
	server_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if (server_fd < 0) {
		printf("server_fd create fail\n");
		return -1;
	}
	printf("socket create ok\n");
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path,path);
	if (bind(server_fd,(struct sockaddr *)&server,sizeof(server))==-1) {
		perror("bind fail\n");
		return -1;
	}
	printf("socket_bind ok\n");
	listen(server_fd,5);
	while(1) {
		client_fd = accept(server_fd,0,0);
		if (client_fd < 0) {
			perror("accept fail\n");
			return -1;
		} 
		printf("accept success\n");
		ret = read(client_fd,buff,512);
		if (ret < 0) {
			perror("read fail\n");
		} else {
			printf("ret:　%d\n",ret);
		}
	}
	close(server_fd);
	unlink(path);
	return 0;
}
