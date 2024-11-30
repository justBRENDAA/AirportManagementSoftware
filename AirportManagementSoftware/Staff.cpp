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
    bool exitProgram = false;
    do {
        std::cout << "\n   STAFF OPTIONS " << std::endl;
        std::cout << "=====================" << std::endl;
        std::cout << "1. View Open Support Tickets" << std::endl;
        std::cout << "2. View Closed Support Tickets" << std::endl;
        std::cout << "3. Update Support Ticket Status" << std::endl;
        std::cout << "4. View Flight Information Report" << std::endl;
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

        if (!exitProgram)
        {
            do {
                std::cout << "\nWould you like to view the staff menu again? (Y/N)? ";
                std::cin >> userContinue;
                std::cout << std::endl;
            } while (userContinue != 'Y' && userContinue != 'y' && userContinue != 'N' && userContinue != 'n');
        }
    } while (!exitProgram && (userContinue == 'Y' || userContinue == 'y'));

    if (userContinue == 'n' || userContinue == 'N')
        std::cout << "Logging out. . .\n";
}

void Staff::handleChoice(int c)
{
    if (choice == 1) {
        viewOpenTickets();
        std::cout << "";
    }
    if (choice == 2) {
        viewClosedTickets();
        std::cout << "";
    }
    else if (choice == 3) {
        updateOpenTickets();
    }
    else if (choice == 4) {
        viewFlightInformationReport();
    }
    else if (choice == 5) {
        // std::cout << "\nLogging out . . . \n";
    }
}

void Staff::viewOpenTickets()
{
    SupportRequests sup(con, username);
    sup.viewAllOpenTickets();
}

void Staff::viewClosedTickets()
{
    SupportRequests sup(con, username);
    sup.viewAllClosedTickets();
}

void Staff::updateOpenTickets()
{
    SupportRequests sup(con, username);
    sup.updateRequestStatus();
}


void Staff::viewFlightInformationReport()
{
    Flight f(con, username);
    f.displayFlightReport();
}

void Staff::setChoice(const int& c)
{
    if (c >= 1 && c <= 5)
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


int Staff::getIntInput()
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