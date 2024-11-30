#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include "Security.h"

Security::Security(sql::Connection* existingCon, std::string user)
{
	con = existingCon;
	username = user;
}

void Security::displayOptions()
{
    char userContinue = 'N';
    bool exitProgram = false;
    do {
        std::cout << "\n SECURITY OPTIONS " << std::endl;
        std::cout << "=====================" << std::endl;
        std::cout << "1. Log Security Threat" << std::endl;
        std::cout << "2. View Security Threat List" << std::endl;
        std::cout << "3. View Flight Information" << std::endl;
        std::cout << "4. Exit Program" << std::endl;

        int selection;

        do {
            std::cin >> selection;
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
                std::cout << "Would you like select another Passenger option (Y/N)? ";
                std::cin >> userContinue;
                std::cout << std::endl;
            } while (userContinue != 'Y' && userContinue != 'y' && userContinue != 'N' && userContinue != 'n');
        }

    } while (!exitProgram && (userContinue == 'Y' || userContinue == 'y'));

    if (userContinue == 'n' || userContinue == 'N')
        std::cout << "Exiting the program. . .\n";
}

void Security::handleChoice(int c)
{
    if (choice == 1) {
        logSecurityThreat();
        std::cout << "";
    }
    else if (choice == 2) {
        viewThreatList();
    }
    else if (choice == 3) {
        viewFlightInformation();
    }
    else if (choice == 4) {
        std::cout << "\nExiting program . . . \n";
    }
}

void Security::logSecurityThreat()
{
    std::string description;
    int threatLevel;
    std::string location;

    // threat details from security member
    std::cout << "Enter threat description: ";
    std::cin.ignore();
    std::getline(std::cin, description);

    std::cout << "Enter threat level (1-5): ";
    std::cin >> threatLevel;

    std::cout << "Enter location of threat: ";
    std::cin.ignore();
    std::getline(std::cin, location);

    sql::PreparedStatement* pstmt = con->prepareStatement(
        "INSERT INTO Threats (description, threat_level, location) VALUES (?, ?, ?)"
    );

    pstmt->setString(1, description);  // pass description
    pstmt->setInt(2, threatLevel);     // pass threat level
    pstmt->setString(3, location);     // pass location

    pstmt->executeUpdate();

    delete pstmt;

    std::cout << "\nThreat was logged successfully.";
}

void Security::viewThreatList()
{

}

void Security::viewFlightInformation()
{

}

void Security::setChoice(const int& c)
{
    if (c >= 1 && c <= 5)
        choice = c;
    else
        choice = -1;
}

int Security::getChoice() const
{
    return choice;
}

sql::Connection* Security::getConnection()
{
	return con;
}