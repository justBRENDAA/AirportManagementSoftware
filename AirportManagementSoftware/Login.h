#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>

class Login {
public:
    // Constructor
    Login();

    // Method to handle login logic
    bool login(const std::string& username, const std::string& password);

    // ***NEEDS TO BE IMPLEMENTED INTO MAIN FUNCITON***
    // -------------------------------------------------
    // Method to create an account 
    bool createAccount(const std::string& username, const std::string& password, const std::string& email);


    // ***NEEDS TO BE IMPLEMENTED INTO MAIN FUNCITON***
    // -------------------------------------------------
    // Method to delete an account
    bool deleteAccount(const std::string& username);

    // Destructor
    ~Login();

private:
    // Connect and disconnect from the database
    void connectToDatabase();
    void disconnectDatabase();

    // database connection object
    sql::Connection* con;  // stores the database connection

    std::string username;
    std::string password;
};

#endif
