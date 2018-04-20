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
#include "cJSON.h"

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
	ret = connect(client_fd,(struct sockaddr *)&server,sizeof(server));
	if (ret < 0) {
		perror("connect fail\n");
		continue;
	} else {
		printf("connect success !\n");
		break;
	}
	return client_fd;
}
//{"upgrade":"set","ID":2,"CmdType":2,"ConTent":{"upgrade_file_path":"cache/text.txt","upgrade_type":1,"reboot_flag":1}}
char * create_json()
{
	char *out = NULL;
	cJSON * root =  cJSON_CreateObject();
    cJSON * item =  cJSON_CreateObject();
	cJSON * next =  cJSON_CreateObject();
	cJSON_AddItemToObject(root, "upgrade", cJSON_CreateString("set"));//根节点下添加
	cJSON_AddItemToObject(root, "ID", cJSON_CreateNumber(2));
	cJSON_AddItemToObject(root, "CmdType", cJSON_CreateNumber(2));
	cJSON_AddItemToObject(root, "ConTent", item);//root节点下添加semantic节点
	cJSON_AddItemToObject(item, "upgrade_file_path", cJSON_CreateString("cache/text.txt"));//添加name节点								
	cJSON_AddItemToObject(item, "upgrade_type", cJSON_CreateNumber(1));//添加name节点								
	cJSON_AddItemToObject(item, "reboot_flag", cJSON_CreateNumber(1));//添加name节点								
	out = cJSON_Print(root);
	//printf("out: %s\n",out);
	//memcpy(out,cJSON_Print(root),sizeof(out));
	printf("out: %s\n",out);
	return out;
}

int jiexi_json(char *input)
{
	cJSON * root = NULL;
	cJSON * item = NULL;//cjson对象
	cJSON *object = NULL;
	int flag = 0;

	root = cJSON_Parse(input);	 
	if (!root) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return -1;
	} else {
		printf("%s\n", "有格式的方式打印Json:");		   
		printf("%s\n\n", cJSON_Print(root));
		printf("%s\n", "无格式方式打印json：");
		printf("%s\n\n", cJSON_PrintUnformatted(root));

		printf("%s\n", "获取下root的ConTent对象:");
		cJSON *object = cJSON_GetObjectItem(root, "Data");//
		printf("%s\n", cJSON_Print(object));

		printf("%s\n", "获取ConTent下的upgrade_file_path对象");
		item = cJSON_GetObjectItem(object, "upgrade_state");
		flag = item->valueint;
		printf("flag: %d\n",flag);
		printf("\n%s\n", "打印json所有最内层键值对:");
		//printJson(root);
	}
	return 0;	 
}

int main()
{
	int ret = 0;
	int client_fd = -1;
	char *string = NULL;
	char buff[2048] = {0};
	string = create_json();
	memcpy(buff,string,strlen(string));
	client_fd = socket_create(AF_UNIX,SOCK_STREAM,0,PATH);
	if (client_fd < 0) {
		printf("socket create fail\n");
		return -1;
	}
	printf("client socket create ok!\n");
	printf("sizeof(string): %d\n",sizeof(string));
	ret = write(client_fd,buff,strlen(buff));
	if (ret >= 0) {
		memset(buff,0,sizeof(buff));
		ret = read(client_fd,buff,sizeof(buff));
		if (ret < 0) {
			printf("read fail\n");
		} else {
			jiexi_json(buff);
		}
	}
return 0;
}
