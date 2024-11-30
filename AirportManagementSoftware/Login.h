#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "Passenger.h"
#include "Staff.h"
#include "Security.h"
#include "UserInterface.h"

class Login {
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

    // setter functions
    // private because they should not be changed after object creation

    void setUserType(const std::string& type); // setter for user_type
    void setUserFirstName(const std::string& type); // setter for user_type
    void setUserID(const int& id); // setter for user_type

public:
    // Constructor
    Login();

    // Method to handle login logic
    bool login(const std::string& username, const std::string& password);
    
    bool createAccount(const std::string& username, const std::string& password, const std::string& phone_num, const std::string& email, 
                       const std::string& first_name, const std::string& last_name, const std::string& passport_num);
    void handleUserType();
   
    // getter functions
    std::string getUserType() const;           
    std::string getUserFirstName() const;             
    int getUserID() const;
    sql::Connection* getConnection(); // to pass connection object to other functions
                                      // we do this so all classes wont have to establish a connection since we already have one made in this class

    // Destructor
    ~Login();
};

#endif
