#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>

class UserInterface {
public:
    static void displayLoginScreen();
    static void displayMainMenu(std::string userType);
    static void displayPassengerOptions();
    static void displayStaffOptions();
    static void displaySecurityOptions();
};

#endif