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
    if (con == nullptr) { // check if the connection is active
        std::cerr << "No active database connection." << std::endl;
        return false;
    }

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT password_hash FROM Users WHERE username = ?"
        );
        pstmt->setString(1, inputUsername);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            std::string storedPasswordHash = res->getString("password_hash");

            if (inputPassword == storedPasswordHash) {
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
bool Login::createAccount(const std::string& inputUsername, const std::string& inputPassword, const std::string& inputEmail) {
    if (con == nullptr) {
        std::cerr << "No active database connection." << std::endl;
        return false;
    }

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO Users (username, password_hash, email) VALUES (?, ?, ?)"
        );
        pstmt->setString(1, inputUsername);
        pstmt->setString(2, inputPassword);  // Store the password hash or plain password based on your security design
        pstmt->setString(3, inputEmail);

        pstmt->executeUpdate();

        delete pstmt;
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
