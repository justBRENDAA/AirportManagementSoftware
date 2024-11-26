#include <iostream>
#include "Login.h"
#include "UserInterface.h"

int main() {
    Login login;  // create a Login object to handle login operations
    UserInterface ui;  // create a UserInterface object to handle displaying prompts and collecting input

    // display login screen
    ui.displayLoginScreen();
 
    // get username and password from UserInterface
    std::string username = ui.getUsernameInput();
    std::string password = ui.getPasswordInput();


    // attempt login using Login class
    if (login.login(username, password)) {
        ui.displaySuccessfulLogin();  // display success message if login works
    }
    else {
        ui.displayUnsuccessfulLogin();  // display failure message if login fails
    }
  
    return 0;
}
