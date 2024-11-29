#ifndef SUPPORTREQUESTS_H
#define SUPPORTREQUESTS_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>

class SupportRequests {
private:
	sql::Connection* con = nullptr;
	std::string username = "";
	std::string supportRequestDescription = "";
	int pass_id = -1;

public:
	SupportRequests(sql::Connection* con, std::string user);

	void setPassengerId();
	void insertRequest();
	void viewUserRequests();
	void viewAllOpenTickets();
	void viewAllClosedTickets();
	void updateRequestStatus();

	sql::Connection* getConnection();

	
};

#endif