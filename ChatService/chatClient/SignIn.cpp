#include "SignIn.h"
class SignIn
{
private:string users;//�û���
		string password;//����
		string password1;//�ڶ������������
		int zone;
public:
	SignIn(string users = "1234567", string password = "qwer1234")
	{ //���캯��
		this->users = users, this->password = password;
	}

	~SignIn() {} //��������

	void deleteusers() {//�û����ظ�ʱɾ����ע��
		users = "______";
		password = "______";
	}

	int setinformation() {//ע��
		int judge1 = 0;
		cout << "�����������û�����";
		//Users = (char*)malloc(20 * sizeof(char));
		cin >> users;
		cout << "�������������룺";
		//Password = (char*)malloc(20 * sizeof(char));
		cin >> password;
		cout << "���ٴ����������õ����룺";
		//Password1 = (char*)malloc(20 * sizeof(char));
		cin >> password1;//�û�����������
		if (password == password1) {// �ж��Ƿ����������Ƿ����
			return 0;
		}
		else {
			return 1;
		}
	}

	string getUsers() { return users; }//�����û������ж�ע����û����Ƿ��ظ�
};


