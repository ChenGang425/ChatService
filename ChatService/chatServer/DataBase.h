#include <Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>



using namespace std;
#pragma comment(lib,"C:\\Program Files\\MySQL\\MySQL Server 5.7\\lib\\libmysql.lib") 

class DataBase {
private:
	string user = "root";
	string pswd = "123456";
	string host = "localhost";
	string table = "game_chat_service";
	unsigned int port = 3306;
	MYSQL myCont;
	MYSQL_RES *result = NULL;
	MYSQL_ROW sql_row;
	int res;


public:

	// ��
	int insertDataBase(string name, string zone, string password);

	// ɾ
	void deleteDataBase();

	// ��
	int updateDataBase(string name, string status);

	// ��ѯ�������Ƿ��Ѵ���
	int selectDataBase(string name, string zone, string password);

};




