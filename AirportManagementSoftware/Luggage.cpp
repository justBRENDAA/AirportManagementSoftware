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
        "SELECT L.luggage_id, L.passenger_id, L.flight_id, L.location "
        "FROM Luggage L "
        "JOIN Passengers P ON L.passenger_id = P.passenger_id "
        "JOIN Users U ON P.user_id = U.user_id "
        "WHERE U.username = ?"
    );

    pstmt->setString(1, username);  // filter by username

    sql::ResultSet* res = pstmt->executeQuery();

    if (res->next()) {
        luggage_id = res->getInt("luggage_id");
        passenger_id = res->getInt("passenger_id");
        flight_id = res->getInt("flight_id");
        location = res->getString("location");

        std::cout << "\n LUGGAGE INFORMATION\n";
        std::cout << "========================\n";
        std::cout << "Luggage ID:    " << luggage_id << std::endl;
        std::cout << "Passenger ID:  " << passenger_id << std::endl;
        std::cout << "Flight ID:     " << flight_id << std::endl;
        std::cout << "Location: " << location << std::endl;

        std::cout << "\nFor information regarding exact luggage location\n"
                  << "visit our Luggage Kiosk and enter the luggage ID";
    }
    else {
        std::cout << "\nYou don't have a flight ticket.\n"
                  << "Please visit the Ticket Booking desk to purchase a flight ticket.\n";
    }

    delete res;
    delete pstmt;

    
} 