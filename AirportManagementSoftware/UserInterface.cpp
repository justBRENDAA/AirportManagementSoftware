#include "UserInterface.h"
#include <iostream>
#include <conio.h>  // for password masking in console

void UserInterface::displayLoginScreen() {
    std::cout << "Welcome to the Airport System!" << std::endl;
    std::cout << "Please log in to continue." << std::endl;
    std::cout << "===============================" << std::endl;
}

void UserInterface::displaySuccessfulLogin() {
    std::cout << "\nLogin successful!" << std::endl;
}

void UserInterface::displayUnsuccessfulLogin() {
    std::cout << "\nLogin failed!" << std::endl;
    
    // Give the user options if login fails
    std::cout << "Choose an option: " << std::endl;
    std::cout << "1. Try logging in again" << std::endl;
    std::cout << "2. Register a new account" << std::endl;
    std::cout << "3. Exit the program" << std::endl;
    std::cout << "Select option (1-3): ";
}

std::string UserInterface::getUsernameInput() {
    std::string username;
    std::cout << "Enter username: ";
    std::cin >> username;
    return username;
}

std::string UserInterface::getPasswordInput() {
    std::string password = "";
    char ch;

    std::cout << "Enter password: ";
    while (true) {
        ch = _getch(); // _getch() captures one character without echoing it to the console
        if (ch == '\r') { // enter key is pressed
            break;
        }
        else if (ch == '\b') { // backspace key is pressed
            if (password.length() > 0) {
                password.pop_back(); // remove last character
                std::cout << "\b \b"; // move cursor back, erase character
            }
        }
        else {
            password.push_back(ch);
            std::cout << "*"; // masks the character being typed with *
        }
    }
    std::cout << std::endl; // moves to the next line after entering password
    return password;
}