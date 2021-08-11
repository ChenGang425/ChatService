#include "server.h"


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

		char recvBuff[1024];
		Msg recvMassage;
		Session sendSession;
		memset(&recvBuff, 0, sizeof(recvBuff));

		if (recv(cSocket[i], recvBuff, 1023, NULL)) {
			// 清空结构体
			memset(&recvMassage, 0, sizeof(recvMassage));

			// 复制recvBuff到recvMassage
			memcpy(&recvMassage, recvBuff, sizeof(recvMassage));

			if (recvMassage.signInOrSignOut == 1) {
				DataBase database;
				int flag = database.insertDataBase(recvMassage.userName, to_string(recvMassage.zone), recvMassage.password);
				if (flag) {
					send(cSocket[i], "注册成功！", sizeof("注册成功！"), 0);
				}
				else {
					send(cSocket[i], "注册失败！", sizeof("注册失败！"), 0);
					closesocket(cSocket[i]);
				}
			}

			if (recvMassage.signInOrSignOut == 2) {
				DataBase database;
				int flag = database.selectDataBase(recvMassage.userName, to_string(recvMassage.zone), recvMassage.password);
				if (flag && database.updateDataBase(recvMassage.userName, "1")) {
					send(cSocket[i], "登录成功！", sizeof("登录成功！"), 0);

					//通知所有客户端有新客户进来了
					string newClientStr = "大家好，我进聊天室了，私聊号码为:" + to_string(i);
					strcpy(sendSession.clientChat, newClientStr.c_str());
					strcpy(sendSession.userName, recvMassage.userName);
					for (list<SOCKET>::const_iterator it = clientCount.begin(); it != clientCount.end(); it++) {
						send(*it, (char*)&sendSession, sizeof(sendSession), 0);
					}

					// 在全服添加该用户
					clientCount.push_back(cSocket[i]);
					// 在全区添加该用户
					if (recvMassage.zone == 1) {
						oneZoneClient.push_back(cSocket[i]);
					}
					else {
						twoZoneClient.push_back(cSocket[i]);
					}

					CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)communicat, (LPVOID)i, NULL, NULL);
				}
				else {
					send(cSocket[i], "登录失败！", sizeof("登录失败！"), 0);
					closesocket(cSocket[i]);
				}
			}
		}
	}

	//8 断开连接
	closesocket(sSocket);
	//9 清理协议信息
	WSACleanup();
}

void communicat(int idx) {

	//7 通信
	char recvBuff[1024];
	Session serverSession;
	memset(&recvBuff, 0, sizeof(recvBuff));
	int r;
	while (1) {
		r = recv(cSocket[idx], recvBuff, 1023, NULL);

		if (r > 0) {
			memset(&serverSession, 0, sizeof(serverSession));//清空结构体
			memcpy(&serverSession, recvBuff, sizeof(serverSession));
			DataBase dataBase;

			//判断用户是否要退出
			if (strcmp(serverSession.clientChat, "EXIT") == 0) {
				DataBase database;
				database.updateDataBase(serverSession.userName, "0");

				// 广播 发送给所有客户端该用户下线通知
				string offlineStr(serverSession.userName);
				offlineStr = offlineStr + "下线了！";
				strcpy(serverSession.clientChat, offlineStr.c_str());

				// 在全服中删除该用户
				clientCount.remove(cSocket[idx]);
				// 在大区中删除该用户
				if (serverSession.zone == 1) {
					oneZoneClient.remove(cSocket[idx]);
				}
				else {
					twoZoneClient.remove(cSocket[idx]);
				}
				for (list<SOCKET>::const_iterator it = clientCount.begin(); it != clientCount.end(); it++) {
					send(*it, (char*)&serverSession, sizeof(serverSession), 0);
				}
			}

			// 判断用户是否在黑名单上
			if (dataBase.selectBlackList(serverSession.userName) == 1) {

				// 私聊
				if (serverSession.clientChat[0] == '/') {
					send(cSocket[serverSession.clientChat[1] - '0'], (char*)&serverSession, sizeof(serverSession), 0);
				}

				// 广播 大区
				else if (serverSession.clientChat[0] == '#') {
					if (serverSession.zone == 1) {
						for (list<SOCKET>::const_iterator it = oneZoneClient.begin(); it != oneZoneClient.end(); it++) {
							send(*it, (char*)&serverSession, sizeof(serverSession), 0);
						}
					}
					else {
						for (list<SOCKET>::const_iterator it = twoZoneClient.begin(); it != twoZoneClient.end(); it++) {
							send(*it, (char*)&serverSession, sizeof(serverSession), 0);
						}
					}

				}
				// 广播 全服
				else {
					for (list<SOCKET>::const_iterator it = clientCount.begin(); it != clientCount.end(); it++) {
						send(*it, (char*)&serverSession, sizeof(serverSession), 0);
					}
				}
			}
		}
	}
}





















/*
void clientSignIn(int idx) {
	// 服务器完成注册任务
	char recvBuff[1024];
	Msg recvMassage;

	memset(&recvBuff, 0, sizeof(recvBuff));

	if (recv(cSocket[idx], recvBuff, 1023, NULL)) {
		memset(&recvMassage, 0, sizeof(recvMassage));//清空结构体
		memcpy(&recvMassage, recvBuff, sizeof(recvMassage));
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
	}

}

void clientSignUp(int idx) {
	// 服务器完成登录任务
	char recvBuff[1024];
	Msg recvMassage;

	memset(&recvBuff, 0, sizeof(recvBuff));

	int r;
	r = recv(cSocket[idx], recvBuff, 1023, NULL);

	if (r > 0) {
		memset(&recvMassage, 0, sizeof(recvMassage));//清空结构体
		memcpy(&recvMassage, recvBuff, sizeof(recvMassage));
		if (recvMassage.signInOrSignOut == 2) {
			DataBase database;
			int flag = database.selectDataBase(recvMassage.userName, to_string(recvMassage.zone), recvMassage.password);
			if (flag && database.updateDataBase(recvMassage.userName, "1")) {
				send(cSocket[idx], "登录成功！", sizeof("登录成功！"), 0);
			}
			else {
				send(cSocket[idx], "登录失败！", sizeof("登录失败！"), 0);
			}
		}
	}
}
*/


