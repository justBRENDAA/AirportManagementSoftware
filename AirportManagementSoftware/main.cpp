#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <cstdlib>  // for getenv() (windows environment variable)

int main() {
    try {
        // Get the password from the environment variable securely
        char* password = nullptr;
        size_t length = 0;
        if (_dupenv_s(&password, &length, "MYSQL_PASSWORD") != 0 || password == nullptr) {
            std::cerr << "Error: MYSQL_PASSWORD environment variable not set!" << std::endl;
            return 1;
        }

        // used to create a MySQL driver instance
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", password);  // Use the password from the env variable
        
        //  connect("host name", "username", "password") 
        // tcp                     bc mysql uses tcp protocol to send and receive data over the network
        // 127.0.0.1 (localhost)   standard address for connecting mysql on personal machine (local computer)
        // 3306                    default port fo mysql (unless configured to use another port)
        
        
        // Print a success message if connected
        std::cout << "Connected to MySQL database!" << std::endl;

        delete con;  // close connection
        free(password); // free memory allocated by _dupenv_s
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
