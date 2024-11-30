#ifndef SECURITY_H
#define SECURITY_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "Flight.h"


class Security {
private:
	sql::Connection* con = nullptr;
	std::string username = "";
	int choice = -1;

	void setChoice(const int& choice);
	void handleChoice(int c);
	void logSecurityThreat();
	void viewThreatList();
	void viewFlightInformation();

public:
	Security(sql::Connection* con, std::string user);

	void displayOptions();
	int getIntInput();
	
	int getChoice() const;
	sql::Connection* getConnection();
};

#endif
