#include "DataBase.h"


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
int DataBase::updateDataBase(string name, string status) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "update chat_info_table set online_status = "+ status +" where name = " + name;
		cout << sentenceStr;
		char* sentenceChar;

		const int len = sentenceStr.length();

		sentenceChar = new char[len + 1];

		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			printf("��������״̬ʧ��!\n");
			return 0;
		}
		else {
			printf("��������״̬�ɹ�!\n");
			return 1;
		}
	}
	else {
		cout << "���ݿ�����ʧ�ܣ�" << endl;
		return 0;
	}
};

// ��
int DataBase::selectDataBase(string name, string zone, string password) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = 
			"select * from chat_info_table where name = " 
			+ name + ", zone = " + zone + ", password = " + password; 
		cout << sentenceStr;
		char* sentenceChar;

		const int len = sentenceStr.length();

		sentenceChar = new char[len + 1];

		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			printf("��ѯ�û�����ʧ��!\n");
			return 0;
		}
		else {
			printf("��ѯ�û����ݳɹ�!\n");

			result = mysql_store_result(&myCont);
			if (result)
			{
				sql_row = mysql_fetch_row(result);
				if ((sizeof(sql_row) / sizeof(sql_row[0])) == 1) {
					return 1;
				}
				else {
					printf("���޴���!\n");
					return 0;
				}
			}
			else {
				return 0;
			}
		}
	}
	else {
		cout << "���ݿ�����ʧ�ܣ�" << endl;
		return 0;
	}
};



