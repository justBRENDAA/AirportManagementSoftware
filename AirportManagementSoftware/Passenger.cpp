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


void Passenger::displayOptions()
{
    do {
        std::cout << "\nPASSENGER OPTIONS: " << std::endl;
        std::cout << "=====================" << std::endl;
        std::cout << "1. Check-In" << std::endl;
        std::cout << "2. Get Gate Number" << std::endl;
        std::cout << "3. Locate Luggage" << std::endl;

        int selection;
        std::cin >> selection;
        setChoice(selection);

        if (getChoice() == -1) {
            std::cout << "Please select a valid option (1-3): ";
            std::cin >> selection;
            setChoice(selection);
        }
    } while (getChoice() == -1);
}

void Passenger::checkFlightInformation()
{
    // first check if user has a ticket
    // since program does not support the purchase of tickets
    // message will direct them to the purchase desk with airport staff
}

void Passenger::locateLuggage()
{
    // again if a user has a ticket we can check their luggage
}

void Passenger::requestSupport()
{
    // users can submit help request here 
    // request added to database
    // confirm request has been sent and notify user
    // that they will hear back through the email associated with their account.
}


void Passenger::setChoice(const int& c)
{
    if (c >= 1 && c <= 3)
        choice = c;
    else
        choice = -1;
}

int Passenger::getChoice() const
{
    return choice;
}