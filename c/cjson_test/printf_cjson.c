/*************************************************************************
    > File Name: printf_cjson.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年04月02日 星期一 09时48分16秒
 ************************************************************************/

#include<stdio.h>
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>

/**
 *	{
 *		"upgrade": "set",
 * 		"ID": 2,
 *		"CmdType": ENUM_OPERATION_UPGRADE,
 *		"ConTent"{
 *			"upgrade_file_path": "/cache/text.txt"
 *			"upgrade_type": 1
 *			"reboot_flag": 1
 *		}	
 *	}
*/
typedef struct
{
	char js_type[10];
	int id;;
	int CmdType;
	char file_path[64];
	int upgrade_type;
	int reboot_flag;
}upgrade_info_st;

#if 0
int create_json()
{
	char *out;
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
	printf("out: %s\n",out);

	upgrade_info_st stUpgradeInfo;
	root = cJSON_Parse(out);	 
	if (!root) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else {
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
	
		printf("%s:", item->string);   //看一下cjson对象的结构体中这两个成员的意思
		printf("%s\n", item->valuestring);
						

		printf("\n%s\n", "打印json所有最内层键值对:");
		printJson(root);
	}
	return 0;	 
}
#endif


//int create_json(char *out)
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

int main()
{
	///char buff[1024] = {0};
	char *string = NULL;
	string = create_json(string);
	jiexi_json(string);
	return 0;
}
