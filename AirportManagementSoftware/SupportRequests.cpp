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

        std::cout << "\nRequest has been sent.";
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error sending support request: " << e.what() << std::endl;
    }
}

void SupportRequests::viewUserRequests()
{

}
