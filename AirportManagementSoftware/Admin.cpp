//#include <cppconn/prepared_statement.h>
//#include <cppconn/resultset.h>
//#include <iostream>
//#include "Admin.h"//
//
//Admin::Admin(sql::Connection* existingCon, std::string user)
//{
//	con = existingCon;
//	username = user;
//}
//
//void Admin::displayOptions()
//{
//    char userContinue = 'N';
//    bool exitProgram = false;
//    do {
//        std::cout << "\n     ADMIN OPTIONS " << std::endl;
//        std::cout << "=========================" << std::endl;
//        std::cout << "1. Insert New Staff Member" << std::endl;
//        std::cout << "2. Insert New Security Member" << std::endl;
//        std::cout << "3. Delete Staff Member" << std::endl;
//        std::cout << "4. Delete Security Member" << std::endl;
//        std::cout << "5. Log Out" << std::endl;
//
//        int selection;
//
//        do {
//            selection = getIntInput();
//            setChoice(selection);
//
//            if (getChoice() == -1)
//                std::cout << "Please select a valid option(1-5): ";
//        } while (getChoice() == -1);
//
//        handleChoice(getChoice());
//
//        if (getChoice() == 5) {
//            exitProgram = true;
//        }
//
//        if (!exitProgram)
//        {
//            do {
//                std::cout << "Would you like select another Passenger option (Y/N)? ";
//                std::cin >> userContinue;
//                std::cout << std::endl;
//            } while (userContinue != 'Y' && userContinue != 'y' && userContinue != 'N' && userContinue != 'n');
//        }
//
//    } while (!exitProgram && (userContinue == 'Y' || userContinue == 'y'));
//
//    if (userContinue == 'n' || userContinue == 'N')
//        std::cout << "Logging out. . .\n";
//}
