#include "Passenger.h"
#include "Luggage.h"
#include "Flight.h"
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
    char userContinue = 'N';
    do {
        std::cout << "\n PASSENGER OPTIONS " << std::endl;
        std::cout << "=====================" << std::endl;
        std::cout << "1. Check Flight Information" << std::endl;
        std::cout << "2. Display Luggage Information" << std::endl;
        std::cout << "3. Request Support" << std::endl;
        std::cout << "4. Exit Program" << std::endl;

        int selection;

        do {
            std::cin >> selection;
            setChoice(selection);

            if (getChoice() == -1)
                std::cout << "Please select a valid option(1-4): ";
        } while (getChoice() == -1);

        handleChoice(getChoice());
        
        do {
            std::cout << "\n\nWould you like select another Passenger option (Y/N)? ";
            std::cin >> userContinue;
            std::cout << std::endl;
        } while (userContinue != 'Y' && userContinue != 'y' && userContinue != 'N' && userContinue != 'n');

    } while (userContinue == 'Y' || userContinue == 'y');
}

void Passenger::handleChoice(int c)
{
    if (choice == 1) {
        checkFlightInformation();
        std::cout << "";
    }
    else if (choice == 2) {
        luggageInformation();
    }
    else if (choice == 3){
        requestSupport();
    }
    else if (choice == 4) {
        std::cout << "Exiting program . . . \n";
        return;
    }
}

void Passenger::checkFlightInformation()
{
    Flight flight(con, username);
    flight.displayInfo();
    std::cout << "\n\n Flight info displayed successfully";
}

void Passenger::luggageInformation()
{
    Luggage luggage(con, username);
    luggage.displayInfo();
    std::cout << "\n\n Luggage info successfully diplayed";
}

void Passenger::requestSupport()
{
    std::cout << "\nWELCOME TO PASSENGER SUPPORT\n";
    std::cout << "==============================\n";

    try {
        std::string supportRequestDescription;
            std::cin.ignore();
            std::cout << "Please enter a description of your request below: \n";
            std::getline(std::cin, supportRequestDescription);

            sql::PreparedStatement* pstmt = con->prepareStatement(
                "SELECT p.passenger_id "
                "FROM Users u "
                "JOIN Passengers p ON u.user_id = p.user_id "
                "WHERE u.username = ?"
            );

            pstmt->setString(1, username); 
        
            sql::ResultSet* res = pstmt->executeQuery();

            if (res->next()) {
                pass_id = res->getInt("passenger_id");
            }

            sql::PreparedStatement* support_pstmt = con->prepareStatement(
                "INSERT INTO Supportrequests (passenger_id, description) VALUES (?, ?)"
            );
            support_pstmt->setInt(1, pass_id);
            support_pstmt->setString(2, supportRequestDescription);

            support_pstmt->executeUpdate();

            delete pstmt;
            delete support_pstmt;

            std::cout << "\nSupport staff will contact you via email.";
    }catch (sql::SQLException& e) {
        std::cerr << "Error sending support request: " << e.what() << std::endl;
    }
}


void Passenger::setChoice(const int& c)
{
    if (c >= 1 && c <= 4)
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
