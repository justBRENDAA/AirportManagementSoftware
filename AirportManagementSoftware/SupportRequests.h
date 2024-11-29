#ifndef SUPPORTREQUESTS_H
#define SUPPORTREQUESTS_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>

class SupportRequests {
private:
	sql::Connection* con;
	std::string username;
	int pass_id;

public:
	SupportRequests(sql::Connection* con, std::string user);


	void insertRequest();
	void viewRequests();
	void updateRequestStatus();

	sql::Connection* getConnection();
};

#endif