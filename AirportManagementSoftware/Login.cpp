#include "Login.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <cstdlib>  // for std::getenv
#include <cstring>  // for std::strlen

Login::Login() {
    connectToDatabase();  // establishes the connection as soon as Login object is instantiated
}

Login::~Login() {
    disconnectDatabase();  // destructor deletes connection
}

// this method is called when object is created in main function
void Login::connectToDatabase() {
    try {
        // get the MySQL PASSWORD from environment variable using _dupenv_s
        char* password = nullptr;
        size_t length = 0;
        if (_dupenv_s(&password, &length, "MYSQL_PASSWORD") != 0 || password == nullptr) {
            std::cerr << "Error: MySQL password not set in environment variable." << std::endl;
            return;
        }

        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", password);  // use the environment variable password
        con->setSchema("airport_db");

        // free allocated memory after done establishing connection
        free(password);
    }
    catch (sql::SQLException& e) {
        std::cerr << "Database connection error: " << e.what() << std::endl;
        con = nullptr;  // handle the error by setting con to nullptr
    }
}

void Login::disconnectDatabase() {
    if (con) {
        delete con;  // delete the connection object to clean up
        con = nullptr;
    }
}

bool Login::login(const std::string& inputUsername, const std::string& inputPassword) {
    if (con == nullptr) { // Check if the connection is active
        std::cerr << "No active database connection." << std::endl;
        return false;
    }

    try {
        username = inputUsername;  // store the values to our class private variables
        password = inputPassword;

        // retrieve the user type and password from the Users table
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT user_id, user_type, password_hash FROM Users WHERE username = ?"
        );
        pstmt->setString(1, inputUsername);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            std::string dbPassword = res->getString("password_hash");  // pulls password from db and store in local variable
            setUserType(res->getString("user_type"));                  // pulls user type from db and stores in private variable
            setUserID(res->getInt("user_id"));                         // pulls user id from db and stores in private variable

            // Check if the entered password matches the stored hash
            if (password == dbPassword) {

                // based on user type, get the first name from the appropriate table
                if (user_type == "Passenger") {
                    sql::PreparedStatement* pstmtPassenger = con->prepareStatement(
                        "SELECT p.first_name FROM Passengers p "           // this join allows us to select first name from db
                        "JOIN Users u ON u.user_id = p.user_id "           // using the user id where based on username 
                        "WHERE u.username = ?"                             // connects the passangers and users table
                    );
                    pstmtPassenger->setString(1, inputUsername);
                    sql::ResultSet* resPassenger = pstmtPassenger->executeQuery();
                    if (resPassenger->next()) {
                        setUserFirstName(resPassenger->getString("first_name"));
                    }
                    delete resPassenger;
                    delete pstmtPassenger;
                }
                else if (user_type == "Staff") {
                    sql::PreparedStatement* pstmtStaff = con->prepareStatement(
                        "SELECT s.first_name FROM Staff s "                      // this join connects the users and staff table
                        "JOIN Users u ON u.user_id = s.user_id "                 // connects through username and user_id
                        "WHERE u.username = ?"
                    );
                    pstmtStaff->setString(1, inputUsername);
                    sql::ResultSet* resStaff = pstmtStaff->executeQuery();
                    if (resStaff->next()) {
                        setUserFirstName(resStaff->getString("first_name"));
                    }
                    delete resStaff;
                    delete pstmtStaff;
                }
                else if (user_type == "Security") {
                    sql::PreparedStatement* pstmtSecurity = con->prepareStatement(
                        "SELECT sec.first_name FROM Security sec "                         // this connects users table and security table
                        "JOIN Users u ON u.user_id = sec.user_id "                   // uses username and user_id to establish connection
                        "WHERE u.username = ?"
                    );
                    pstmtSecurity->setString(1, inputUsername);
                    sql::ResultSet* resSecurity = pstmtSecurity->executeQuery();
                    if (resSecurity->next()) {
                        setUserFirstName(resSecurity->getString("first_name")); // Security table now uses 'first_name'
                    }
                    delete resSecurity;
                    delete pstmtSecurity;
                }

                delete res;
                delete pstmt;
                return true;
            }
        }
        delete res;
        delete pstmt;
        return false;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error during login: " << e.what() << std::endl;
        return false;
    }
}


// Create a new account in the database
bool Login::createAccount(const std::string& inputUsername, const std::string& inputPassword, const std::string& inputPhoneNum, const std::string& inputEmail, 
                          const std::string& inputFirstName, const std::string& inputLastName, const std::string& inputPassportNum) {
    if (con == nullptr) {
        std::cerr << "No active database connection." << std::endl;
        return false;
    }

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO Users (username, password_hash, phone_number, email, user_type) VALUES (?, ?, ?, ?, ?)"
        );
        pstmt->setString(1, inputUsername);
        pstmt->setString(2, inputPassword);
        pstmt->setString(3, inputPhoneNum);
        pstmt->setString(4, inputEmail);
        pstmt->setString(5, "Passenger");

        pstmt->executeUpdate();

        delete pstmt;

        sql::PreparedStatement* pstmtGetID = con->prepareStatement("SELECT LAST_INSERT_ID();");
        sql::ResultSet* res = pstmtGetID->executeQuery();
        res->next();  // move to the result row
        int user_id = res->getInt(1);  // retrieve the user_id (auto-incremented)

        delete pstmtGetID;
        delete res;

        // insert into passenger table 
        sql::PreparedStatement* pstmtPassenger = con->prepareStatement(
            "INSERT INTO Passengers (user_id, first_name, last_name, passport_number) VALUES (?, ?, ?, ?)"
        );
        pstmtPassenger->setInt(1, user_id);
        pstmtPassenger->setString(2, inputFirstName);
        pstmtPassenger->setString(3, inputLastName);
        pstmtPassenger->setString(4, inputPassportNum);

        pstmtPassenger->executeUpdate();

        delete pstmtPassenger;

        // successfull creation message in main function
        // std::cout << "Account successfully created!" << std::endl;

        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error during account creation: " << e.what() << std::endl;
        return false;
    }
}

// delete an account from the database
bool Login::deleteAccount(const std::string& inputUsername) {
    if (con == nullptr) {
        std::cerr << "No active database connection." << std::endl;
        return false;
    }

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "DELETE FROM Users WHERE username = ?"
        );
        pstmt->setString(1, inputUsername);

        pstmt->executeUpdate();

        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error during account deletion: " << e.what() << std::endl;
        return false;
    }
}


// setter/getter methods
void Login::setUserType(const std::string& type)
{
    user_type = type;
}

std::string Login::getUserType() const
{
    return user_type;
}

void Login::setUserFirstName(const std::string& name)
{
    first_name = name;
}

std::string Login::getUserFirstName() const
{
    return first_name;
}

void Login::setUserID(const int& id)
{
    user_id = id;
}

int Login::getUserID() const
{
    return user_id;
}

sql::Connection* Login::getConnection()
{
    return con;
}
