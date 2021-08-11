#include "Client.h"

// 连接服务器
int Client::connectServer() {
	//1 确定协议
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		cout << "确定协议版本失败: " << GetLastError() << endl;
		return -1;
	}
	cout << "确定协议版本成功！" << endl;

	//2 创建socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == clientSocket) {
		cout << "创建socket失败：" << GetLastError() << endl;
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	cout << "创建socket成功！" << endl;

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
		cout << "连接服务器失败：" << GetLastError() << endl;
		// 断开连接
		closesocket(clientSocket);
		// 清理协议信息
		WSACleanup();
		return -1;
	}
	cout << "连接服务器成功！" << endl;
	return 0;
}


// 用户注册
void Client::userSignIn() {
	// 注册
	memset(recvBuff, 0, sizeof(recvBuff));
	memset(&massage, 0, sizeof(massage));
	while (signInOrSignOut == 1) {
		SignIn signIn = SignIn();
		signIn.setinformation();

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
			cout << ">>" << recvBuff << endl;
			if (strcmp(recvBuff, "注册成功！") == 0) {
				signInOrSignOut = 2;
			}
		}
		else {
			cout << "注册失败,请重新输入！" << endl;
		}
	}
}


// 用户登录
void Client::userSignUp() {
	// 登录
	memset(recvBuff, 0, sizeof(recvBuff));
	memset(&massage, 0, sizeof(massage));
	while (signInOrSignOut == 2) {
		SignUp signUp = SignUp();
		signUp.Login();
		memcpy(&massage, &signUp.getMsg(), sizeof(signUp.getMsg()));

		// 发送
		send(clientSocket, (char*)&massage, sizeof(massage), NULL);

		int r;
		r = recv(clientSocket, recvBuff, 1023, NULL);

		if (r > 0) {
			recvBuff[r] = 0;
			cout << ">> " << recvBuff << endl;
			if (strcmp(recvBuff, "登录成功！") == 0) {
				signInOrSignOut = 0;
			}
		}
		else {
			cout << "登录失败，请重新登录！" << endl;
		}
	}
}


// 用户通信
void Client::communication() {
	int clientWork = 1;
	while (clientWork) {
		memset(&clientSession, 0, sizeof(clientSession));
		strcpy(clientSession.userName, massage.userName);
		clientSession.zone = massage.zone;
		cout << "请输入你想要发送的信息:" << endl;
		cout << "想要私聊请输入：/ + 私聊号码 + 私聊内容" << endl;
		cout << "想要发大区请输入：# + 内容" << endl;
		cout << "想查询在线用户请输入：查询在线用户" << endl;
		cout << "想查询玩家信息请输入：查询玩家信息" << endl;
		if (strcmp(clientSession.userName, "chengang") == 0) {
			cout << "想管理黑名单请输入：设置黑名单" << endl;
		}
		cin >> clientSession.clientChat;

		if (strcmp(clientSession.clientChat, "查询在线用户") == 0) {
			dataBaseClient.selectOnlineClient();
		}

		else if (strcmp(clientSession.clientChat, "查询玩家信息") == 0) {
			string searchUserInf;
			cout << "请输入想要查询的玩家名称：" << endl;
			cin >> searchUserInf;
			dataBaseClient.selectUserInf(searchUserInf);
		}
		else if (strcmp(clientSession.clientChat, "设置黑名单") == 0 && 
			strcmp(clientSession.userName, "chengang") == 0) {
			string blackListUser;
			string inOrOut;
			cout << "想要将哪位玩家拉入或拉出黑名单：" << endl;
			cin >> blackListUser;
			cout << "想要将他拉入还是黑名单还是拉出黑名单：" << endl;
			cout << "0.拉出   " << "1. 拉入" << endl;
			cin >> inOrOut;
			dataBaseClient.updateBlackList(blackListUser, inOrOut);
		}
		else {
			send(clientSocket, (char *)&clientSession, sizeof(clientSession), NULL);

			// 客户输出exit,退出
			if (strcmp(clientSession.clientChat, "EXIT") == 0) {
				clientWork = 0;
			}
		}
	}
}


// 断开连接
void Client::disconnect() {
	//8 断开连接
	closesocket(clientSocket);
	//9 清理协议信息
	WSACleanup();
}


// 获得用户套接字
SOCKET Client::getClientSocket() {
	return clientSocket;
}


// 用户选择注册还是登录
void Client::userSelectSignInOrSignUp() {
	cout << "请选择：1.注册   2.登录" << endl;
	cin >> signInOrSignOut;
}


