#include "Passenger.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <cstdlib>  // for std::getenv
#include <cstring>  // for std::strlen

Passenger::Passenger() {
    connectToDatabase();  // establishes the connection as soon as Login object is instantiated
}

Passenger::~Passenger() {
    disconnectDatabase();  // destructor deletes connection
}

// this method is called when object is created in main function
void Passenger::connectToDatabase() {
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

void Passenger::disconnectDatabase() {
    if (con) {
        delete con;  // delete the connection object to clean up
        con = nullptr;
    }
}