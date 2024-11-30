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

        std::cout << "\n  FLIGHT INFORMATION\n";
        std::cout << "========================\n";
        std::cout << "Flight number      : " << flight_number << std::endl;
        std::cout << "Departure Info     : " << departure_time << std::endl;
        std::cout << "Arrival Info       : " << arrival_time << std::endl;
        std::cout << "Origin Airport     : " << origin_airport_name << std::endl;
        std::cout << "Destination Airport: " << destination_airport_name << std::endl;
        std::cout << "Flight Capacity    : " << capacity << std::endl;
    }
    else {
        std::cout << "\nYou don't have a flight ticket.\n"
                  << "Please visit the Ticket Booking desk to purchase a flight ticket.\n";
    }

    delete resFlight;
    delete pstmt;
}

void Flight::displayFlightReport()
{
    std::cout << " \n  FLIGHT PASSENGER REPORT\n";
    std::cout << "=============================\n";

    sql::PreparedStatement* flightNum_pstmt = con->prepareStatement(
        "SELECT f.flight_number "                        // get flight number from flights table
        "FROM Flights f;"
    );
    sql::ResultSet* flightNum_results = flightNum_pstmt->executeQuery();

    // the while will run through the flight ids and use them to display their data
    while (flightNum_results->next()) {
        std::string flightNumber = flightNum_results->getString("flight_number");

        std::cout << "\n   Flight Number: " << flightNumber << "\n";
        std::cout << "===============================\n";

        sql::PreparedStatement* passengers_pstmt = con->prepareStatement(
            "SELECT p.first_name, p.last_name, p.passport_number "          
            "FROM Passengers p "                                            
            "JOIN PassengerFlight pf ON p.passenger_id = pf.passenger_id "  // basically saying to take each passenger and match it with a flight using passenger id
            "JOIN Flights f ON pf.flight_id = f.flight_id "                 // then we take the linked passengers and match it to the flight using flight id
            "WHERE f.flight_number = ?;"                                    // then we only show the ones with flight number equal to ? 
        );

        passengers_pstmt->setString(1, flightNumber);  // Set the flight number
        sql::ResultSet* passengerRes = passengers_pstmt->executeQuery();

        bool hasPassengers = false;
        // loop through all the passaners if we get a results list
        while (passengerRes->next()) {
            std::string firstName = passengerRes->getString("first_name");
            std::string lastName = passengerRes->getString("last_name");
            std::string passportNumber = passengerRes->getString("passport_number");

            std::cout << firstName << " " << lastName << " | Passport: " << passportNumber << "\n";
            hasPassengers = true;
        }

        if (!hasPassengers) {
            std::cout << "No passengers found for this flight.\n";
        }

        delete passengerRes;
        delete passengers_pstmt;
    }

    delete flightNum_pstmt; 
    delete flightNum_results;    

}
