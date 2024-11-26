#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

class UserInterface {
public:
    // Method to display the login screen
    static void displayLoginScreen();

    // Method to display successful login message
    static void displaySuccessfulLogin();

    // Method to display unsuccessful login message
    static void displayUnsuccessfulLogin();

    // Method to get username input from the user
    static std::string getUsernameInput();

    // Method to get password input from the user (masked input) - they only see **** when typing password
    static std::string getPasswordInput();
};

#endif