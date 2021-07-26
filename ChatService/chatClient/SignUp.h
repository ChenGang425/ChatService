#include<iostream>
#include<string>
#include "comment.h"
using namespace std;


class SignUp
{
private:
	//string users;//用户名
	//string password;//密码
	//int zone;// 游戏大区
	Msg massage;

public:
	SignUp();

	~SignUp();//析构函数

	void deleteusers();

	void Login();
	Msg getMsg();

};
