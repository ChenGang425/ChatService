#include<iostream>
#include<string>
#include "comment.h"
using namespace std;


class SignUp
{
private:

	Msg massage;

public:
	SignUp();

	~SignUp();//Îö¹¹º¯Êý

	void deleteusers();

	void Login();

	Msg getMsg();

};
