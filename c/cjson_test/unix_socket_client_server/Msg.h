/*************************************************************************
    > File Name: Msg.h
    > Created Time: 2018年04月21日 星期六 16时02分13秒
 ************************************************************************/
#ifndef _MSG_H_
#define _MSG_H_

// json　格式
// // 请求：　｛"Method":"set/get/report","ID":xxx,"CmdType":"","Parameter":{
// }｝
// // 响应：　｛"ID": XXX,"ResultCode":0,"Reason":"XXX"｝

typedef enum
{
	ENUM_OPERATION_GET = 0x01,
	ENUM_OPERATION_SET = 0x02,
	ENUM_OPERATION_REPORT = 0x03,
	ENUM_OPERATION_KNOW = 0x04
}MSG_TYPE_E;

typedef struct
{
	MSG_TYPE_E eMsgType;
	int length;
}MSG_HEAD_ST;
#endif
