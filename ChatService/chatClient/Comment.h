#ifndef _COMMENT_H_
#define _COMMENT_H_

#include <string>
using namespace std;

// Ĭ�Ϸ�������IP��ַ
#define SERVER_IP "127.0.0.1"

// �������˿ں�
#define SERVER_PORT 8888

// int epoll_create(int size)�е�size
// Ϊepoll֧�ֵ��������
#define EPOLL_SIZE 5000

// ��������С65535
#define BUF_SIZE 0xFFFF

// ���û���¼��Ļ�ӭ��Ϣ
#define SERVER_WELCOME "Welcome you join to the chat room! Your chat ID is: Client #%d"

// �����û��յ���Ϣ��ǰ׺
#define SERVER_MESSAGE "ClientID %d say >> %s"
#define SERVER_PRIVATE_MESSAGE "Client %d say to you privately >> %s"
#define SERVER_PRIVATE_ERROR_MESSAGE "Client %d is not in the chat room yet~"
// �˳�ϵͳ
#define EXIT "EXIT"

// ����������������Ψһ�Ŀͻ�
#define CAUTION "There is only one int the char room!"


//������Ϣ�ṹ���ڷ���˺Ϳͻ���֮�䴫��
struct Msg
{
	int signInOrSignOut;
	string userName;
	string password;
	int zone;

};
#endif // _COMMENT_H_

