#include "server.h"


int main()
{
	//1 确定协议
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		cout << "确定协议版本失败:" << GetLastError() << endl;
		return -1;
	}
	cout << "确定协议版本成功！" << endl;

	//2 创建socket
	SOCKET sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sSocket) {
		cout << "创建socket失败：" << GetLastError() << endl;
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	cout << "创建socket成功！" << endl;

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
		cout << "绑定失败：" << GetLastError() << endl;
		// 断开连接
		closesocket(sSocket);
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	cout << "绑定成功！" << endl;

	//5 监听
	r = listen(sSocket, 10);
	if (-1 == r) {
		cout << "监听失败：" << GetLastError() << endl;
		// 断开连接
		closesocket(sSocket);
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	cout << "监听成功！" << endl;


	//6 接受客户端连接
	SOCKADDR_IN cAddr = { 0 };
	int cAddrLen = sizeof cAddr;
	for (int i = 0; i < 1024; i++) {
		cSocket[i] = accept(sSocket, (sockaddr*)&cAddr, &cAddrLen);
		if (SOCKET_ERROR == cSocket[i]) {
			cout << "网络奔溃：" << GetLastError() << endl;
			// 断开连接
			closesocket(sSocket);
			// 清理协议信息
			WSACleanup();
			return -1;
		}
		cout << "有客户端连接上服务器了：" << inet_ntoa(cAddr.sin_addr) << endl;

		char recvBuff[1024];
		Msg recvMassage;
		Session sendSession;
		memset(&recvBuff, 0, sizeof(recvBuff));

		if (recv(cSocket[i], recvBuff, 1023, NULL)) {
			// 清空结构体
			memset(&recvMassage, 0, sizeof(recvMassage));

			// 复制recvBuff到recvMassage
			memcpy(&recvMassage, recvBuff, sizeof(recvMassage));

			while (recvMassage.signInOrSignOut == 1) {
				DataBase database;

				int flag = database.insertDataBase(recvMassage.userName, to_string(recvMassage.zone), recvMassage.password);
				if (flag) {
					send(cSocket[i], "注册成功！", sizeof("注册成功！"), 0);

					// 清空结构体
					memset(&recvMassage, 0, sizeof(recvMassage));
					recv(cSocket[i], (char*)&recvMassage, sizeof(recvMassage), NULL);
				}
				else if (database.selectUserWhetherSignIn(recvMassage.userName)) {
					send(cSocket[i], "该名称已被注册！", sizeof("该名称已被注册！"), 0);

					// 清空结构体
					memset(&recvMassage, 0, sizeof(recvMassage));
					recv(cSocket[i], (char*)&recvMassage, sizeof(recvMassage), NULL);

				}

				else {
					send(cSocket[i], "注册失败！", sizeof("注册失败！"), 0);
					closesocket(cSocket[i]);
					break;
				}
			}

			while (recvMassage.signInOrSignOut == 2) {
				DataBase database;
				
				int flag = database.selectDataBase(recvMassage.userName, to_string(recvMassage.zone), recvMassage.password);
				if (flag == 0) {
					send(cSocket[i], "名称、大区或密码输入错误，请重新输入！", sizeof("名称、大区或密码输入错误，请重新输入！"), 0);
					// 清空结构体
					memset(&recvMassage, 0, sizeof(recvMassage));
					recv(cSocket[i], (char*)&recvMassage, sizeof(recvMassage), NULL);
				}
				else if (flag && database.updateDataBase(recvMassage.userName, "1")) {
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
					break;
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

				dataBase.updateDataBase(serverSession.userName, "0");

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

			// 查询在线用户
			else if (strcmp(serverSession.clientChat, "查询在线玩家列表") == 0) {
				string onlineClient = dataBase.selectOnlineClient();
				strcpy(serverSession.clientChat, onlineClient.c_str());

				send(cSocket[idx], (char*)&serverSession, sizeof(serverSession), 0);

			}

			// 查询玩家信息
			else if (serverSession.clientChat[0] == '$') {
				strcpy(serverSession.clientChat, serverSession.clientChat + 1);
				string userName = serverSession.clientChat;
				string userInfo = dataBase.selectUserInf(userName);
				memset(serverSession.clientChat, 0, sizeof(serverSession.clientChat));
				strcpy(serverSession.clientChat, userInfo.c_str());

				send(cSocket[idx], (char*)&serverSession, sizeof(serverSession), 0);
			}

			// 设置黑名单
			else if (serverSession.clientChat[0] == '^') {
				string content = serverSession.clientChat;
				string blackListUser = content.substr(1, content.length() - 2);
				string inOrOut = content.substr(content.length() - 1, 1);
				dataBase.updateBlackList(blackListUser, inOrOut);
			}


			// 判断用户是否在黑名单上
			else if (dataBase.selectBlackList(serverSession.userName) == 1) {

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



