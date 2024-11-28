#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>


class Passenger {
private:
    // Connect and disconnect from the database
    void connectToDatabase();
    void disconnectDatabase();

    // database connection object
    sql::Connection* con;  // stores the database connection

    std::string username;
    std::string password;
    std::string user_type;
    std::string first_name;
    int user_id;

public:
    // Constructor
    Passenger();

    

    // Destructor
    ~Passenger();
};

#endif
