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

	// 增
	int insertDataBase(string name, string zone, string password);

	// 删
	void deleteDataBase();

	// 改
	int updateDataBase(string name, string status);

	// 查询该姓名是否已存在
	int selectDataBase(string name, string zone, string password);

	// 查询该用户是否在黑名单
	int selectBlackList(string name);

	// 查询该名称是否已被注册
	int selectUserWhetherSignIn(string name);

	// 查询在线用户
	string selectOnlineClient();

	// 查询玩家信息
	string selectUserInf(string searchUserInf);

	// 设置黑名单
	void updateBlackList(string blackListUser, string inOrOut);

};




