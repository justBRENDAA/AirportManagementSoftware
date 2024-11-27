#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>

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

public:
    // Constructor
    Login();

    // Method to handle login logic
    bool login(const std::string& username, const std::string& password);
    bool createAccount(const std::string& username, const std::string& password, const std::string& phone_num, const std::string& email);
    bool deleteAccount(const std::string& username);

    void setUserType(const std::string& type); // setter for user_type
    std::string getUserType() const;           // getter for user_type. will be used to display appropriate options after login!

    void setUserFirstName(const std::string& type); // setter for user_type
    std::string getUserFirstName() const;           // getter for user_type. will be used to display appropriate options after login!

    // Destructor
    ~Login();


};

#endif
