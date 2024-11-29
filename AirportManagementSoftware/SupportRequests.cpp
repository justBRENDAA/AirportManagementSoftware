#include "SupportRequests.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>


SupportRequests::SupportRequests(sql::Connection* existingCon, std::string user)
{
	con = existingCon;
	username = username;
}

void SupportRequests::insertRequest()
{
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
}
