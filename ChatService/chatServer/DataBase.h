#include <Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <time.h>


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
	// connect
	//MYSQL * sqlConnect();

	// ��
	int insertDataBase(string name, string zone, string password);

	// ɾ
	void deleteDataBase();

	// ��
	void updateDataBase();

	// ��ѯ�������Ƿ��Ѵ���
	void selectDataBase();

};






//
//int res;
//	mysql_init(&myCont);
//	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
//	{
//		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
//		res = mysql_query(&myCont, "select * from test");//��ѯ
//		if (!res)
//		{
//			result = mysql_store_result(&myCont);
//			if (result)
//			{
//				while (sql_row = mysql_fetch_row(result))//��ȡ���������
//				{
//					cout << "BOOKNAME:" << sql_row[0] << endl;
//					cout << "    SIZE:" << sql_row[1] << endl;
//				}
//			}
//		}
//		else
//		{
//			cout << "query sql failed!" << endl;
//		}
//	}
//	else
//	{
//		cout << "connect failed!" << endl;
//	}
//	if (result != NULL)
//		mysql_free_result(result);
//	mysql_close(&myCont);
//	system("pause");
//	return 0;

