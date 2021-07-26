#include<iostream>
#include<string>
using namespace std;

class SignIn
{
private:

	string userName;//用户名
	string password;//密码
	string password1;//第二次输入的密码
	int zone;// 选择游戏大区 （1区还是2区）


public:
	SignIn();

	~SignIn();//析构函数

	void deleteusers();//用户名重复时删除该注册


	void setinformation();//注册


	string getUsers();

	string getPassword();

	int getZone();
	//返回用户名以判断注册的用户名是否重复
};



