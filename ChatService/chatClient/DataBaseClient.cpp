#include "DataBaseClient.h"

void DataBaseClient::selectOnlineClient() {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "select * from chat_info_table where online_status = 1";

		//cout << sentenceStr;
		char* sentenceChar = new char[sentenceStr.length() + 1];
		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			//cout << "查询在线用户失败!" << endl;
		}
		else {
			//cout << "查询在线用户成功!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				cout << "在线的用户有：" << endl;
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
				{
					cout << sql_row[1] << endl;
				}
			}
		}
	}
	else {
		//cout << "数据库连接失败！" << endl;
	}
}


void DataBaseClient::selectUserInf(string searchUserInf) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "select * from chat_info_table where name = '" + searchUserInf + "'";

		//cout << sentenceStr;
		char* sentenceChar = new char[sentenceStr.length() + 1];
		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			//cout << "查询在线用户失败!" << endl;
		}
		else {
			//cout << "查询在线用户成功!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				cout << searchUserInf << "的信息为：" << endl;
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
				{
					cout << "玩家名称 : " << sql_row[1] << endl;
					cout << "所在大区 : " << sql_row[2] << endl;
					cout << "注册时间 : " << sql_row[4] << endl;
					cout << "在线状态 : " << sql_row[5] << endl;
				}
			}
		}
	}
	else {
		//cout << "数据库连接失败！" << endl;
	}
}


void DataBaseClient::updateBlackList(string blackListUser, string inOrOut) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "update chat_info_table set blacklist = " + inOrOut + " where name = '" + blackListUser + "'";
		//cout << sentenceStr;
		char* sentenceChar = new char[sentenceStr.length() + 1];

		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			//cout << "更改黑名单状态失败!" << endl;
		}
		else {
			//cout << "更改黑名单状态成功!" << endl;
		}
	}
	else {
		//cout << "数据库连接失败！" << endl;
	}
}


