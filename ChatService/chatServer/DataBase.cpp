#include "DataBase.h"


// ��
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
			cout << "��������ʧ��!" << endl;
			return 0;
		}
		else {
			cout << "�������ݳɹ�!" << endl;
			return 1;
		}
	}
	else {
		cout << "���ݿ�����ʧ�ܣ�" << endl;
		return 0;
	}
}

// ɾ
void DataBase::deleteDataBase() {}

// ��
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
			cout << "��������״̬ʧ��!" << endl;
			return 0;
		}
		else {
			cout << "��������״̬�ɹ�!" << endl;
			return 1;
		}
	}
	else {
		cout << "���ݿ�����ʧ�ܣ�" << endl;
		return 0;
	}
}

// ��
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
			cout << "��ѯ�û�����ʧ��!" << endl;
			return 0;
		}
		else {
			cout << "��ѯ�û����ݳɹ�!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				sql_row = mysql_fetch_row(result);
				if (sql_row != NULL) {
					cout << "�û���¼����ͨ��" << endl;
					return 1;
				}
				else {
					cout << "���޴���!" << endl;
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
}

// ��ѯ���û��Ƿ��ں�����
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
			cout << "��ѯ�û�������ʧ��!" << endl;
			return 0;
		}
		else {
			cout << "��ѯ�û��������ɹ�!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				sql_row = mysql_fetch_row(result);
				if (strcmp(sql_row[0], "0") == 0) {
					cout << "���û����ں�������" << endl;
					return 1;
				}
				else {
					cout << "���û��ں�������" << endl;
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
}


int DataBase::selectUserWhetherSignIn(string name) {
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "select * from chat_info_table where name = '" + name + "'";

		cout << sentenceStr;
		char* sentenceChar = new char[sentenceStr.length() + 1];
		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			cout << "��ѯ�Ƿ���ע��ʧ��!" << endl;
		}
		else {
			cout << "��ѯ�Ƿ���ע��ɹ�!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				sql_row = mysql_fetch_row(result);
				if (sql_row != NULL) {
					return 1;
				}

			}
		}
	}
	else {
		cout << "���ݿ�����ʧ�ܣ�" << endl;
	}
	return 0;
}


// ��ѯ�����û�
string DataBase::selectOnlineClient() {
	string onlineClient;
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "select * from chat_info_table where online_status = 1";

		cout << sentenceStr;
		char* sentenceChar = new char[sentenceStr.length() + 1];
		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			cout << "��ѯ�����û�ʧ��!" << endl;
		}
		else {
			cout << "��ѯ�����û��ɹ�!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				cout << "���ߵ��û��У�" << endl;
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
				{
					cout << sql_row[1] << endl;
					onlineClient = onlineClient + sql_row[1] + "\n";
				}
				return onlineClient;
			}
		}
	}
	else {
		cout << "���ݿ�����ʧ�ܣ�" << endl;
	}
	return NULL;
}

string DataBase::selectUserInf(string searchUserInf) {
	string answer;
	mysql_init(&myCont);
	MYSQL * mySqlConnect = mysql_real_connect(&myCont, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0);
	if (mySqlConnect) {
		string sentenceStr = "select * from chat_info_table where name = '" + searchUserInf + "'";

		cout << sentenceStr;
		char* sentenceChar = new char[sentenceStr.length() + 1];
		strcpy(sentenceChar, sentenceStr.c_str());
		int flag = mysql_query(&myCont, sentenceChar);
		if (flag) {
			cout << "��ѯ�����û�ʧ��!" << endl;
		}
		else {
			cout << "��ѯ�����û��ɹ�!" << endl;

			result = mysql_store_result(&myCont);
			if (result)
			{
				cout << searchUserInf << "����ϢΪ��" << endl;
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
				{
					answer = answer + "������� : " + sql_row[1] + "\n";
					cout << "������� : " << sql_row[1] << endl;
					answer = answer + "���ڴ��� : " + sql_row[2] + "\n";
					cout << "���ڴ��� : " << sql_row[2] << endl;
					answer = answer + "ע��ʱ�� : " + sql_row[4] + "\n";
					cout << "ע��ʱ�� : " << sql_row[4] << endl;
					answer = answer + "����״̬ : " + sql_row[5] + "\n";
					cout << "����״̬ : " << sql_row[5] << endl;
				}
				return answer;
			}
		}
	}
	else {
		//cout << "���ݿ�����ʧ�ܣ�" << endl;
	}
	return NULL;
}





