#include <Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <time.h>


using namespace std;
#pragma comment(lib,"C:\\Program Files\\MySQL\\MySQL Server 5.7\\lib\\libmysql.lib") 

//
//int res;
//	mysql_init(&myCont);
//	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
//	{
//		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
//		res = mysql_query(&myCont, "select * from test");//查询
//		if (!res)
//		{
//			result = mysql_store_result(&myCont);
//			if (result)
//			{
//				while (sql_row = mysql_fetch_row(result))//获取具体的数据
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


