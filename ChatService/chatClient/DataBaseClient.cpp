#include "DataBaseClient.h"

void DataBaseClient::selectOnlineClient() {
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
				sql_row = mysql_fetch_row(result);
				cout << "���ߵ��û��У�" << endl;
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
				{
					cout << sql_row[1] << endl;
				}
			}
		}
	}
	else {
		cout << "���ݿ�����ʧ�ܣ�" << endl;
	}
}