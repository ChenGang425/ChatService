#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#include <windows.h>

#include "SignIn.h"
#include "SignUp.h"
#include "Comment.h"
#include "DataBaseClient.h"

using namespace std;

/*
	增加线程
	并发
	线程1 ：接收用户输入并发送到服务器
	线程2 ：接收服务器发来的数据并显示到界面上
*/

SOCKET clientSocket;
void recvServerAndShow();
DataBaseClient dataBaseClient;

int main()
{
	//1 确定协议
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		printf("确定协议版本失败:%d\n", GetLastError());
		return -1;
	}
	printf("确定协议版本成功！\n");

	//2 创建socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == clientSocket) {
		printf("创建socket失败：%d\n", GetLastError());
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	printf("创建socket成功！ \n");

	//3 获取到服务器协议地址簇
	SOCKADDR_IN sAddr = { 0 };
	sAddr.sin_family = AF_INET;// 必须和socket函数第一个参数一致
	sAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//ip地址是一个整数  "" 字符串 字符串转整数
	sAddr.sin_port = htons(9527);//小端转大端
	// 0 - 65535  5000以上   20000以下比较稳妥

	//4 连接服务器
	int r = connect(clientSocket, (sockaddr*)&sAddr, sizeof sAddr);
	if (-1 == r) {
		printf("连接服务器失败：%d\n", GetLastError());
		// 断开连接
		closesocket(clientSocket);
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	cout << "连接服务器成功！" << endl;
	cout << "请选择：1.注册   2.登录" << endl;
	int signInOrSignOut = 0;
	cin >> signInOrSignOut;

	// 注册
	char recvBuff[1024];
	memset(recvBuff, 0, sizeof(recvBuff));
	while (signInOrSignOut == 1) {
		SignIn signIn = SignIn();
		signIn.setinformation();
		Msg massage;
		//设置注册还是登录命令
		massage.signInOrSignOut = 1;

		// 设置用户名
		strcpy(massage.userName, signIn.getUsers().c_str());

		// 设置用户密码
		strcpy(massage.password, signIn.getPassword().c_str());

		// 设置游戏区
		massage.zone = signIn.getZone();

		//发送
		send(clientSocket, (char*)&massage, sizeof(massage), NULL);

		cout << massage.userName << massage.password << massage.zone << endl;

		int r;
		r = recv(clientSocket, recvBuff, 1023, NULL);

		if (r > 0) {
			recvBuff[r] = 0;
			printf(">> %s\n", recvBuff);
			if (strcmp(recvBuff, "注册成功！") == 0) {
				signInOrSignOut = 2;
			}
		}
		else {
			cout << "注册失败,请重新输入！" << endl;
		}
	}

	// 登录
	Msg massage;
	while (signInOrSignOut == 2) {
		SignUp signUp = SignUp();
		signUp.Login();
		memcpy(&massage, &signUp.getMsg(), sizeof(signUp.getMsg()));
		
		// 发送
		send(clientSocket, (char*)&massage, sizeof(massage), NULL);

		memset(recvBuff, 0, sizeof(recvBuff));

		int r;
		r = recv(clientSocket, recvBuff, 1023, NULL);

		if (r > 0) {
			recvBuff[r] = 0;
			printf(">> %s\n", recvBuff);
			if (strcmp(recvBuff, "登录成功！") == 0) {
				signInOrSignOut = 0;
			}
		}
		else {
			cout << "登录失败，请重新登录！" << endl;
		}
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvServerAndShow,
		NULL, NULL, NULL);

	//5 通信
	Session clientSession;
	int clientWork = 1;
	while (clientWork) {
		strcpy(clientSession.userName, massage.userName);
		clientSession.zone = massage.zone;
		cout << "请输入你想要发送的信息:" << endl;
		cin >> clientSession.clientChat;

		if (strcmp(clientSession.clientChat, "查询在线用户") == 0) {
			dataBaseClient.selectOnlineClient();
		} else {
			send(clientSocket, (char *)&clientSession, sizeof(clientSession), NULL);

			// 客户输出exit,退出
			if (strcmp(clientSession.clientChat, "EXIT") == 0) {
				clientWork = 0;
			}
		}
	}

	//8 断开连接
	closesocket(clientSocket);
	//9 清理协议信息
	WSACleanup();
}

void recvServerAndShow() {
	char buff[1024];
	Session clientSession;
	int r;
	while (1) {
		memset(buff, 0, sizeof(buff));
		memset(&clientSession, 0, sizeof(clientSession));
		r = recv(clientSocket, buff, 1023, NULL);
		if (r > 0) {
			memcpy(&clientSession, buff, sizeof(clientSession));
			cout << clientSession.userName << ">>" << clientSession.clientChat << endl;
		}
	}
}


