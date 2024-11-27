#include <iostream>
#include "Login.h"
#include "UserInterface.h"

int main() {
    Login login;       // create a Login object to handle login operations
    UserInterface ui;  // create a UserInterface object to handle displaying prompts and collecting input

    // display login screen
    ui.displayLoginScreen();

    // get username and password from UserInterface
    std::string username = ui.getUsernameInput(); // this function prompts the user to enter username 
    std::string password = ui.getPasswordInput(); // this function prompts the user to enter password 

    // attempt login using Login class
    if (login.login(username, password)) {
        ui.displaySuccessfulLogin();  // display success message if login works

        // Retrieve and display the user's first name
        std::string firstName = login.getUserFirstName();
        std::cout << "Welcome, " << firstName << "!" << std::endl;

        // Display options based on the user type
        std::string userType = login.getUserType();


        // OPTIONS DISPLAYED ARE ONLY TEMPORARY. we will call the necessary functions from each class once we create them
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
            std::cout << "Unknown user type." << std::endl; // in case user type is wrong in database
        }

    }
    else {
        ui.displayUnsuccessfulLogin();  // display failure message if login fails

        // Give the user options if login fails
        std::cout << "Choose an option: " << std::endl;
        std::cout << "1. Try logging in again" << std::endl;
        std::cout << "2. Register a new account" << std::endl;
        std::cout << "3. Exit the program" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Call the login process again
            std::cout << "\nRetrying login..." << std::endl;
            return main();  // restart the login process
        }
        else if (choice == 2) {
            std::string username, password, email;
            std::cout << "Enter a new username: ";
            std::cin >> username;
            std::cout << "Enter a new password: ";
            std::cin >> password;
            std::cout << "Enter your email: ";
            std::cin >> email;

            // Call createAccount from Login class to register the user
            if (login.createAccount(username, password, email)) {
                std::cout << "Account successfully created!" << std::endl;
            }
            else {
                std::cout << "\nError creating account." << std::endl;
            }
        }
        else if (choice == 3) {
            std::cout << "\nExiting the program." << std::endl;
            return 0;  // exit the program
        }
        else {
            std::cout << "Invalid choice. Exiting the program." << std::endl;
            return 0;  // Exit the program if invalid choice
        }
    }

    return 0;
}
