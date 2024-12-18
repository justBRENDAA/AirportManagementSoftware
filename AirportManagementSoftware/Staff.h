#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "SupportRequests.h"
#include "Flight.h"

class Staff {
private:
    sql::Connection* con = nullptr;  // stores the database connection
    std::string username = "";
    int choice = -1;

public:
    Staff(sql::Connection* existingCon, std::string username);
    ~Staff();

    void displayOptions();
    void handleChoice(int c, char& uc);
    void viewOpenTickets();
    void viewClosedTickets();
    void updateOpenTickets();
    void viewFlightInformationReport();

    int getIntInput();

    //setters
    void setChoice(const int& choice);

    // getters
    int getChoice() const;
    sql::Connection* getConnection();
};

#endif