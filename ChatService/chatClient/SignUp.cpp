#include "SignUp.h"

class SignUp
{
private:
	string users;//�û���
	string password;//����

public:
	SignUp(char* users = "1234567", char* password = "qwer1234")
	{ //���캯��
		this->users = users, this->password = password;
	}

	~SignUp() {} //��������

	void deleteusers() {//�û����ظ�ʱɾ����ע��
		users = "______";
		password = "______";
	}

	int Login(string users, string password) {//��¼
		if (this->users == users && this->password == password) {
			return 0;
		}
		else {
			return 1;
		}
	}

};



