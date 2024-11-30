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
        std::cout << "4. Log Out" << std::endl;

        int selection;

        do {
            selection = getIntInput();
            setChoice(selection);

            if (getChoice() == -1)
                std::cout << "Please select a valid option(1-4): ";
        } while (getChoice() == -1);

        handleChoice(getChoice());

        if (getChoice() == 4) {
            exitProgram = true;
        }

        if (!exitProgram)
        {
            do {
                std::cout << "Would you like select another Security option (Y/N)? ";
                std::cin >> userContinue;
                std::cout << std::endl;
            } while (userContinue != 'Y' && userContinue != 'y' && userContinue != 'N' && userContinue != 'n');
        }

    } while (!exitProgram && (userContinue == 'Y' || userContinue == 'y'));

    if (userContinue == 'n' || userContinue == 'N')
        std::cout << "Logging out. . .\n";
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
        //std::cout << "\nLogging out . . . \n";
    }
}

void Security::logSecurityThreat()
{
    std::string description;
    int threatLevel;
    std::string location;

    // threat details from security member
    std::cout << "\nEnter threat description: ";
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

    std::cout << "\nThreat logged successfully.\n\n";
}

void Security::viewThreatList()
{
    sql::PreparedStatement* pstmt = con->prepareStatement(
        "SELECT threat_id, description, threat_level, location, timestamp FROM Threats"
    );

    sql::ResultSet* res = pstmt->executeQuery();

    std::cout << "\n   THREATS LIST\n";
    std::cout << "======================\n";

    // while loop will traverse through every output line
    while (res->next()) {
        // set the values
        int threat_id = res->getInt("threat_id");
        std::string description = res->getString("description");
        int threat_level = res->getInt("threat_level");
        std::string location = res->getString("location");
        std::string timestamp = res->getString("timestamp");

        // print the info
        std::cout << "Threat ID: " << threat_id << "\n";
        std::cout << "Description: " << description << "\n";
        std::cout << "Threat Level: " << threat_level << "\n";
        std::cout << "Location: " << location << "\n";
        std::cout << "Timestamp: " << timestamp << "\n";
        std::cout << "----------------------------------------\n\n";
    }

    delete res;
    delete pstmt;
}

void Security::viewFlightInformation()
{
    Flight f(con, username);
    f.displayFlightReport();
}

void Security::setChoice(const int& c)
{
    if (c >= 1 && c <= 4)
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

int Security::getIntInput()
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