#include "Flight.h"
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

Flight::Flight(sql::Connection* existingCon, std::string user)
{
	con = existingCon;
	username = user;
}

void Flight::displayInfo()
{
    sql::PreparedStatement* pstmt = con->prepareStatement(
        "SELECT f.flight_number, f.departure_time, f.arrival_time, "
        "oa.name AS origin_airport_name, da.name AS destination_airport_name, f.capacity "
        "FROM Flights f "
        "JOIN PassengerFlight pf ON f.flight_id = pf.flight_id "
        "JOIN Passengers p ON pf.passenger_id = p.passenger_id "
        "JOIN Users u ON p.user_id = u.user_id "
        "JOIN Airports oa ON f.origin_airport_id = oa.airport_id "
        "JOIN Airports da ON f.destination_airport_id = da.airport_id "
        "WHERE u.username = ?"
    );

    pstmt->setString(1, username);

    sql::ResultSet* resFlight = pstmt->executeQuery();

    if (resFlight->next()) {
        flight_number = resFlight->getString("flight_number");
        departure_time = resFlight->getString("departure_time");
        arrival_time = resFlight->getString("arrival_time");
        origin_airport_name = resFlight->getString("origin_airport_name");
        destination_airport_name = resFlight->getString("destination_airport_name");
        capacity = resFlight->getInt("capacity");
    }

    delete resFlight;
    delete pstmt;

    std::cout << "\n  FLIGHT INFORMATION\n";
    std::cout << "========================\n";
    std::cout << "Flight number      : " << flight_number << std::endl;
    std::cout << "Departure Info     : " << departure_time << std::endl;
    std::cout << "Arrival Info       : " << arrival_time << std::endl;
    std::cout << "Origin Airport     : " << origin_airport_name << std::endl;
    std::cout << "Destination Airport: " << destination_airport_name << std::endl;
    std::cout << "Capacity           : " << capacity << std::endl;
}
