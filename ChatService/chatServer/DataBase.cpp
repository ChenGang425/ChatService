#include "DataBase.h"


// connect
//MYSQL * DataBase::sqlConnect() {
//
//};

// ��
int DataBase::insertDataBase(string name, string zone, string password) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		time_t curtime;

		time(&curtime);

		string registration_time(ctime(&curtime));
		string sentenceStr = "insert into chat_info_table (name, zone, password, registration_time) values ( "
			+ name + "," + zone + "," + password +","+ registration_time +")";
		cout << sentenceStr;
		char* sentenceChar;

		const int len = sentenceStr.length();

		sentenceChar = new char[len + 1];

		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			printf("��������ʧ��!\n");
			return 0;
		}
		else {
			printf("�������ݳɹ�!\n");
			return 1;
		}
	}
	else {
		cout << "���ݿ�����ʧ�ܣ�" << endl;
		return 0;
	}
};

// ɾ
void DataBase::deleteDataBase() {};

// ��
void DataBase::updateDataBase() {};

// ��ѯ�������Ƿ��Ѵ���
void DataBase::selectDataBase() {};



//int main()
//{

void init() {
	const char user[] = "root";
	const char pswd[] = "123456";
	const char host[] = "localhost";
	const char table[] = "game_chat_service";
	unsigned int port = 3306;
	MYSQL myCont;
	MYSQL_RES *result = NULL;
	MYSQL_ROW sql_row;
	int res;
	MYSQL *ms_conn = mysql_init(&myCont);

	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
		res = mysql_query(&myCont, "select * from test");//��ѯ
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
				{
					cout << "BOOKNAME:" << sql_row[0] << endl;
					cout << "    SIZE:" << sql_row[1] << endl;
				}
			}
		}
		else
		{
			cout << "query sql failed!" << endl;
		}
	}
	else
	{
		cout << "connect failed!" << endl;
	}
	if (result != NULL)
		mysql_free_result(result);
	mysql_close(ms_conn), ms_conn = NULL;

	//system("pause");
	//return 0;
}
//}
