﻿#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#include <windows.h>

#include "Comment.h"
#include "DataBase.h"

SOCKET cSocket[1024];
int clientCount = 0;

void communicat(int idx);

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
	SOCKET sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sSocket) {
		printf("创建socket失败：%d\n", GetLastError());
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	printf("创建socket成功！ \n");

	//3 服务器协议地址簇
	SOCKADDR_IN sAddr = { 0 };
	sAddr.sin_family = AF_INET;// 必须和socket函数第一个参数一致
	sAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//ip地址是一个整数  "" 字符串 字符串转整数
	sAddr.sin_port = htons(9527);//小端转大端
	// 0 - 65535  5000以上   20000以下比较稳妥

	//4 绑定
	int r = bind(sSocket, (sockaddr*)&sAddr, sizeof sAddr);
	if (-1 == r) {
		printf("绑定失败：%d\n", GetLastError());
		// 断开连接
		closesocket(sSocket);
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	printf("绑定成功！ \n");

	//5 监听
	r = listen(sSocket, 10);
	if (-1 == r) {
		printf("监听失败：%d\n", GetLastError());
		// 断开连接
		closesocket(sSocket);
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	printf("监听成功！ \n");


	//6 接受客户端连接
	SOCKADDR_IN cAddr = { 0 };
	int cAddrLen = sizeof cAddr;
	for (int i = 0; i < 1024; i++) {
		cSocket[i] = accept(sSocket, (sockaddr*)&cAddr, &cAddrLen);
		if (SOCKET_ERROR == cSocket[i]) {
			printf("网络奔溃：%d\n", GetLastError());
			// 断开连接
			closesocket(sSocket);
			// 清理协议信息
			WSACleanup();
			return -1;
		}
		printf("有客户端连接上服务器了：%s\n", inet_ntoa(cAddr.sin_addr));
		clientCount++;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)communicat, (LPVOID)i, NULL, NULL);
	}



	//8 断开连接
	closesocket(sSocket);
	//9 清理协议信息
	WSACleanup();
}

void communicat(int idx) {
	//7 通信
	char recvBuff[1024];
	Msg recvMassage;

	memset(&recvBuff, 0, sizeof(recvBuff));

	int r;
	while (1) {
		r = recv(cSocket[idx], recvBuff, 1023, NULL);

		if (r > 0) {
			memset(&recvMassage, 0, sizeof(recvMassage));//清空结构体
			memcpy(&recvMassage, recvBuff, sizeof(recvMassage));
			recvBuff[r] = 0;
			cout << recvMassage.signInOrSignOut << recvMassage.zone << endl;


			// 服务器完成注册任务
			if (recvMassage.signInOrSignOut == 1) {
				DataBase database;
				int flag = database.insertDataBase(recvMassage.userName, to_string(recvMassage.zone), recvMassage.password);
				if (flag) {
					send(cSocket[idx], "注册成功！", sizeof("注册成功！"), 0);
				}
				else {
					send(cSocket[idx], "注册失败！", sizeof("注册失败！"), 0);
				}

			}

			// 服务器完成登录任务
			if (recvMassage.signInOrSignOut == 2) {
				DataBase database;
				int flag = database.selectDataBase(recvMassage.userName, to_string(recvMassage.zone), recvMassage.password);
				if (flag && database.updateDataBase(recvMassage.userName)) {
					send(cSocket[idx], "登录成功！", sizeof("登录成功！"), 0);
				}
				else {
					send(cSocket[idx], "登录失败！", sizeof("登录失败！"), 0);
				}
			}

			// 广播 发送给所有客户端
			for (int i = 0; i < clientCount; i++) {
				send(cSocket[i], recvBuff, r, NULL);
			}
		}
	}
}


