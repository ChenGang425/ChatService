#include "Client.h"

// ���ӷ�����
int Client::connectServer() {
	//1 ȷ��Э��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		cout << "ȷ��Э��汾ʧ��: " << GetLastError() << endl;
		return -1;
	}
	cout << "ȷ��Э��汾�ɹ���" << endl;

	//2 ����socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == clientSocket) {
		cout << "����socketʧ�ܣ�" << GetLastError() << endl;
		// ����Э����Ϣ
		WSACleanup();
		return -1;
	}
	cout << "����socket�ɹ���" << endl;

	//3 ��ȡ��������Э���ַ��
	SOCKADDR_IN sAddr = { 0 };
	sAddr.sin_family = AF_INET;// �����socket������һ������һ��
	sAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//ip��ַ��һ������  "" �ַ��� �ַ���ת����
	sAddr.sin_port = htons(9527);//С��ת���
	// 0 - 65535  5000����   20000���±Ƚ�����

	//4 ���ӷ�����
	int r = connect(clientSocket, (sockaddr*)&sAddr, sizeof sAddr);
	if (-1 == r) {
		cout << "���ӷ�����ʧ�ܣ�" << GetLastError() << endl;
		// �Ͽ�����
		closesocket(clientSocket);
		// ����Э����Ϣ
		WSACleanup();
		return -1;
	}
	cout << "���ӷ������ɹ���" << endl;
	return 0;
}


// �û�ע��
void Client::userSignIn() {
	// ע��
	memset(recvBuff, 0, sizeof(recvBuff));
	memset(&massage, 0, sizeof(massage));
	while (signInOrSignOut == 1) {
		SignIn signIn = SignIn();
		signIn.setinformation();

		//����ע�ỹ�ǵ�¼����
		massage.signInOrSignOut = 1;

		// �����û���
		strcpy(massage.userName, signIn.getUsers().c_str());

		// �����û�����
		strcpy(massage.password, signIn.getPassword().c_str());

		// ������Ϸ��
		massage.zone = signIn.getZone();

		//����
		send(clientSocket, (char*)&massage, sizeof(massage), NULL);

		cout << massage.userName << massage.password << massage.zone << endl;

		int r;
		r = recv(clientSocket, recvBuff, 1023, NULL);

		if (r > 0) {
			recvBuff[r] = 0;
			cout << ">>" << recvBuff << endl;
			if (strcmp(recvBuff, "ע��ɹ���") == 0) {
				signInOrSignOut = 2;
			}
		}
		else {
			cout << "ע��ʧ��,���������룡" << endl;
		}
	}
}


// �û���¼
void Client::userSignUp() {
	// ��¼
	memset(recvBuff, 0, sizeof(recvBuff));
	memset(&massage, 0, sizeof(massage));
	while (signInOrSignOut == 2) {
		SignUp signUp = SignUp();
		signUp.Login();
		memcpy(&massage, &signUp.getMsg(), sizeof(signUp.getMsg()));

		// ����
		send(clientSocket, (char*)&massage, sizeof(massage), NULL);

		int r;
		r = recv(clientSocket, recvBuff, 1023, NULL);

		if (r > 0) {
			recvBuff[r] = 0;
			cout << ">> " << recvBuff << endl;
			if (strcmp(recvBuff, "��¼�ɹ���") == 0) {
				signInOrSignOut = 0;
			}
		}
		else {
			cout << "��¼ʧ�ܣ������µ�¼��" << endl;
		}
	}
}


// �û�ͨ��
void Client::communication() {
	int clientWork = 1;
	while (clientWork) {
		memset(&clientSession, 0, sizeof(clientSession));
		strcpy(clientSession.userName, massage.userName);
		clientSession.zone = massage.zone;
		cout << "����������Ҫ���͵���Ϣ:" << endl;
		cout << "��Ҫ˽�������룺/ + ˽�ĺ��� + ˽������" << endl;
		cout << "��Ҫ�����������룺# + ����" << endl;
		cout << "���ѯ�����û������룺��ѯ�����û�" << endl;
		cout << "���ѯ�����Ϣ�����룺��ѯ�����Ϣ" << endl;
		if (strcmp(clientSession.userName, "chengang") == 0) {
			cout << "���������������룺���ú�����" << endl;
		}
		cin >> clientSession.clientChat;

		if (strcmp(clientSession.clientChat, "��ѯ�����û�") == 0) {
			dataBaseClient.selectOnlineClient();
		}

		else if (strcmp(clientSession.clientChat, "��ѯ�����Ϣ") == 0) {
			string searchUserInf;
			cout << "��������Ҫ��ѯ��������ƣ�" << endl;
			cin >> searchUserInf;
			dataBaseClient.selectUserInf(searchUserInf);
		}
		else if (strcmp(clientSession.clientChat, "���ú�����") == 0 && 
			strcmp(clientSession.userName, "chengang") == 0) {
			string blackListUser;
			string inOrOut;
			cout << "��Ҫ����λ��������������������" << endl;
			cin >> blackListUser;
			cout << "��Ҫ�������뻹�Ǻ���������������������" << endl;
			cout << "0.����   " << "1. ����" << endl;
			cin >> inOrOut;
			dataBaseClient.updateBlackList(blackListUser, inOrOut);
		}
		else {
			send(clientSocket, (char *)&clientSession, sizeof(clientSession), NULL);

			// �ͻ����exit,�˳�
			if (strcmp(clientSession.clientChat, "EXIT") == 0) {
				clientWork = 0;
			}
		}
	}
}


// �Ͽ�����
void Client::disconnect() {
	//8 �Ͽ�����
	closesocket(clientSocket);
	//9 ����Э����Ϣ
	WSACleanup();
}


// ����û��׽���
SOCKET Client::getClientSocket() {
	return clientSocket;
}


// �û�ѡ��ע�ỹ�ǵ�¼
void Client::userSelectSignInOrSignUp() {
	cout << "��ѡ��1.ע��   2.��¼" << endl;
	cin >> signInOrSignOut;
}


