#include "SignUp.h"


SignUp::SignUp(){
	massage.signInOrSignOut = 2;
}

SignUp::~SignUp() {} //��������

void SignUp::deleteusers() {//�û����ظ�ʱɾ����ע��
}

void SignUp::Login() {//��¼
	cout << "���ã����¼��" << endl;
	cout << "�������û�����";
	cin >> massage.userName;
	cout << "���������룺";
	cin >> massage.password;
	cout << "��ѡ����Ϸ������";
	cin >> massage.zone;
}

Msg SignUp::getMsg() {
	return massage;
}



