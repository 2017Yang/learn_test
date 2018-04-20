/*************************************************************************
    > File Name: client.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年03月31日 星期六 11时06分19秒
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#define PATH "./server"

int socket_create(int domain,int type, int protocol,char *path)
{
	int ret = 0;
	int client_fd = 0;
	struct sockaddr_un server;
	client_fd = socket(domain,type,protocol);
	if (client_fd < 0) {
		printf("socket create fail\n");
		return -1;
	}
	
	server.sun_family = domain;
	strcpy(server.sun_path,path);
	while(1) {
		ret = connect(client_fd,(struct sockaddr *)&server,sizeof(server));
		if (ret < 0) {
			perror("connect fail\n");
			continue;
		} else {
			printf("connect success !\n");
			break;
		}
	}
	return client_fd;
}

int main()
{
	int ret = 0;
	ret = socket_create(AF_UNIX,SOCK_STREAM,0,PATH);
	if (ret < 0) {
		printf("socket create fail\n");
		return -1;
	}

	return 0;
}
