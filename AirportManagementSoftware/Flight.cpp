//#include "Flight.h"
//#include "iostream"
//
//bool Flight::find(int number, const string& gate, float time) const {
//    return (flightNumber == number && flightGate == gate && flightTime == time);
//}
//
//void Flight::obtainInput() {
//    cout << "Enter flight number: ";
//    cin >> flightNumber;
//    cin.ignore(); // Ignore leftover newline from input buffer
//
//    cout << "Enter flight gate: ";
//    getline(cin, flightGate);
//
//    cout << "Enter flight destination: ";
//    getline(cin, flightDestination);
//
//    cout << "Enter flight time (in hours, e.g., 12.30): ";
//    cin >> flightTime;
//
//    cout << "Enter flight credentials: ";
//    cin.ignore();
//    getline(cin, flightCredentials);
//
//    flightStatus = "WAITING FOR DEPARTURE"; // Default status
//}
//
//void Flight::displayFlightDetails() const {
//    cout << "Flight Number: " << flightNumber << endl;
//    cout << "Flight Gate: " << flightGate << endl;
//    cout << "Flight Destination: " << flightDestination << endl;
//    cout << "Flight Time: " << flightTime << " hours" << endl;
//    cout << "Flight Status: " << flightStatus << endl;
//    cout << "Flight Credentials: " << flightCredentials << endl;
//}