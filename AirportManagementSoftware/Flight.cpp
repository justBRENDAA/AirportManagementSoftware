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
    std::cout << "in flight display info\n";
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

    sql::PreparedStatement* pass_flight_pstmt = con->prepareStatement(
        "SELECT flight_id FROM Passengerflight WHERE user_id = ?"
    );
    pass_flight_pstmt->setInt(1, user_id);

    sql::ResultSet* resPassFlight = pass_flight_pstmt->executeQuery();

    if (resPass->next()) {
        flight_id = resPassFlight->getInt("flight_id");
    }

    delete resPassFlight;
    delete pass_flight_pstmt;

    sql::PreparedStatement* flight_pstmt = con->prepareStatement(
        "SELECT flight_number, departure_time, arrival_time, origin_airport_id, destination_airport_id, capacity FROM Flight WHERE flight_id = ?"
    );
    flight_pstmt->setInt(1, flight_id);

    sql::ResultSet* resFlight = flight_pstmt->executeQuery();

    if (resFlight->next()) {
        flight_number = resFlight->getString("flight_number");
        departure_time = resFlight->getString("departure_time");
        arrival_time = resFlight->getString("arrival_time");
        origin_airport_id = resFlight->getInt("origin_airport_id");
        destination_airport_id = resFlight->getInt("destination_airport_id");
        capacity = resFlight->getInt("capacity");
    }

    delete resFlight;
    delete flight_pstmt;

    std::cout << "\n LUGGAGE INFORMATION\n";
    std::cout << "========================\n";
    std::cout << "Flight number      :    " << flight_number << std::endl;
    std::cout << "Departure Info     :  " << departure_time << std::endl;
    std::cout << "Arrival Info       :     " << arrival_time << std::endl;
    std::cout << "Origin Airport     : " << origin_airport_id << std::endl;
    std::cout << "Destination Airport: " << destination_airport_id << std::endl;
    std::cout << "Capacity           : " << capacity << std::endl;

    std::cout << "\nFor information regarding exact luggage location\nvisit our Luggage Kiosk and enter the luggage ID";
}
