#include "Staff.h"

Staff::Staff(sql::Connection* existingCon, std::string user)
{
	con = existingCon;  // establishes the connection as soon as Login object is instantiated
	username = user;
}

Staff::~Staff()
{
	//
}

void Staff::displayOptions()
{
    char userContinue = 'N';
    do {
        std::cout << "\n STAFF OPTIONS " << std::endl;
        std::cout << "=====================" << std::endl;
        std::cout << "1. View Open Support Tickets" << std::endl;
        std::cout << "2. Update Support Ticket Status" << std::endl;
        std::cout << "3. View Flight Information Report" << std::endl;
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
            std::cout << "\n\nWould you like to view the staff menu again? (Y/N)? ";
            std::cin >> userContinue;
            std::cout << std::endl;
        } while (userContinue != 'Y' && userContinue != 'y' && userContinue != 'N' && userContinue != 'n');

    } while (userContinue == 'Y' || userContinue == 'y');
}

void Staff::handleChoice(int c)
{
    if (choice == 1) {
        viewOpenTickets();
        std::cout << "";
    }
    else if (choice == 2) {
        updateOpenTickets();
    }
    else if (choice == 3) {
        viewFlightInformationReport();
    }
    else if (choice == 4) {
        std::cout << "Exiting program . . . \n";
        return;
    }
}

void Staff::viewOpenTickets()
{

}

void Staff::updateOpenTickets()
{
}

void Staff::viewFlightInformationReport()
{
}

void Staff::setChoice(const int& c)
{
    if (c >= 1 && c <= 4)
        choice = c;
    else
        choice = -1;
}

int Staff::getChoice() const
{
    return choice;
}

sql::Connection* Staff::getConnection()
{
    return con;
}
