#include <iostream>
#include "Luggage.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

Luggage::Luggage(sql::Connection* existingCon, std::string user)
{
	con = existingCon;
	username = user;
}

void Luggage::displayInfo()
{
    sql::PreparedStatement* user_pstmt = con->prepareStatement(
        "SELECT user_id FROM Users WHERE username = ?"
    );
    user_pstmt->setString(1, username);
    
    sql::ResultSet* resUser = user_pstmt->executeQuery();

    if (resUser->next()) {
        user_id = resUser->getInt("user_id");
    }

    delete resUser;
    delete user_pstmt;

    sql::PreparedStatement* pass_pstmt = con->prepareStatement(
        "SELECT passenger_id FROM Passengers WHERE user_id = ?"
    );
    pass_pstmt->setInt(1, user_id);

    sql::ResultSet* resPass = pass_pstmt->executeQuery();

    if (resPass->next()) {
        passenger_id = resPass->getInt("passenger_id");
    }

    delete resPass;
    delete pass_pstmt;

    sql::PreparedStatement* pstmt = con->prepareStatement(
        "SELECT luggage_id, passenger_id, flight_id, location FROM Luggage WHERE passenger_id = ?"
    );
    pstmt->setInt(1, passenger_id);

    sql::ResultSet* resLuggage = pstmt->executeQuery();

    if (resLuggage->next()) {
        luggage_id = resLuggage->getInt("luggage_id");
        passenger_id = resLuggage->getInt("passenger_id");
        flight_id = resLuggage->getInt("flight_id");
        location = resLuggage->getString("location");
    }

    delete resLuggage;
    delete pstmt;

    std::cout << "\n LUGGAGE INFORMATION\n";
    std::cout << "========================\n";
    std::cout << "Luggage ID:    " << luggage_id << std::endl;
    std::cout << "Passenger ID:  " << passenger_id << std::endl;
    std::cout << "Flight ID:     " << flight_id << std::endl;
    std::cout << "Location: " << location << std::endl;

    std::cout << "\nFor information regarding exact luggage location\nvisit our Luggage Kiosk and enter the luggage ID";
}