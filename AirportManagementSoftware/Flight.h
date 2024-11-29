#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>

class Flight{
private:
	sql::Connection* con;
	std::string username;

	
	int user_id;
	int passenger_id;
	int flight_id;
	std::string origin_airport_name;
	std::string destination_airport_name;
	std::string flight_number;
	std::string departure_time;
	std::string arrival_time; 
	int origin_airport_id;
	int destination_airport_id;
	int capacity;
	

public:
	Flight(sql::Connection* existingCon, std::string username);
	void displayInfo();
};

#endif
