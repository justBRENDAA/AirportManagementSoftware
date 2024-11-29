#include "Passenger.h"
#include "Luggage.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <cstdlib>  // for std::getenv
#include <cstring>  // for std::strlen


Passenger::Passenger(sql::Connection* existingCon, std::string user) {
    con = existingCon;  // establishes the connection as soon as Login object is instantiated
    username = user;
}


Passenger::~Passenger() {
    // empty for now
}


void Passenger::displayOptions()
{
    
    std::cout << "\n PASSENGER OPTIONS " << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "1. Check Flight Information" << std::endl;
    std::cout << "2. Display Luggage Information" << std::endl;
    std::cout << "3. Request Support" << std::endl;

    int selection;

    do {
        std::cin >> selection;
        setChoice(selection);

        if (getChoice() == -1)
            std::cout << "Please select a valid option(1-3): ";
    } while (getChoice() == -1);

    handleChoice(getChoice());
}

void Passenger::handleChoice(int c)
{
    if (choice == 1) {
        checkFlightInformation();
    }
    else if (choice == 2) {
        luggageInformation();
    }
    else if (choice == 3){
        requestSupport();
    }
}

void Passenger::checkFlightInformation()
{
    // first check if user has a ticket
    // since program does not support the purchase of tickets
    // message will direct them to the purchase desk with airport staff
}

void Passenger::luggageInformation()
{
    Luggage luggage(con, username);
    luggage.displayInfo();
    std::cout << "\n\n Luggage info successfully diplayed";
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

sql::Connection* Passenger::getConnection()
{
    return con;
}
