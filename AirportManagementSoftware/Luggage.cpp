//#include <iostream>
//#include "Luggage.h"
//
//
//using namespace std;
//
//    //Final constats initialization
//    const string Luggage::LUGGAGEID;
//    const string Luggage::PASSENGERID;
//    const string Luggage::FLIGHTNUMBER;
//    const int Luggage::LUGGAGEAMOUNT = 0;
//
//    //constructor for the different constants
//    Luggage::Luggage( string lugId, string passId, int flightNum, int lugAmount, string stats): luggageId(lugId), passengerId(passId), flightNumber(flightNum), luggageAmount(lugAmount), status(stats) {}
//
//
//    void Luggage::getUserInput() { 
//        cout << "Enter your Luggage ID: ";
//        cin >> luggageId;
//        
//        cout << "Enter yout passenger ID: ";
//        cin >> passengerId;
//        
//        cout << "Enter your flight number: ";
//        cin >> flightNumber;
//        
//        cout << "Enter amount of luggage: ";
//        cin >> luggageAmount;
//
//        cout << "Enter the current status of your luggage (Not located, In Transport, Delivered): ";
//        cin >> status;
//}
//        //Update status of luggage message
//        string Luggage::updateStatus() {
//            if (status == "Not Located") {
//                status = "In Transport";
//            }else if (status == "In Transport") {
//                status = "Delivered";
//            }else {
//                status = "Not Located";
//            }
//            return status;
//    }
//
//    //Track luggage
//    string Luggage::trackLuggage() const {
//        return "Tracking credentials: Luggage ID " + luggageId + ", Status: "  + status;
//    }
//
//    //Display luggage area
//    string Luggage::displayLuggageArea() const {
//        return "Your Luggage " + luggageId + "is connected to flight # " + to_string(flightNumber) + ".";
//    }
//
//    //Method for constants
//    void Luggage::displayConstant() {
//        std::cout << "LUGGAGEID" << LUGGAGEID << std::endl;
//        std::cout << "PASSENGERID" << PASSENGERID << std::endl;
//        std::cout << "FLIGHTNUMBER" << FLIGHTNUMBER << std::endl;
//        std::cout << "LUGGAGEAMOUNT" << LUGGAGEAMOUNT << std::endl;
//}
//
