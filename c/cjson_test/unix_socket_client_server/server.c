/*************************************************************************
    > File Name: server.c
    > Created Time: 2018年03月31日 星期六 10时12分34秒
 ************************************************************************/
#include<stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "cJSON.h"
#include <string.h>
#define PATH "./server"
#include "Msg.h"


int jiexi_json(char *input, int *id)
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

		printf("%s\n", "获取下root的Method对象:");
		item = cJSON_GetObjectItem(root, "Method");//
		printf("Methon: %s\n",item->valuestring);

		printf("%s\n", "获取下root的ID对象:");
		item = cJSON_GetObjectItem(root, "ID");//
		printf("ID: %d\n",item->valueint);
		*id = item->valueint;


		printf("%s\n", "获取下root的CmdType对象:");
		item = cJSON_GetObjectItem(root, "CmdType");//
		printf("CmdType: %s\n",item->valuestring);
		
		printf("%s\n", "获取Parameter下的对象");
		object = cJSON_GetObjectItem(object, "Parameter");
		printf("parameter: %s\n",cJSON_Print(object));
	}
	return 0;	 
}

char * create_success_json(int Id,int ResCode)
{
	char *out = NULL;
	cJSON * root =  cJSON_CreateObject();
	cJSON_AddItemToObject(root, "ID", cJSON_CreateNumber(Id));
	cJSON_AddItemToObject(root, "ResultCode", cJSON_CreateNumber(ResCode));
	cJSON_AddItemToObject(root, "Reason", cJSON_CreateString("NULL"));
							
	out = cJSON_Print(root);
	//printf("out: %s\n",out);
	return out;
}
char *create_fail_json(int Id,int ResCode,char* err)
{
	char *out = NULL;
	cJSON *root = NULL;
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "ID", cJSON_CreateNumber(Id));
	cJSON_AddItemToObject(root, "ResultCode", cJSON_CreateNumber(ResCode));
	cJSON_AddItemToObject(root, "Reason", cJSON_CreateString(err));
							
	out = cJSON_Print(root);
	//printf("out: %s\n",out);
	return out;
}
int main()
{
	int ret = 0;
	int server_fd = 0;
	int client_fd = 0;
	int id = 0;
	struct sockaddr_un server;
	char *str = NULL;
	char *p = NULL;
	char *json_buff = NULL;
	MSG_HEAD_ST stMsgHead;
	unlink(PATH);
	server_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if (server_fd < 0) {
		printf("server_fd create fail\n");
		return -1;
	}
	printf("socket create ok\n");
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path,PATH);
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
		memset(&stMsgHead,0,sizeof(MSG_HEAD_ST));
		ret = read(client_fd,&stMsgHead,sizeof(MSG_HEAD_ST));
		if (ret < 0) {
			perror("read fail\n");
		} else {
			printf("ret:　%d\n",ret);
			printf("stMsgHead type: %d\n",stMsgHead.eMsgType);
			printf("stMsgHead length: %d\n",stMsgHead.length);
			json_buff = (char *)malloc(sizeof(char) * stMsgHead.length);
			if (NULL == json_buff) {
				printf("json_buff malloc fail\n");
				continue;
			}
			p = (char*)&stMsgHead;
			p += sizeof(MSG_HEAD_ST);
			memcpy(json_buff,p,stMsgHead.length);
			ret = jiexi_json(json_buff,&id);
			if (0 == ret) {
				str = create_success_json(id,0);
			} else {
				str = create_fail_json(id,2,"fail");	
			}
			memset(&stMsgHead,0,sizeof(MSG_HEAD_ST));
			stMsgHead.eMsgType = ENUM_OPERATION_REPORT;
			stMsgHead.length = strlen(str);
			p = (char*)&stMsgHead;
			p += sizeof(MSG_HEAD_ST);
			p = malloc(sizeof(char)*stMsgHead.length);
			memcpy(p,str,sizeof(str));
			ret = write(client_fd,&stMsgHead,sizeof(MSG_HEAD_ST)+stMsgHead.length);
			if (ret <= 0) {
				printf("server write fail\n");
				return -1;
			}
			printf("server write ok!\n");
		}
		
	}
	close(server_fd);
	unlink(PATH);
	return 0;
}
