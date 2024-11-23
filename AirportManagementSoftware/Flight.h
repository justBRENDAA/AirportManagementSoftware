#ifndef FLIGHT_H;
#define FLIGHT_H;

#include <string>;

class Flight{
public:
	int flightNumber;
	std::string flightGate;
	std::string flightDestination;
	std::string flightStatus;
	std::string flightCredentials;
	float flightTime;

	bool find(int number, const std::string& gate, float time) const;
	void obtainInput();
	void displayFlightDetails() const;
};

#endif
