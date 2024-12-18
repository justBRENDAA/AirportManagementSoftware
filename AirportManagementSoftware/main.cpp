#include "UserInterface.h"
#include "Login.h"
#include "Passenger.h" 
#include "Staff.h"
#include "Security.h"

#include <iostream>

void newAccountPrompts(std::string& fn, std::string& ln, std::string& user, std::string& pass, std::string& phone, std::string& email, std::string& passnum);
int getIntInput(bool &f);

int main() {
    UserInterface ui;  // create a UserInterface object to handle displaying prompts and collecting input
    Login login;       // create a Login object to handle login operations
    int option;

    // Initial menu: Login, Create Account, or Exit
    
    std::cout << "Welcome to the system. Choose an option : " << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Create a new account" << std::endl;
    std::cout << "3. Exit the program" << std::endl;
    
    bool validOption = false;   
    option = getIntInput(validOption);
    
    
    if(validOption)
    {
        switch (option) {
            case 1: {
                // User chose to login
                ui.displayLoginScreen();

                // get user input on username and password from UserInterface class
                std::string username = ui.getUsernameInput();
                std::string password = ui.getPasswordInput();

                // attempt login
                if (login.login(username, password))
                {

                }
                // if login didnt work
                else {
                    ui.displayUnsuccessfulLogin();  // display failure message if login does not work

                    int choice;
                    std::cin >> choice;

                    if (choice == 1) {
                        // Retry login
                        std::cout << "\nRetrying login..." << std::endl;
                        return main();  // restart the program
                    }
                    else if (choice == 2) { // havent tested my creating account. i actually think we need to make default user_type be Passenger
                        std::string first_name, last_name, username, password, phone_number, email, passport_num;
                        newAccountPrompts(first_name, last_name, username, password, phone_number, email, passport_num);

                        // Call createAccount from Login class to register the user 
                        // (this only creates passenger login. For staff/security admin will add them in the database and provde credentials)
                        if (login.createAccount(username, password, phone_number, email, first_name, last_name, passport_num)) {
                            std::cout << "Account successfully created!" << std::endl;
                        }
                        else {
                            std::cout << "\nError creating account." << std::endl;
                        }
                    }
                    else if (choice == 3) {
                        std::cout << "\nExiting the program." << std::endl;

                    }
                    else {
                        std::cout << "Invalid choice. Exiting the program." << std::endl;
                        return 0;  // Exit the program if invalid choice
                    }
                }
                break;
            }
                  // create new account
            case 2: {
                // create a new account
                std::string first_name, last_name, username, password, phone_number, email, passport_num;
                newAccountPrompts(first_name, last_name, username, password, phone_number, email, passport_num);

                // Call createAccount from Login class to register the user 
                // (this only creates passenger login. For staff/security admin will add them in the database and provde credentials)
                if (login.createAccount(username, password, phone_number, email, first_name, last_name, passport_num)) {
                    std::cout << "\nAccount successfully created!\n" << std::endl;
                    return main(); // restarts program so user can select to login or exit
                }
                else {
                    std::cout << "\nError creating account." << std::endl;
                }
                break;
            }
                  // exit the program
            case 3: {
                std::cout << "Exiting the program. . ." << std::endl;
                break;
            }
                  // invalid choice
            default: {
                std::cout << "Invalid choice. Try again.\n" << std::endl;
                return main();
                break;
            }
        }
    }
    else
        return main();
   
    return 0;
}

void newAccountPrompts(std::string& fn, std::string& ln, std::string& user, std::string& pass, std::string& phone, std::string& email, std::string& passnum) {
    std::cout << "Enter your first name: ";
    std::cin >> fn;
    std::cout << "Enter your last name: ";
    std::cin >> ln;
    std::cout << "Enter a new username: ";
    std::cin >> user;
    std::cout << "Enter a new password: ";
    std::cin >> pass;
    std::cout << "Enter your phone number (format: 1234567890): ";
    std::cin >> phone;
    std::cout << "Enter your email: ";
    std::cin >> email;
    std::cout << "Enter your passport number: ";
    std::cin >> passnum;
}

int getIntInput(bool &flag)
{
    std::string strInput;
    
    std::cin >> strInput;
    std::cout << std::endl;

    try {
        int intInput = stoi(strInput);
        flag = true;
        return intInput;
    }
    catch (const std::exception& e) {
        std::cout << "Value entered must be an integer.\n";
    }
}