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
    con = nullptr;
}


void Passenger::displayOptions()
{
    char userContinue = 'N';
    bool exitProgram = false;
    do {
        std::cout << "\n PASSENGER OPTIONS " << std::endl;
        std::cout << "=====================" << std::endl;
        std::cout << "1. Check Flight Information" << std::endl;
        std::cout << "2. Display Luggage Information" << std::endl;
        std::cout << "3. Request Support" << std::endl;
        std::cout << "4. View Your Support Requests" << std::endl;
        std::cout << "5. Log Out" << std::endl;

        int selection;

        do {
            selection = getIntInput();
            setChoice(selection);

            if (getChoice() == -1)
                std::cout << "Please select a valid option(1-5): ";
        } while (getChoice() == -1);

        handleChoice(getChoice());
        
        if (getChoice() == 5) {
            exitProgram = true;
        }

        if(!exitProgram)
        {
            do {
                std::cout << "Would you like select another Passenger option (Y/N)? ";
                std::cin >> userContinue;
                std::cout << std::endl;
            } while (userContinue != 'Y' && userContinue != 'y' && userContinue != 'N' && userContinue != 'n');
        }

    } while (!exitProgram && (userContinue == 'Y' || userContinue == 'y'));

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
        viewSupportRequests();
    }
    else if (choice == 5) {
        std::cout << "\nLogging out . . . \n";
    }
}

void Passenger::checkFlightInformation()
{
    Flight flight(con, username);
    flight.displayInfo();
    std::cout << "\nFlight info displayed successfully\n\n";
}

void Passenger::luggageInformation()
{
    Luggage luggage(con, username);
    luggage.displayInfo();
    std::cout << "\nLuggage info successfully diplayed\n\n";
}

void Passenger::requestSupport()
{
    std::cout << "\nWELCOME TO PASSENGER SUPPORT\n";
    std::cout << "==============================\n";

    SupportRequests sup(con, username);
    sup.insertRequest();
}

void Passenger::viewSupportRequests()
{
    SupportRequests sup(con, username);
    sup.viewUserRequests();
}


void Passenger::setChoice(const int& c)
{
    if (c >= 1 && c <= 5)
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


int Passenger::getIntInput()
{
    std::string strInput;
   
    std::cin >> strInput;
    std::cout << std::endl;

    try {
        int intInput = stoi(strInput);
        intInput = intInput;
        return intInput;
    }
    catch (const std::exception& e) {
        std::cout << "Value entered must be an integer.\n";
    }
}