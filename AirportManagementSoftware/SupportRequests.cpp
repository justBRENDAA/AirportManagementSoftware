#include "SupportRequests.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>


SupportRequests::SupportRequests(sql::Connection* existingCon, std::string user)
{
	con = existingCon;
	username = user;
}

void SupportRequests::setPassengerId()
{
    try{
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT p.passenger_id "
            "FROM Users u "                                // get passenger id from passengers table
            "JOIN Passengers p ON u.user_id = p.user_id "  // by joining it through user table 
            "WHERE u.username = ?"                         // with username
        );

        pstmt->setString(1, username);                     // set username as the ? 

        sql::ResultSet* res = pstmt->executeQuery();       // execute the query

        if (res->next()) {
            pass_id = res->getInt("passenger_id");         // store obrained id in private variable
        }

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error obtaining passenger id: " << e.what() << std::endl;
    }
}

// method called by users to send a support request
void SupportRequests::insertRequest()
{
    try{
        std::cin.ignore();
        std::cout << "Please enter a description of the support request below: \n";
        std::getline(std::cin, supportRequestDescription);

        setPassengerId();

        sql::PreparedStatement* support_pstmt = con->prepareStatement(               // query inserts into 
            "INSERT INTO Supportrequests (passenger_id, description) VALUES (?, ?)"  // support request table
        );
        support_pstmt->setInt(1, pass_id);                         // set the passenger id as first ? 
        support_pstmt->setString(2, supportRequestDescription);    // set the descriptio as the second ? 

        support_pstmt->executeUpdate();                            // execute the query

                                                      // delete pointers
        delete support_pstmt;

        std::cout << "\nRequest has been sent.\n\n";
    }catch (sql::SQLException& e) {
        std::cerr << "Error sending support request: " << e.what() << std::endl;
    }
}

void SupportRequests::viewUserRequests()
{
    try {
        setPassengerId();

        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT request_id, description, status "
            "FROM Supportrequests "
            "WHERE passenger_id = ?"
        );
        pstmt->setInt(1, pass_id);

        sql::ResultSet* res = pstmt->executeQuery();

        std::cout << "\n YOUR SUPPORT REQUESTS\n";
        std::cout << "==========================\n";

        bool hasRequests = false;
        while (res->next()) {
            hasRequests = true;
            std::cout << "Request ID: " << res->getInt("request_id") << "\n";
            std::cout << "Description: " << res->getString("description") << "\n";
            std::cout << "Status: " << res->getString("status") << "\n";
            std::cout << "-------------------------\n";
        }

        std::cout << std::endl; // blank line

        if (!hasRequests) {
            std::cout << "No support requests found.\n";
        }

        delete res;
        delete pstmt;

    }catch (sql::SQLException& e) {
        std::cerr << "Error sending support request: " << e.what() << std::endl;
    }
}

void SupportRequests::viewAllOpenTickets()
{
    try {
        // this query selects all tickets with pending and escalated status
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT request_id, passenger_id, description, status "
            "FROM Supportrequests "
            "WHERE status = 'Pending' OR status = 'Escalated'"
        );

        sql::ResultSet* res = pstmt->executeQuery();

        std::cout << "\n  ALL OPEN SUPPORT TICKETS";
        std::cout << "==============================\n";

        bool hasOpenTickets = false; // flag to check if there is any tickets
        while (res->next()) {
            hasOpenTickets = true;
            std::cout << "Request ID: " << res->getInt("request_id") << "\n";
            std::cout << "Passenger ID: " << res->getInt("passenger_id") << "\n";
            std::cout << "Description: " << res->getString("description") << "\n";
            std::cout << "Status: " << res->getString("status") << "\n";
            std::cout << "------------------------------\n";
        }

        if (!hasOpenTickets) {
            std::cout << "No open support tickets found with Pending or Escalated status.\n";
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error retrieving open support tickets: " << e.what() << std::endl;
    }
}

void SupportRequests::viewAllClosedTickets()
{
}

void SupportRequests::updateRequestStatus()
{
}

sql::Connection* SupportRequests::getConnection()
{
    return con;
}
