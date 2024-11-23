#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Enumeration for threat types
enum ThreatType {
    UNAUTHORIZED_ACCESS,
    SUSPICIOUS_BEHAVIOR,
    INTRUSION_DETECTED,
    MALICIOUS_ACTIVITY
};

// Structure to represent a potential threat
struct Threat {
    int threatId;
    ThreatType type;
    string description;
    bool isHandled;  // Whether the threat has been handled or not

    // Constructor
    Threat(int id, ThreatType t, string desc) 
        : threatId(id), type(t), description(desc), isHandled(false) {}
};

// Class to simulate the Security System
class SecuritySystem {
private:
    vector<Threat> threatList;
    int threatCounter;

public:
    SecuritySystem() : threatCounter(1) {}

    // Function to simulate detecting a threat
    void detectThreat(ThreatType type, string description) {
        Threat newThreat(threatCounter++, type, description);
        threatList.push_back(newThreat);
        cout << "Threat detected! ID: " << newThreat.threatId << " - " << description << endl;
    }

    // Function to handle a threat and trigger an alert
    void handleThreat(int threatId) {
        for (auto& threat : threatList) {
            if (threat.threatId == threatId && !threat.isHandled) {
                threat.isHandled = true;
                cout << "\nAlert! Handling threat ID: " << threat.threatId << endl;
                cout << "Type: " << getThreatTypeName(threat.type) << endl;
                cout << "Description: " << threat.description << endl;

                // Simulate handling time
                this_thread::sleep_for(chrono::seconds(3));
                cout << "Threat ID: " << threat.threatId << " has been handled successfully!" << endl;
                return;
            }
        }
        cout << "Threat ID " << threatId << " not found or already handled!" << endl;
    }

    // Function to list all detected threats
    void listThreats() {
        if (threatList.empty()) {
            cout << "No threats detected." << endl;
            return;
        }

        cout << "\nListing all detected threats:\n";
        for (const auto& threat : threatList) {
            cout << "ID: " << threat.threatId
                << ", Type: " << getThreatTypeName(threat.type)
                << ", Description: " << threat.description
                << ", Handled: " << (threat.isHandled ? "Yes" : "No") << endl;
        }
    }

    // Helper function to get a string representation of the ThreatType enum
    string getThreatTypeName(ThreatType type) {
        switch (type) {
        case UNAUTHORIZED_ACCESS: return "Unauthorized Access";
        case SUSPICIOUS_BEHAVIOR: return "Suspicious Behavior";
        case INTRUSION_DETECTED: return "Intrusion Detected";
        case MALICIOUS_ACTIVITY: return "Malicious Activity";
        default: return "Unknown";
        }
    }

    // Function to check if there are any unhandled threats
    bool hasUnhandledThreats() {
        for (const auto& threat : threatList) {
            if (!threat.isHandled) {
                return true;
            }
        }
        return false;
    }
};

