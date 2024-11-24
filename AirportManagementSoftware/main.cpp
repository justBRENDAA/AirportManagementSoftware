//test file
#include <iostream> 
#include "UserInterface.h"
#include "Login.h"
#include "Luggage.h"
#include "Flight.h"

using namespace std; 

int main() {
  
    // THIS DISPLAYS LOGIN SCREEN
    UserInterface::displayLoginScreen();

    // USER LOGIN WITH USER ENTERING USER TYPE
    string userType;
    cout << "Enter your user type (Passenger, Staff, Security): ";
    cin >> userType;

    // DISPLAY MENU BASED ON USER TYPE
    UserInterface::displayMainMenu(userType);

    
    return 0;
}

