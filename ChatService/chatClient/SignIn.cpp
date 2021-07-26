#include "SignIn.h"


SignIn::SignIn() {}

SignIn::~SignIn() {} //析构函数

void SignIn::deleteusers() {//用户名重复时删除该注册
	userName = "______";
	password = "______";
}

void SignIn::setinformation() {//注册

	cout << "请设置您的用户名：";
	cin >> userName;

	cout << "请选择您想要进入的游戏大区：" << endl;
	cout << "1. 游戏1区      2. 游戏2区" << endl;
	cin >> zone;

	cout << "请设置您的密码：";
	cin >> password;

	cout << "请再次输入您设置的密码：";
	cin >> password1;//用户名密码输入

	while (password != password1) {// 判断是否两次密码是否相等
		cout << "两次密码不一致，请重新输入：" << endl;

		cout << "请设置您的密码：";
		cin >> password;

		cout << "请再次输入您设置的密码：";
		cin >> password1;//用户名密码输入
	}

}

string SignIn::getUsers() { //返回用户名以判断注册的用户名是否重复
	return this->userName;
}

string SignIn::getPassword() {
	return password;
}

int SignIn::getZone() {
	return zone;
}



