#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#include <windows.h>

#include "SignIn.h"
#include "SignUp.h"
#include "Comment.h"

using namespace std;

/*
	�����߳�
	����
	�߳�1 �������û����벢���͵�������
	�߳�2 �����շ��������������ݲ���ʾ��������
*/

SOCKET clientSocket;
//void recvServerAndShow();

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
	printf("���ӷ������ɹ���\n");
	printf("��ѡ��1.ע��   2.��¼\n");
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
			if (strcmp(recvBuff, "ע��ɹ���") > 0) {
				signInOrSignOut = 2;
			}
		}
		else {
			printf("ע��ʧ�ܣ�");
			signInOrSignOut = 0;
		}
	}

	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvServerAndShow,
	//	NULL, NULL, NULL);

	////5 ͨ��

	//char buff[1024];
	//while (1) {
	//	memset(buff, 0, 1024);//���
	//	printf("������Ҫ���͸�����������Ϣ��");
	//	scanf("%s", buff);

	//	send(clientSocket, buff, strlen(buff), NULL);
	//}


	////8 �Ͽ�����
	//closesocket(clientSocket);
	////9 ����Э����Ϣ
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


