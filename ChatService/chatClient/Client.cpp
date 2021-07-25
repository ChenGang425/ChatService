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

SOCKET clientSocket;
//void recvServerAndShow();

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
	printf("连接服务器成功！\n");
	printf("请选择：1.注册   2.登录\n");
	int signInOrSignOut = 0;
	cin >> signInOrSignOut;

	while (signInOrSignOut == 1) {
		SignIn signIn = SignIn();
		signIn.setinformation();
		Msg massage;
		massage.signInOrSignOut = 1;
		massage.userName = signIn.getUsers();
		massage.password = signIn.getPassword();
		massage.zone = signIn.getZone();

		char sendBuff[500];
		memset(sendBuff, 0, sizeof(sendBuff));
		memcpy(sendBuff, &massage, sizeof(massage));
		send(clientSocket, sendBuff, strlen(sendBuff), NULL);

		char recvBuff[1024];
		int r;
		r = recv(clientSocket, recvBuff, 1023, NULL);

		if (r > 0) {
			recvBuff[r] = 0;
			printf(">> %s\n", recvBuff);
			if (strcmp(recvBuff, "注册成功！") > 0) {
				signInOrSignOut = 2;
			}
		}
		else {
			printf("注册失败！");
			signInOrSignOut = 0;
		}
	}

	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvServerAndShow,
	//	NULL, NULL, NULL);

	////5 通信

	//char buff[1024];
	//while (1) {
	//	memset(buff, 0, 1024);//清空
	//	printf("请输入要发送给服务器的信息：");
	//	scanf("%s", buff);

	//	send(clientSocket, buff, strlen(buff), NULL);
	//}


	////8 断开连接
	//closesocket(clientSocket);
	////9 清理协议信息
	//WSACleanup();
}

//void recvServerAndShow() {
//	char buff[1024];
//	int r;
//	while (1) {
//		r = recv(clientSocket, buff, 1023, NULL);
//		if (r > 0) {
//			buff[r] = 0;
//			printf(">> %s\n", buff);
//		}
//	}
//}


