#include <iostream>
#include <string>
#include <mysql/mysql.h>
using namespace std;
class Database
{
public:
	Database();
	~Database();

	int init_db(std::string host, std::string user, std::string password, std::string db_name);
	void run();
private:
	int exe_sql();
	int insert_sql();
	int delete_sql();
	int update_sql();
	MYSQL* connection;
	MYSQL_RES* result;
	MYSQL_ROW row;
};
