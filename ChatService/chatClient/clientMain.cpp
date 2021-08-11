#include "Client.h"

void recvServerAndShow();

Client client;
int main() {

	// ���ӷ�����
	client.connectServer();

	// �û�������ע�ỹ�ǵ�¼
	client.userSelectSignInOrSignUp();

	// ע�����
	client.userSignIn();

	// ��¼����
	client.userSignUp();

	// �����̣߳�����������Ϣ
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvServerAndShow,
		NULL, NULL, NULL);

	// ͨ��
	client.communication();

	// �Ͽ�����
	client.disconnect();
}

// �û�������Ϣ
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

