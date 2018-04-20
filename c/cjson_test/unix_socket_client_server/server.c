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
typedef menu
{
	ENUM_OPERATION_GET,
	ENUM_OPERATION_SET,
	ENUM_OPERATION_REPORT,
	ENUM_OPERATION_KNOW
}MSG_TYPE_E;
typedef struct
{
	MSG_TYPE_E eMsgTYpe;
	int msg_length;
}MSG_HEAD_ST;

int jiexi_json(char *input)
{
	cJSON * root = NULL;
	cJSON * item = NULL;//cjson对象
	cJSON *object = NULL;
	upgrade_info_st stUpgradeInfo;

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
		cJSON *object = cJSON_GetObjectItem(root, "ConTent");//
		printf("%s\n", cJSON_Print(object));

		
		printf("%s\n", "获取ConTent下的upgrade_file_path对象");
		item = cJSON_GetObjectItem(object, "upgrade_file_path");
		printf("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s\n",item->type,item->string,item->valuestring);
		//memcpy(stUpgradeInfo.file_path,item->valuestring,strlen(item->valuestring)); 
		sprintf(stUpgradeInfo.file_path,"%s",item->valuestring);
		printf("upgrade_file_path: %s\n",stUpgradeInfo.file_path);

		item = cJSON_GetObjectItem(object, "upgrade_type");
		stUpgradeInfo.upgrade_type = item->valueint;
		printf("upgrade_type: %d\n", stUpgradeInfo.upgrade_type);

		item = cJSON_GetObjectItem(object, "reboot_flag");
		stUpgradeInfo.reboot_flag = item->valueint;
		printf("reboot_flag: %d\n", stUpgradeInfo.reboot_flag);
		
	//	printf("%s:", item->string);   //看一下cjson对象的结构体中这两个成员的意思
	//	printf("%s\n", item->valuestring);
						

		printf("\n%s\n", "打印json所有最内层键值对:");
		//printJson(root);
	}
	return 0;	 
}

char * create_json()
{
	char *out = NULL;
	cJSON * root =  cJSON_CreateObject();
    cJSON * item =  cJSON_CreateObject();

	cJSON_AddItemToObject(root, "ID", cJSON_CreateNumber(2));
	cJSON_AddItemToObject(root, "ResultCode", cJSON_CreateNumber(0));
	cJSON_AddItemToObject(root, "Reason", cJSON_CreateString("NULL"));
	cJSON_AddItemToObject(root, "Data", item);//root节点下添加semantic节点
	cJSON_AddItemToObject(item, "Upgrade_state", cJSON_CreateNumber(1));//添加name节点								
							
	out = cJSON_Print(root);
	//printf("out: %s\n",out);
	//memcpy(out,cJSON_Print(root),sizeof(out));
	printf("out: %s\n",out);
	return out;
}

int main()
{
	int ret = 0;
	int server_fd = 0;
	int client_fd = 0;
	struct sockaddr_un server;
	char buff[2048] = {0};
	char *str = NULL;
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
		ret = read(client_fd,buff,2048);
		if (ret < 0) {
			perror("read fail\n");
		} else {
			printf("ret:　%d\n",ret);
			jiexi_json(buff);
			str = create_json();
			memset(buff,0,sizeof(buff));
			memcpy(buff,str,strlen(str));
			write(client_fd,buff,strlen(buff));
		}
		
	}
	close(server_fd);
	unlink(PATH);
	return 0;
}
