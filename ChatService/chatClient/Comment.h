#ifndef _COMMENT_H_
#define _COMMENT_H_

#include <string>
using namespace std;


//������Ϣ�ṹ���ڷ���˺Ϳͻ���֮�䴫��
struct Msg
{
	int signInOrSignOut;
	char userName[20];
	char password[20];
	int zone;

};

struct Session 
{
	char userName[20];
	char clientChat[200];
	int zone;
};
#endif // _COMMENT_H_

