#include<iostream>
#include<string>
using namespace std;

class SignIn
{
private:

	string userName;//�û���
	string password;//����
	string password1;//�ڶ������������
	int zone;// ѡ����Ϸ���� ��1������2����


public:
	SignIn();

	~SignIn();//��������

	void deleteusers();//�û����ظ�ʱɾ����ע��


	void setinformation();//ע��


	string getUsers();

	string getPassword();

	int getZone();
	//�����û������ж�ע����û����Ƿ��ظ�
};



