#include "SignIn.h"


SignIn::SignIn() {}

SignIn::~SignIn() {} //��������

void SignIn::deleteusers() {//�û����ظ�ʱɾ����ע��
	userName = "______";
	password = "______";
}

void SignIn::setinformation() {//ע��

	cout << "�����������û�����";
	cin >> userName;

	cout << "��ѡ������Ҫ�������Ϸ������" << endl;
	cout << "1. ��Ϸ1��      2. ��Ϸ2��" << endl;
	cin >> zone;

	cout << "�������������룺";
	cin >> password;

	cout << "���ٴ����������õ����룺";
	cin >> password1;//�û�����������

	while (password != password1) {// �ж��Ƿ����������Ƿ����
		cout << "�������벻һ�£����������룺" << endl;

		cout << "�������������룺";
		cin >> password;

		cout << "���ٴ����������õ����룺";
		cin >> password1;//�û�����������
	}

}

string SignIn::getUsers() { //�����û������ж�ע����û����Ƿ��ظ�
	return this->userName;
}

string SignIn::getPassword() {
	return password;
}

int SignIn::getZone() {
	return zone;
}



