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
	int req_id = -1;
	bool supportRequestsExist = false;

public:
	SupportRequests(sql::Connection* con, std::string user);

	void setPassengerId();
	void insertRequest();
	void viewUserRequests();
	void viewAllOpenTickets();
	void viewAllClosedTickets();
	void updateRequestStatus();

	void getIntInput();

	sql::Connection* getConnection();
};

#endif