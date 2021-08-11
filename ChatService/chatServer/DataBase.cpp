#include "DataBase.h"


// 增
int DataBase::insertDataBase(string name, string zone, string password) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		SYSTEMTIME sys;
		GetLocalTime(&sys);

		string registration_time = to_string(sys.wYear) + "-" + to_string(sys.wMonth) + "-" + to_string(sys.wDay) +
			" " + to_string(sys.wHour) + ":" + to_string(sys.wMinute) + ":" + to_string(sys.wSecond) + "." + to_string(sys.wMilliseconds);;
		string sentenceStr = "INSERT INTO chat_info_table (name, zone, password, registration_time, online_status, blacklist) VALUES ('"
			+ name + "' ,'" + zone + "' ,'" + password +"' ,'"+ registration_time +"', 0, 0)";
		cout << sentenceStr;
		char* sentenceChar;

		const int len = sentenceStr.length();

		sentenceChar = new char[len + 1];

		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			cout << "增加数据失败!" << endl;
			return 0;
		}
		else {
			cout << "增加数据成功!" << endl;
			return 1;
		}
	}
	else {
		cout << "数据库连接失败！" << endl;
		return 0;
	}
}

// 删
void DataBase::deleteDataBase() {}

// 改
int DataBase::updateDataBase(string name, string status) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "update chat_info_table set online_status = "+ status +" where name = '" + name + "'";
		cout << sentenceStr;
		char* sentenceChar;

		const int len = sentenceStr.length();

		sentenceChar = new char[len + 1];

		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			cout << "更改在线状态失败!" << endl;
			return 0;
		}
		else {
			cout << "更改在线状态成功!" << endl;
			return 1;
		}
	}
	else {
		cout << "数据库连接失败！" << endl;
		return 0;
	}
}

// 查
int DataBase::selectDataBase(string name, string zone, string password) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = 
			"select * from chat_info_table where name = '" 
			+ name + "' and zone = '" + zone + "' and password = '" + password + "'"; 
		cout << sentenceStr;
		char* sentenceChar;

		const int len = sentenceStr.length();

		sentenceChar = new char[len + 1];

		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			cout << "查询用户数据失败!" << endl;
			return 0;
		}
		else {
			cout << "查询用户数据成功!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				sql_row = mysql_fetch_row(result);
				if ((sizeof(sql_row) / sizeof(sql_row[0])) == 1) {
					cout << "用户登录请求通过" << endl;
					return 1;
				}
				else {
					cout << "查无此人!" << endl;
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
}

// 查询该用户是否在黑名单
int DataBase::selectBlackList(string name) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "select blacklist from chat_info_table where name = '" + name + "'";

		cout << sentenceStr;
		char* sentenceChar = new char[sentenceStr.length() + 1];

		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			cout << "查询用户黑名单失败!" << endl;
			return 0;
		}
		else {
			cout << "查询用户黑名单成功!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				sql_row = mysql_fetch_row(result);
				if (strcmp(sql_row[0], "0") == 0) {
					cout << "该用户不在黑名单上" << endl;
					return 1;
				}
				else {
					cout << "该用户在黑名单上" << endl;
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
}





