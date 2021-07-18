#include "SignIn.h"
class SignIn
{
private:string users;//用户名
		string password;//密码
		string password1;//第二次输入的密码
		int zone;
public:
	SignIn(string users = "1234567", string password = "qwer1234")
	{ //构造函数
		this->users = users, this->password = password;
	}

	~SignIn() {} //析构函数

	void deleteusers() {//用户名重复时删除该注册
		users = "______";
		password = "______";
	}

	int setinformation() {//注册
		int judge1 = 0;
		cout << "请设置您的用户名：";
		//Users = (char*)malloc(20 * sizeof(char));
		cin >> users;
		cout << "请设置您的密码：";
		//Password = (char*)malloc(20 * sizeof(char));
		cin >> password;
		cout << "请再次输入您设置的密码：";
		//Password1 = (char*)malloc(20 * sizeof(char));
		cin >> password1;//用户名密码输入
		if (password == password1) {// 判断是否两次密码是否相等
			return 0;
		}
		else {
			return 1;
		}
	}

	string getUsers() { return users; }//返回用户名以判断注册的用户名是否重复
};


