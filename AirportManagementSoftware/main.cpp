#include <iostream>
#include "Login.h"
#include "UserInterface.h"

int main() {
    Login login;       // create a Login object to handle login operations
    UserInterface ui;  // create a UserInterface object to handle displaying prompts and collecting input

    int option;

    // Initial menu: Login, Create Account, or Exit
    
    std::cout << "Welcome to the system. Choose an option:" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Create a new account" << std::endl;
    std::cout << "3. Exit the program" << std::endl;
        
    std::cin >> option;
        
    switch (option) {
        case 1: {
            // User chose to login
            ui.displayLoginScreen();

            // get user input on username and password from UserInterface class
            std::string username = ui.getUsernameInput();
            std::string password = ui.getPasswordInput();

            // attempt login
            if (login.login(username, password)) {
                ui.displaySuccessfulLogin();  // Display success message if login works

                // Retrieve and display the user's first name
                std::string firstName = login.getUserFirstName();
                std::cout << "Welcome, " << firstName << "!" << std::endl;

                // Display options based on the user type
                std::string userType = login.getUserType();

                // OPTIONS DISPLAYED ARE ONLY TEMPORARY. We'll call the necessary functions from each class once we create them
                if (userType == "Passenger") {
                    std::cout << "\nOptions for passengers: " << std::endl;
                    std::cout << "1. Check-In" << std::endl;
                    std::cout << "2. Get Gate Number" << std::endl;
                    std::cout << "3. Locate Luggage" << std::endl;
                }
                else if (userType == "Staff") {
                    std::cout << "\nOptions for staff: " << std::endl;
                    std::cout << "1. Assist Passengers" << std::endl;
                    std::cout << "2. Manage Flights" << std::endl;
                    std::cout << "3. View Reports" << std::endl;
                }
                else if (userType == "Security") {
                    std::cout << "\nOptions for security: " << std::endl;
                    std::cout << "1. Enforce Safety" << std::endl;
                    std::cout << "2. Check Airport" << std::endl;
                    std::cout << "3. Manage Threats" << std::endl;
                }
                else {
                    std::cout << "Unknown user type." << std::endl; // In case user type is wrong in database
                }
            }
            // if login didnt work
            else {
                ui.displayUnsuccessfulLogin();  // display failure message if login does not work

                // Give the user options if login fails
                std::cout << "Choose an option: " << std::endl;
                std::cout << "1. Try logging in again" << std::endl;
                std::cout << "2. Register a new account" << std::endl;
                std::cout << "3. Exit the program" << std::endl;

                int choice;
                std::cin >> choice;

                if (choice == 1) {
                    // Retry login
                    std::cout << "\nRetrying login..." << std::endl;
                    return main();  // restart the program
                }
                else if (choice == 2) { // havent tested my creating account. i actually think we need to make default user_type be Passenger
                    // create a new account
                    std::string first_name, last_name, username, password, phone_number, email, passport_num;
                    std::cout << "Enter your first name: ";
                    std::cin >> first_name;
                    std::cout << "Enter your last name: ";
                    std::cin >> last_name;
                    std::cout << "Enter a new username: ";
                    std::cin >> username;
                    std::cout << "Enter a new password: ";
                    std::cin >> password;
                    std::cout << "Enter your phone number (format: 1234567890): ";
                    std::cin >> phone_number;
                    std::cout << "Enter your email: ";
                    std::cin >> email;
                    std::cout << "Enter your passport number: ";
                    std::cin >> passport_num;
                    

                    // Call createAccount from Login class to register the user 
                    // (this only creates passenger login. For staff/security admin will add them in the database and provde credentials)
                    if (login.createAccount(username, password, phone_number, email)) {
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
        case 2: {
            // User chose to create a new account
            std::string username, password, email, phone_number;
            std::cout << "Enter a new username: ";
            std::cin >> username;
            std::cout << "Enter a new password: ";
            std::cin >> password;
            std::cout << "Enter your email: ";
            std::cin >> email;
            std::cout << "Enter your phone number (format: 1234567890): ";
            std::cin >> phone_number;

            // Call createAccount from Login class to register the user
            if (login.createAccount(username, password, phone_number, email)) {
                std::cout << "Account successfully created!" << std::endl;
            }
            else {
                std::cout << "\nError creating account." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "\nExiting the program." << std::endl;
            break;
        }
        default: {
            std::cout << "Invalid choice. Please choose again." << std::endl;
            break;
        }
    }
    

    return 0;
}
