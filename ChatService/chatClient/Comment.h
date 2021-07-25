#ifndef _COMMENT_H_
#define _COMMENT_H_

#include <string>
using namespace std;

// 默认服务器端IP地址
#define SERVER_IP "127.0.0.1"

// 服务器端口号
#define SERVER_PORT 8888

// int epoll_create(int size)中的size
// 为epoll支持的最大句柄数
#define EPOLL_SIZE 5000

// 缓冲区大小65535
#define BUF_SIZE 0xFFFF

// 新用户登录后的欢迎信息
#define SERVER_WELCOME "Welcome you join to the chat room! Your chat ID is: Client #%d"

// 其他用户收到消息的前缀
#define SERVER_MESSAGE "ClientID %d say >> %s"
#define SERVER_PRIVATE_MESSAGE "Client %d say to you privately >> %s"
#define SERVER_PRIVATE_ERROR_MESSAGE "Client %d is not in the chat room yet~"
// 退出系统
#define EXIT "EXIT"

// 提醒你是聊天室中唯一的客户
#define CAUTION "There is only one int the char room!"


//定义信息结构，在服务端和客户端之间传送
struct Msg
{
	int signInOrSignOut;
	string userName;
	string password;
	int zone;

};
#endif // _COMMENT_H_

