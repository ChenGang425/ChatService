#include<iostream>
#include<string>
#include "comment.h"
using namespace std;


class SignUp
{
private:
	//string users;//�û���
	//string password;//����
	//int zone;// ��Ϸ����
	Msg massage;

public:
	SignUp();

	~SignUp();//��������

	void deleteusers();

	void Login();
	Msg getMsg();

};
