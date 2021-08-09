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
	�����߳�
	����
	�߳�1 �������û����벢���͵�������
	�߳�2 �����շ��������������ݲ���ʾ��������
*/

SOCKET clientSocket;
void recvServerAndShow();
DataBaseClient dataBaseClient;

int main()
{
	//1 ȷ��Э��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		printf("ȷ��Э��汾ʧ��:%d\n", GetLastError());
		return -1;
	}
	printf("ȷ��Э��汾�ɹ���\n");

	//2 ����socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == clientSocket) {
		printf("����socketʧ�ܣ�%d\n", GetLastError());
		// ����Э����Ϣ
		WSACleanup();
		return -1;
	}
	printf("����socket�ɹ��� \n");

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
		printf("���ӷ�����ʧ�ܣ�%d\n", GetLastError());
		// �Ͽ�����
		closesocket(clientSocket);
		// ����Э����Ϣ
		WSACleanup();
		return -1;
	}
	cout << "���ӷ������ɹ���" << endl;
	cout << "��ѡ��1.ע��   2.��¼" << endl;
	int signInOrSignOut = 0;
	cin >> signInOrSignOut;

	// ע��
	char recvBuff[1024];
	memset(recvBuff, 0, sizeof(recvBuff));
	while (signInOrSignOut == 1) {
		SignIn signIn = SignIn();
		signIn.setinformation();
		Msg massage;
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
			printf(">> %s\n", recvBuff);
			if (strcmp(recvBuff, "ע��ɹ���") == 0) {
				signInOrSignOut = 2;
			}
		}
		else {
			cout << "ע��ʧ��,���������룡" << endl;
		}
	}

	// ��¼
	Msg massage;
	while (signInOrSignOut == 2) {
		SignUp signUp = SignUp();
		signUp.Login();
		memcpy(&massage, &signUp.getMsg(), sizeof(signUp.getMsg()));
		
		// ����
		send(clientSocket, (char*)&massage, sizeof(massage), NULL);

		memset(recvBuff, 0, sizeof(recvBuff));

		int r;
		r = recv(clientSocket, recvBuff, 1023, NULL);

		if (r > 0) {
			recvBuff[r] = 0;
			printf(">> %s\n", recvBuff);
			if (strcmp(recvBuff, "��¼�ɹ���") == 0) {
				signInOrSignOut = 0;
			}
		}
		else {
			cout << "��¼ʧ�ܣ������µ�¼��" << endl;
		}
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvServerAndShow,
		NULL, NULL, NULL);

	//5 ͨ��
	Session clientSession;
	int clientWork = 1;
	while (clientWork) {
		strcpy(clientSession.userName, massage.userName);
		clientSession.zone = massage.zone;
		cout << "����������Ҫ���͵���Ϣ:" << endl;
		cin >> clientSession.clientChat;

		if (strcmp(clientSession.clientChat, "��ѯ�����û�") == 0) {
			dataBaseClient.selectOnlineClient();
		} else {
			send(clientSocket, (char *)&clientSession, sizeof(clientSession), NULL);

			// �ͻ����exit,�˳�
			if (strcmp(clientSession.clientChat, "EXIT") == 0) {
				clientWork = 0;
			}
		}
	}

	//8 �Ͽ�����
	closesocket(clientSocket);
	//9 ����Э����Ϣ
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


