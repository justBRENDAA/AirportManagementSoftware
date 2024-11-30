//#ifndef ADMIN_H
//#define ADMIN_H
//
//#include <string>
//#include <mysql_driver.h>
//#include <mysql_connection.h>
//
//
//class Admin {
//private:
//    sql::Connection* con;  
//    std::string username;
//    
//    //setters
//    void setChoice(const int& choice);
//
//public:
//    // constructor
//    Admin(sql::Connection* existingCon, std::string username);
//
//    void displayOptions();
//    void handleChoice(int c);
//    int getIntInput();
//
//    // getters
//    int getChoice() const;
//    sql::Connection* getConnection();
//
//    // Destructor
//    ~Admin();
//};
//
//#endif