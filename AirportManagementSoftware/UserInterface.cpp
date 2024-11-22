#include "UserInterface.h"
#include <iostream>

using namespace std;  

// FUNCTION TO DISPLAY THE LOGIN PROMPT
void UserInterface::displayLoginScreen() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    // validate username and password here
}

// FUNCTION TO SELECT WHAT MENU TO DISPLAY BASED ON USER TYPE
void UserInterface::displayMainMenu(string userType) {
    if (userType == "Passenger") {
        displayPassengerOptions();
    }
    else if (userType == "Staff") {
        displayStaffOptions();
    }
    else if (userType == "Security") {
        displaySecurityOptions();
    }
    else {
        cout << "Invalid user type" << endl;
    }
}

// FUNCTION TO DISPLAY PASSENGER MENU
void UserInterface::displayPassengerOptions() {
    cout << "Passenger Options\n";
    cout << "------------------------\n";
    cout << "1. Choice 1\n";
    cout << "2. Choice 2\n";
    cout << "3. Choice 3\n";
}


// FUNCTION TO DISPLAY PASSENGER MENU
void UserInterface::displayStaffOptions() {
    cout << "Staff Options\n";
    cout << "------------------------\n";
    cout << "1. Choice 1\n";
    cout << "2. Choice 2\n";
    cout << "3. Choice 3\n";
}

// FUNCTION TO DISPLAY PASSENGER MENU
void UserInterface::displaySecurityOptions() {
    cout << "Security Options\n";
    cout << "------------------------\n";
    cout << "1. Choice 1\n";
    cout << "2. Choice 2\n";
    cout << "3. Choice 3\n";
}
