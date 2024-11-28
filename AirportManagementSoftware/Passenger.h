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
    int choice;
    int user_id;

    //setters
    void setChoice(const int& choice);


public:
    // Constructor
    Passenger();

    void displayOptions();
    void checkFlightInformation();
    void locateLuggage();
    void requestSupport();

    // getters
    int getChoice() const;


    // Destructor
    ~Passenger();
};

#endif
