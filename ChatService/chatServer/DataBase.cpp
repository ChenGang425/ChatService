#include "DataBase.h"


// 增
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
			printf("增加数据失败!\n");
			return 0;
		}
		else {
			printf("增加数据成功!\n");
			return 1;
		}
	}
	else {
		cout << "数据库连接失败！" << endl;
		return 0;
	}
};

// 删
void DataBase::deleteDataBase() {};

// 改
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
			printf("更改在线状态失败!\n");
			return 0;
		}
		else {
			printf("更改在线状态成功!\n");
			return 1;
		}
	}
	else {
		cout << "数据库连接失败！" << endl;
		return 0;
	}
};

// 查
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
			printf("查询用户数据失败!\n");
			return 0;
		}
		else {
			printf("查询用户数据成功!\n");

			result = mysql_store_result(&myCont);
			if (result)
			{
				sql_row = mysql_fetch_row(result);
				if ((sizeof(sql_row) / sizeof(sql_row[0])) == 1) {
					return 1;
				}
				else {
					printf("查无此人!\n");
					return 0;
				}
			}
			else {
				return 0;
			}
		}
	}
	else {
		cout << "数据库连接失败！" << endl;
		return 0;
	}
};



