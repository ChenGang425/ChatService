#include "SignUp.h"

class SignUp
{
private:
	string users;//用户名
	string password;//密码

public:
	SignUp(char* users = "1234567", char* password = "qwer1234")
	{ //构造函数
		this->users = users, this->password = password;
	}

	~SignUp() {} //析构函数

	void deleteusers() {//用户名重复时删除该注册
		users = "______";
		password = "______";
	}

	int Login(string users, string password) {//登录
		if (this->users == users && this->password == password) {
			return 0;
		}
		else {
			return 1;
		}
	}

};



