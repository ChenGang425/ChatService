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

class Client {
private:

	// �û�ѡ��ע�ỹ�ǵ�¼
	int signInOrSignOut = 0;

	// ���ջ���
	char recvBuff[1024];

	// ��¼��ע��ʹ�õ���Ϣ
	Msg massage;

	// �û����͵���Ϣ
	Session clientSession;

	// �û�socket
	SOCKET clientSocket;

public:

	// ���ӷ�����
	int connectServer();

	// �û�ע��
	void userSignIn();

	// �û���¼
	void userSignUp();

	// �û�ͨ��
	void communication();

	// �û��Ͽ�����
	void disconnect();

	// ����׽���
	SOCKET getClientSocket();

	// �û�ѡ��ע�ỹ�ǵ�¼
	void userSelectSignInOrSignUp();
};