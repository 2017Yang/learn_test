/*************************************************************************
    > File Name: client.c
    > Created Time: 2018年03月31日 星期六 11时06分19秒
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include "cJSON.h"
#define PATH "./server"
#include "Msg.h"

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
		return -1;
	} else {
		printf("connect success !\n");
	}
	return client_fd;
}
//{"upgrade":"set","ID":2,"CmdType":2,"ConTent":{"upgrade_file_path":"cache/text.txt","upgrade_type":1,"reboot_flag":1}}
char * create_json()
{
	char *out = NULL;
	cJSON * root =  cJSON_CreateObject();
    cJSON * item =  cJSON_CreateObject();
	cJSON_AddItemToObject(root, "Method", cJSON_CreateString("set"));//根节点下添加
	cJSON_AddItemToObject(root, "ID", cJSON_CreateNumber(2));
	cJSON_AddItemToObject(root, "CmdType", cJSON_CreateNumber(2));
	cJSON_AddItemToObject(root, "Parametert", item);//root节点下添加semantic节点
	out = cJSON_Print(root);
	//printf("out: %s\n",out);
	return out;
}

int parse_json(char *input)
{
	cJSON * root = NULL;
	cJSON * item = NULL;//cjson对象
	cJSON *object = NULL;

	root = cJSON_Parse(input);	 
	if (!root) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return -1;
	} else {
		printf("%s\n", "有格式的方式打印Json:");		   
		printf("%s\n\n", cJSON_Print(root));
		printf("%s\n", "无格式方式打印json：");
		printf("%s\n\n", cJSON_PrintUnformatted(root));

		printf("%s\n", "获取下root的对象ID:");
		item = cJSON_GetObjectItem(root, "ID");//
		printf("%d\n", item->valueint);

		printf("%s\n", "获取root下的ResultCode对象");
		item = cJSON_GetObjectItem(root, "ResultCode");
		printf("flag: %d\n",item->valueint);
	}
	return 0;	 
}

int main()
{
	int ret = 0;
	int client_fd = -1;
	char *string = NULL;
	char *json_buff = NULL;
	char *p = NULL;
	char *q = NULL;
	MSG_HEAD_ST stMsgHead;
	client_fd = socket_create(AF_UNIX,SOCK_STREAM,0,PATH);
	if (client_fd < 0) {
		printf("socket create fail\n");
		return -1;
	}
	printf("client socket create ok!\n");
	memset(&stMsgHead,0,sizeof(MSG_HEAD_ST));
	string = create_json();
	printf("sizeof(string): %d\n",strlen(string));
	stMsgHead.eMsgType = ENUM_OPERATION_SET;
	stMsgHead.length = strlen(string);
	p = (char *)&stMsgHead;
	p += sizeof(MSG_HEAD_ST);
	p = (char *)malloc(sizeof(char)*stMsgHead.length);
	memcpy(p,string,sizeof(string));
	ret = write(client_fd,&stMsgHead,sizeof(MSG_HEAD_ST)+stMsgHead.length);
	if (ret >= 0) {
		memset(&stMsgHead,0,sizeof(MSG_HEAD_ST));
		printf("stMsgHead.eMsgHeadType: %d\n",stMsgHead.eMsgType);
		printf("stMsgHead.length: %d\n",stMsgHead.length);


		ret = read(client_fd,&stMsgHead,sizeof(MSG_HEAD_ST));
		if (ret < 0) {
			printf("read fail\n");
		} else {
			json_buff = (char*)malloc(sizeof(char) * stMsgHead.length);
			if (NULL == json_buff) {
				printf("json_buff malloc fail\n");
				return -1;
			}
			q = (char *)&stMsgHead;
			q += sizeof(MSG_HEAD_ST);
			memcpy(json_buff,q,sizeof(json_buff));
			parse_json(json_buff);
		}
	}
	return 0;
}
