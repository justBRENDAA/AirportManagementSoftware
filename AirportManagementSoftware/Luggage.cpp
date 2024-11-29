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
    sql::PreparedStatement* pstmt = con->prepareStatement(
        "SELECT luggage_id, passenger_id, flight_id, location FROM Luggage WHERE username = ?"
    );
    pstmt->setString(1, username);

    sql::ResultSet* resLuggage = pstmt->executeQuery();
    if (resLuggage->next()) {
        luggage_id = resLuggage->getString("luggage_id");
        passenger_id = resLuggage->getString("passenger_id");
        flight_id = resLuggage->getString("flight_id");
        location = resLuggage->getString("location");
    }
    delete resLuggage;
    delete pstmt;

    std::cout << "Luggage Information\n";
    std::cout << "=====================\n";
    std::cout << "Luggage ID: " << luggage_id << std::endl;
    std::cout << "Passenger ID: " << passenger_id << std::endl;
    std::cout << "Flight ID: " << flight_id << std::endl;
    std::cout << "Location: " << location << std::endl;
}