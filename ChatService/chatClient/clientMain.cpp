#include "Client.h"

void recvServerAndShow();

Client client;
int main() {

	// 连接服务器
	client.connectServer();

	// 用户决定是注册还是登录
	client.userSelectSignInOrSignUp();

	// 注册操作
	client.userSignIn();

	// 登录操作
	client.userSignUp();

	// 创建线程，用来接收消息
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvServerAndShow,
		NULL, NULL, NULL);

	// 通信
	client.communication();

	// 断开连接
	client.disconnect();
}

// 用户接收信息
void recvServerAndShow() {
	char buff[1024];
	Session clientSession;
	int r;
	while (1) {
		memset(buff, 0, sizeof(buff));
		memset(&clientSession, 0, sizeof(clientSession));
		r = recv(client.getClientSocket(), buff, 1023, NULL);
		if (r > 0) {
			memcpy(&clientSession, buff, sizeof(clientSession));
			cout << clientSession.userName << ">>" << clientSession.clientChat << endl;
		}
	}
}

