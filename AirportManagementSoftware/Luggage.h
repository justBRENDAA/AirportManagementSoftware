#ifndef LUGGAGE_H
#define LUGGAGE_H


#include <string>
using namespace std;


class Luggage {
public:
    //Final constants
    static const string LUGGAGEID;
    static const string PASSENGERID;
    static const string FLIGHTNUMBER;
    static const int LUGGAGEAMOUNT;
    
    //public variables
    string luggageId;
    string passengerId;
    int flightNumber;
    int luggageAmount;
    string status;


    Luggage(string LugId = "", string passId = "", int flightNum = 0, int lugAmount = 0, string stats = "Not Located");
    
    void getUserInput();
    //Update status of luggage
    string updateStatus();

    //Track luggage
    string trackLuggage() const;

    //Displays the luggage area
    string displayLuggageArea() const;

    //Method for constants
    static void displayConstant();
};

#endif