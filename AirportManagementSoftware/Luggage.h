#ifndef LUGGAGE_H
#define LUGGAGE_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>


class Luggage {
private:
    std::string username;
    std::string luggage_id;
    std::string passenger_id;
    std::string flight_id;
    std::string location;
    
    sql::Connection* con;

public:
    Luggage(sql::Connection* existingCon, std::string username);
    void displayInfo();
};

#endif