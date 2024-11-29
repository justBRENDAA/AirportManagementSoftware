#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>

class Staff {
private:
    sql::Connection* con;  // stores the database connection
    std::string username;
    int choice;

public:
    Staff(sql::Connection* existingCon, std::string username);
    ~Staff();

    void displayOptions();
    void handleChoice(int c);
    void viewOpenTickets();
    void updateOpenTickets();
    void viewFlightInformationReport();

    //setters
    void setChoice(const int& choice);

    // getters
    int getChoice() const;
    sql::Connection* getConnection();
};



#endif