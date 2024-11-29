#ifndef LUGGAGE_H
#define LUGGAGE_H

#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>


class Luggage {
private:
    std::string luggage_id;
    std::string passenger_id;
    std::string flight_id;
    std::string location;

public:
    Luggage(sql::Connection* existingCon, std::string username);

};

#endif