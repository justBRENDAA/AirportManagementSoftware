#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "Luggage.h"
#include "SupportRequests.h"

class Passenger {
private:
    // database connection object
    sql::Connection* con;  // stores the database connection

    std::string username;
    std::string password;
    std::string user_type;
    std::string first_name;
    std::string description;
    int pass_id;
    int choice;
    int user_id;

    //setters
    void setChoice(const int& choice);


public:
    // Constructor
    Passenger(sql::Connection* existingCon, std::string username);

    void displayOptions();
    void handleChoice(int c);
    void checkFlightInformation();
    void luggageInformation();
    void requestSupport();

    // getters
    int getChoice() const;
    sql::Connection* getConnection();

    // Destructor
    ~Passenger();
};

#endif
