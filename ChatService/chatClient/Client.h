#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#include <windows.h>

#include "SignIn.h"
#include "SignUp.h"
#include "Comment.h"


using namespace std;


/*
	增加线程
	并发
	线程1 ：接收用户输入并发送到服务器
	线程2 ：接收服务器发来的数据并显示到界面上
*/

class Client {
private:

	// 用户选择注册还是登录
	int signInOrSignOut = 0;

	// 接收缓存
	char recvBuff[1024];

	// 登录和注册使用的信息
	Msg massage;

	// 用户发送的信息
	Session clientSession;

	// 用户socket
	SOCKET clientSocket;

public:

	// 连接服务器
	int connectServer();

	// 用户注册
	void userSignIn();

	// 用户登录
	void userSignUp();

	// 用户通信
	void communication();

	// 用户断开连接
	void disconnect();

	// 获得套接字
	SOCKET getClientSocket();

	// 用户选择注册还是登录
	void userSelectSignInOrSignUp();
};