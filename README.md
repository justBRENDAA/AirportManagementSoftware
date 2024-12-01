# AirportManagementSoftware

SQL QUERIES TO SETUP AND POPULATE TABLES

-- Users Table

CREATE TABLE Users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password_hash VARCHAR(255) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE, -- Enforce unique emails
    phone_number VARCHAR(15),
    user_type ENUM('Passenger', 'Staff', 'Security') NOT NULL
);

-- Airports Table

CREATE TABLE Airports (
    airport_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    location VARCHAR(100) NOT NULL
);

-- Passengers Table
CREATE TABLE Passengers (
    passenger_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    passport_number VARCHAR(20) UNIQUE,
    FOREIGN KEY (user_id) REFERENCES Users(user_id) -- Link to Users table
);

-- Flights Table
CREATE TABLE Flights (
    flight_id INT AUTO_INCREMENT PRIMARY KEY,
    flight_number VARCHAR(20) NOT NULL UNIQUE,
    departure_time DATETIME NOT NULL,
    arrival_time DATETIME NOT NULL,
    origin_airport_id INT NOT NULL,
    destination_airport_id INT NOT NULL,
    capacity INT NOT NULL,
    FOREIGN KEY (origin_airport_id) REFERENCES Airports(airport_id),
    FOREIGN KEY (destination_airport_id) REFERENCES Airports(airport_id)
);

-- PassengerFlight Table (Relationship between passengers and flights)
CREATE TABLE PassengerFlight (
    id INT AUTO_INCREMENT PRIMARY KEY,
    passenger_id INT NOT NULL,
    flight_id INT NOT NULL,
    FOREIGN KEY (passenger_id) REFERENCES Passengers(passenger_id),
    FOREIGN KEY (flight_id) REFERENCES Flights(flight_id),
    UNIQUE(passenger_id, flight_id) -- Prevent duplicate entries for the same passenger on the same flight
);

-- Luggage Table
CREATE TABLE Luggage (
    luggage_id INT AUTO_INCREMENT PRIMARY KEY,
    passenger_id INT NOT NULL,
    flight_id INT NOT NULL,
    location VARCHAR(100) NOT NULL,
    FOREIGN KEY (passenger_id) REFERENCES Passengers(passenger_id),
    FOREIGN KEY (flight_id) REFERENCES Flights(flight_id)
);

-- Staff Table
CREATE TABLE Staff (
    staff_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    position VARCHAR(50),
    FOREIGN KEY (user_id) REFERENCES Users(user_id) -- Link to Users table
);

-- Security Table
CREATE TABLE Security (
    security_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    security_clearance BOOLEAN NOT NULL DEFAULT FALSE,  -- TRUE if clearance granted, FALSE otherwise
    FOREIGN KEY (user_id) REFERENCES Users(user_id) -- Link to Users table
);

-- Support Requests Table
CREATE TABLE SupportRequests (
    request_id INT AUTO_INCREMENT PRIMARY KEY,
    passenger_id INT NOT NULL,
    description TEXT NOT NULL,
    status ENUM('Pending', 'Resolved', 'Escalated') DEFAULT 'Pending',
    FOREIGN KEY (passenger_id) REFERENCES Passengers(passenger_id)
);

-- Threats Table
CREATE TABLE Threats (
    threat_id INT AUTO_INCREMENT PRIMARY KEY,
    description TEXT NOT NULL,
    threat_level INT NOT NULL,
    location VARCHAR(100) NOT NULL,
    timestamp DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Maps Table
CREATE TABLE Maps (
    map_id INT AUTO_INCREMENT PRIMARY KEY,
    airport_id INT NOT NULL,
    terminal_name VARCHAR(100),
    gate_number VARCHAR(20),
    FOREIGN KEY (airport_id) REFERENCES Airports(airport_id)
);


INSERT INTO Airports (name, location) VALUES
('Houston International Airport', 'Houston, TX'),
('Chicago International Airport', 'Chicago, IL'),
('Los Angeles International Airport', 'Los Angeles, CA'),
('Florida International Airport', 'Orlando, FL'),
('San Francisco International Airport', 'San Francisco, CA');

-- inserting passengers into users table
INSERT INTO Users (username, password_hash, email, phone_number, user_type) VALUES
('bluis1', '123', 'brenda@email.com', '832-111-2222', 'Passenger'),
('mgrey1', '123', 'meredith@email.com', '123-555-7890', 'Passenger'),
('akarev1', '123', 'alex@email.com', '123-555-7891', 'Passenger'),
('cyang1', '123', 'christina@email.com', '123-555-7892', 'Passenger'),
('dshep1', '123', 'derek@email.com', '123-555-7893', 'Passenger'),
('lgray1', '123', 'lexie@email.com', '123-555-7894', 'Passenger'),
('rwebber1', '123', 'webber@email.com', '713-555-7894', 'Passenger'),
('mbailey1', '123', 'miranda@email.com', '713-555-7894', 'Passenger'),
('arobbins', '123', 'arizona@email.com', '832-555-7894', 'Passenger'),
('ashep1', '123', 'amelia@email.com', '346-555-7894', 'Passenger'),
('mpierce1', '123', 'maggie@email.com', '713-555-7894', 'Passenger'),
('pburke', '123', 'preston@email.com', '346-555-7894', 'Passenger'),
('tgrey1', '123', 'thatcher@email.com', '832-555-7894', 'Passenger'),
('awebber1', '123', 'adele@email.com', '713-555-7894', 'Passenger'),
('alincoln1', '123', 'atticus@email.com', '713-555-7894', 'Passenger'),
('zshep1', '123', 'zola@email.com', '832-555-7894', 'Passenger'),
('bstinson1', '123', 'barney@email.com', '346-555-7894', 'Passenger'),
('tmosby1', '123', 'ted@email.com', '713-555-7894', 'Passenger'),
('rscherb1', '123', 'robin@email.com', '346-555-7894', 'Passenger'),
('laldrin', '123', 'lily@email.com', '832-555-7894', 'Passenger'),
('mericksen1', '123', 'marshall@email.com', '713-555-7894', 'Passenger'),
('srivers1', '123', 'sandy@email.com', '713-555-7894', 'Passenger'),
('ktakakura1', '123', 'ken@email.com', '832-555-7894', 'Passenger'),
('mayase1', '123', 'momo@email.com', '346-555-7894', 'Passenger'),
('sayase1', '123', 'seiko@email.com', '713-555-7894', 'Passenger'),
('tgranny1', '123', 'turbo@email.com', '346-555-7894', 'Passenger'),
('ashiratori1', '123', 'aira@email.com', '832-555-7894', 'Passenger');

-- inserting passengers from users table into passengers table 
INSERT INTO Passengers (user_id, first_name, last_name, passport_number)
VALUES
((SELECT user_id FROM Users WHERE username = 'bluis1'), 'Brenda', 'Luis', 'P12345678'),
((SELECT user_id FROM Users WHERE username = 'mgrey1'), 'Meredith', 'Grey', 'P22334455'),
((SELECT user_id FROM Users WHERE username = 'akarev1'), 'Alex', 'Karev', 'P33445566'),
((SELECT user_id FROM Users WHERE username = 'cyang1'), 'Christina', 'Yang', 'P44556677'),
((SELECT user_id FROM Users WHERE username = 'dshep1'), 'Derek', 'Shepherd', 'P55667788'),
((SELECT user_id FROM Users WHERE username = 'lgray1'), 'Lexie', 'Grey', 'P66778899'),
((SELECT user_id FROM Users WHERE username = 'rwebber1'), 'Richard', 'Webber', 'P77889900'),
((SELECT user_id FROM Users WHERE username = 'mbailey1'), 'Miranda', 'Bailey', 'P88990011'),
((SELECT user_id FROM Users WHERE username = 'arobbins'), 'Arizona', 'Robbins', 'P99001122'),
((SELECT user_id FROM Users WHERE username = 'ashep1'), 'Amelia', 'Shepherd', 'P10111213'),
((SELECT user_id FROM Users WHERE username = 'mpierce1'), 'Maggie', 'Pierce', 'P11121314'),
((SELECT user_id FROM Users WHERE username = 'pburke'), 'Preston', 'Burke', 'P12131415'),
((SELECT user_id FROM Users WHERE username = 'tgrey1'), 'Thatcher', 'Grey', 'P13141516'),
((SELECT user_id FROM Users WHERE username = 'awebber1'), 'Adele', 'Webber', 'P14151617'),
((SELECT user_id FROM Users WHERE username = 'alincoln1'), 'Atticus', 'Lincoln', 'P15161718'),
((SELECT user_id FROM Users WHERE username = 'zshep1'), 'Zola', 'Shepherd', 'P16171819'),
((SELECT user_id FROM Users WHERE username = 'bstinson1'), 'Barney', 'Stinson', 'P17181920'),
((SELECT user_id FROM Users WHERE username = 'tmosby1'), 'Ted', 'Mosby', 'P18192021'),
((SELECT user_id FROM Users WHERE username = 'rscherb1'), 'Robin', 'Scherbatsky', 'P19202122'),
((SELECT user_id FROM Users WHERE username = 'laldrin'), 'Lily', 'Aldrin', 'P20212223'),
((SELECT user_id FROM Users WHERE username = 'mericksen1'), 'Marshall', 'Ericksen', 'P21222324'),
((SELECT user_id FROM Users WHERE username = 'srivers1'), 'Sandy', 'Rivers', 'P22232425'),
((SELECT user_id FROM Users WHERE username = 'ktakakura1'), 'Ken', 'Takakura', 'P23242526'),
((SELECT user_id FROM Users WHERE username = 'mayase1'), 'Momo', 'Yamase', 'P24252627'),
((SELECT user_id FROM Users WHERE username = 'sayase1'), 'Seiko', 'Ayase', 'P25262728'),
((SELECT user_id FROM Users WHERE username = 'tgranny1'), 'Turbo', 'Granny', 'P26272829'),
((SELECT user_id FROM Users WHERE username = 'ashiratori1'), 'Aira', 'Shiratori', 'P27282930');

-- insert staff into users table 
INSERT INTO Users (username, password_hash, email, phone_number, user_type) VALUES
('bwaldorf', '123', 'blair@email.com', '713-111-1111', 'Staff'),
('narchi', '123', 'nate@email.com', '713-222-2222', 'Staff'),
('dhumphrey', '123', 'dan@email.com', '713-333-3333', 'Staff'),
('svander', '123', 'serena@email.com', '713-444-4444', 'Staff'),
('jhumph', '123', 'jenny@email.com', '713-555-5555', 'Staff'),
('lbass', '123', 'lilybass@email.com', '713-666-6666', 'Staff'),
('cbass', '123', 'chuck@email.com', '713-777-7777', 'Staff'),
('evander', '123', 'eric@email.com', '713-888-8888', 'Staff'),
('gsparks', '123', 'georgina@email.com', '713-999-9999', 'Staff'),
('ewaldorf', '123', 'eleanor@email.com', '713-101-0101', 'Staff'),
('warchibald', '123', 'william@email.com', '713-121-2121', 'Staff'),
('rbass', '123', 'russell@email.com', '713-131-3131', 'Staff'),
('cvanderbilt', '123', 'cyrus@email.com', '713-141-4141', 'Staff'),
('tsharp', '123', 'tripp@email.com', '713-151-5151', 'Staff'),
('bbass', '123', 'bart@email.com', '713-161-6161', 'Staff'),
('dorota1', '123', 'dorota@email.com', '713-171-7171', 'Staff'),
('apreston', '123', 'agnes@email.com', '713-181-8181', 'Staff'),
('hgrimaldi', '123', 'hannah@email.com', '713-191-9191', 'Staff'),
('epayton', '123', 'emma@email.com', '713-202-0202', 'Staff'),
('mvenetis', '123', 'maxwell@email.com', '713-212-1212', 'Staff'),
('kporter', '123', 'kate@email.com', '713-232-2323', 'Staff'),
('rmeyer', '123', 'raina@email.com', '713-242-4242', 'Staff'),
('dmarshall', '123', 'damien@email.com', '713-252-5252', 'Staff'),
('ldesmond', '123', 'laurel@email.com', '713-262-6262', 'Staff'),
('mlevine', '123', 'maureen@email.com', '713-272-7272', 'Staff'),
('vnelson', '123', 'vanessa@email.com', '713-282-8282', 'Staff'),
('cbuckley', '123', 'carol@email.com', '713-292-9292', 'Staff');

-- Insert staff from users into staff table (Gossip Girl characters)
INSERT INTO Staff (user_id, first_name, last_name, position) VALUES
((SELECT user_id FROM Users WHERE username = 'bwaldorf'), 'Blair', 'Waldorf', 'Manager'),
((SELECT user_id FROM Users WHERE username = 'narchi'), 'Nate', 'Archibald', 'Assistant Manager'),
((SELECT user_id FROM Users WHERE username = 'dhumphrey'), 'Dan', 'Humphrey', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'svander'), 'Serena', 'Vanderwoodsen', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'jhumph'), 'Jenny', 'Humphrey', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'lbass'), 'Lily', 'Bass', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'cbass'), 'Chuck', 'Bass', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'evander'), 'Eric', 'Vanderwoodsen', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'gsparks'), 'Georgina', 'Sparks', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'ewaldorf'), 'Eleanor', 'Waldorf', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'warchibald'), 'William', 'Archibald', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'rbass'), 'Russell', 'Bass', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'cvanderbilt'), 'Cyrus', 'Vanderbilt', 'Supervisor'),
((SELECT user_id FROM Users WHERE username = 'tsharp'), 'Tripp', 'Sharp', 'Support'),
((SELECT user_id FROM Users WHERE username = 'bbass'), 'Bart', 'Bass', 'Support'),
((SELECT user_id FROM Users WHERE username = 'dorota1'), 'Dorota', 'Zbornak', 'Support'),
((SELECT user_id FROM Users WHERE username = 'apreston'), 'Agnes', 'Preston', 'Support'),
((SELECT user_id FROM Users WHERE username = 'hgrimaldi'), 'Hannah', 'Grimaldi', 'Support'),
((SELECT user_id FROM Users WHERE username = 'epayton'), 'Emma', 'Payton', 'Support'),
((SELECT user_id FROM Users WHERE username = 'mvenetis'), 'Maxwell', 'Venetis', 'Ticketing'),
((SELECT user_id FROM Users WHERE username = 'kporter'), 'Kate', 'Porter', 'Ticketing'),
((SELECT user_id FROM Users WHERE username = 'rmeyer'), 'Raina', 'Meyer', 'Ticketing'),
((SELECT user_id FROM Users WHERE username = 'dmarshall'), 'Damien', 'Marshall', 'Ticketing'),
((SELECT user_id FROM Users WHERE username = 'ldesmond'), 'Laurel', 'Desmond', 'Ticketing'),
((SELECT user_id FROM Users WHERE username = 'mlevine'), 'Maureen', 'Levine', 'Ticketing'),
((SELECT user_id FROM Users WHERE username = 'vnelson'), 'Vanessa', 'Nelson', 'Ticketing'),
((SELECT user_id FROM Users WHERE username = 'cbuckley'), 'Carol', 'Buckley', 'Ticketing');


-- Insert into Users table for security (Criminal Minds characters)
INSERT INTO Users (username, password_hash, email, phone_number, user_type) VALUES
('jjjareau', '456', 'jjjareau@email.com', '713-333-3333', 'Security'),
('ahotchner', '456', 'ahotchner@email.com', '713-444-4444', 'Security'),
('eprentiss', '456', 'eprentiss@email.com', '713-555-5555', 'Security'),
('penelopeg', '456', 'penelopeg@email.com', '713-666-6666', 'Security'),
('spencerreid', '456', 'spencerreid@email.com', '713-777-7777', 'Security');


-- Insert into Security table using SELECT to retrieve user_id
INSERT INTO Security (user_id, first_name, last_name, security_clearance)
VALUES
((SELECT user_id FROM Users WHERE username = 'jjjareau'), 'Jennifer', 'Jareau', TRUE),
((SELECT user_id FROM Users WHERE username = 'ahotchner'), 'Aaron', 'Hotchner', TRUE),  
((SELECT user_id FROM Users WHERE username = 'eprentiss'), 'Emily', 'Prentiss', TRUE), 
((SELECT user_id FROM Users WHERE username = 'penelopeg'), 'Penelope', 'Garcia', TRUE),
((SELECT user_id FROM Users WHERE username = 'spencerreid'), 'Spencer', 'Reid', TRUE);    

-- Flights
INSERT INTO Flights (flight_number, departure_time, arrival_time, origin_airport_id, destination_airport_id, capacity)
VALUES
('AA100', '2024-12-01 08:00:00', '2024-12-01 10:00:00', 1, 2, 180),  -- Houston to Chicago
('AA200', '2024-12-02 09:00:00', '2024-12-02 11:00:00', 2, 3, 180),  -- Chicago to Los Angeles
('AA300', '2024-12-03 10:00:00', '2024-12-03 12:00:00', 3, 4, 180),  -- Los Angeles to Florida
('AA400', '2024-12-04 11:00:00', '2024-12-04 13:00:00', 4, 5, 180),  -- Florida to San Francisco
('AA500', '2024-12-05 12:00:00', '2024-12-05 14:00:00', 5, 1, 180);  -- San Francisco to Houston

-- assign passengers to the flights 
INSERT INTO PassengerFlight (passenger_id, flight_id)
VALUES
(1, 1),   -- Brenda Luis on Flight AA100 (Houston to Chicago)
(2, 1),   -- Meredith Grey on Flight AA100
(3, 1),   -- Alex Karev on Flight AA100
(4, 1),   -- Christina Yang on Flight AA100
(5, 2),   -- Derek Shepherd on Flight AA200 (Chicago to Los Angeles)
(6, 2),   -- Lexie Grey on Flight AA200
(7, 2),   -- Richard Webber on Flight AA200
(8, 2),   -- Miranda Bailey on Flight AA200
(9, 3),   -- Arizona Robbins on Flight AA300 (Los Angeles to Florida)
(10, 3),  -- Amelia Shepherd on Flight AA300
(11, 3),  -- Callie Torres on Flight AA300
(12, 3),  -- Owen Hunt on Flight AA300
(13, 4),  -- Jackson Avery on Flight AA400 (Florida to San Francisco)
(14, 4),  -- April Kepner on Flight AA400
(15, 4),  -- Maggie Pierce on Flight AA400
(16, 4),  -- Joe Wilson on Flight AA400
(17, 5),  -- Miranda Bailey on Flight AA500 (San Francisco to Houston)
(18, 5),  -- Alex Karev on Flight AA500
(19, 5),  -- Owen Hunt on Flight AA500
(20, 5);  -- Derek Shepherd on Flight AA500


INSERT INTO Luggage (passenger_id, flight_id, location)
VALUES
(1, 1, 'Houston'),   -- Brenda Luis, Flight AA100, Houston
(2, 1, 'Houston'),   -- Meredith Grey, Flight AA100, Houston
(3, 1, 'Houston'),   -- Alex Karev, Flight AA100, Houston
(4, 1, 'Houston'),   -- Christina Yang, Flight AA100, Houston
(5, 2, 'Chicago'),   -- Derek Shepherd, Flight AA200, Chicago
(6, 2, 'Chicago'),   -- Lexie Grey, Flight AA200, Chicago
(7, 2, 'Chicago'),   -- Richard Webber, Flight AA200, Chicago
(8, 2, 'Chicago'),   -- Miranda Bailey, Flight AA200, Chicago
(9, 3, 'Los Angeles'),   -- Arizona Robbins, Flight AA300, Los Angeles
(10, 3, 'Los Angeles'),  -- Amelia Shepherd, Flight AA300, Los Angeles
(11, 3, 'Los Angeles'),  -- Callie Torres, Flight AA300, Los Angeles
(12, 3, 'Los Angeles'),  -- Owen Hunt, Flight AA300, Los Angeles
(13, 4, 'Florida'),  -- Jackson Avery, Flight AA400, Florida
(14, 4, 'Florida'),  -- April Kepner, Flight AA400, Florida
(15, 4, 'Florida'),  -- Maggie Pierce, Flight AA400, Florida
(16, 4, 'Florida'),  -- Joe Wilson, Flight AA400, Florida
(17, 5, 'San Francisco'),  -- Miranda Bailey, Flight AA500, San Francisco
(18, 5, 'San Francisco'),  -- Alex Karev, Flight AA500, San Francisco
(19, 5, 'San Francisco'),  -- Owen Hunt, Flight AA500, San Francisco
(20, 5, 'San Francisco');  -- Derek Shepherd, Flight AA500, San Francisco
