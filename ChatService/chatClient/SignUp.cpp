#include "SignUp.h"


SignUp::SignUp(){
	massage.signInOrSignOut = 2;
}

SignUp::~SignUp() {} //析构函数

void SignUp::deleteusers() {//用户名重复时删除该注册
}

void SignUp::Login() {//登录
	cout << "您好，请登录！" << endl;
	cout << "请输入用户名：";
	cin >> massage.userName;
	cout << "请输入密码：";
	cin >> massage.password;
	cout << "请选择游戏大区：";
	cin >> massage.zone;
}

Msg SignUp::getMsg() {
	return massage;
}



