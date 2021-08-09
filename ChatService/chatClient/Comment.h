#ifndef _COMMENT_H_
#define _COMMENT_H_

#include <string>
using namespace std;


//定义信息结构，在服务端和客户端之间传送
struct Msg
{
	int signInOrSignOut;
	char userName[20];
	char password[20];
	int zone;

};

struct Session 
{
	char userName[20];
	char clientChat[200];
	int zone;
};
#endif // _COMMENT_H_

