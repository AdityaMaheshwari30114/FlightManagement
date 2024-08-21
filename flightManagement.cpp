#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <limits>
#include <windows.h>

using namespace std;

class Airline {
private:
    string flightNumber, destination, departure;
    int seats;

public:
    Airline(string flight, string des, string dep, int seats)
        : flightNumber(flight), destination(des), departure(dep), seats(seats) {}

    string getFlight() const {
        return flightNumber;
    }

    string getDestination() const {
        return destination;
    }

    string getDeparture() const {
        return departure;
    }

    int getSeats() const {
        return seats;
    }

    void reserveSeat() {
        if (seats > 0) {
            seats--;
        } else {
            throw runtime_error("No available seats to reserve.");
        }
    }

    void cancelReservation() {
        seats++;
    }

    void updateSeatCountInFile() const {
        ifstream inFile("Flight.txt");
        if (!inFile) {
            throw runtime_error("Error opening the input file.");
        }

        ofstream outFile("FlightTemp.txt");
        if (!outFile) {
            throw runtime_error("Error opening the output file.");
        }

        string line;
        while (getline(inFile, line)) {
            if (line.find(flightNumber) != string::npos) {
                stringstream ss;
                ss << flightNumber << " : " << destination << " : " << departure << " : " << seats;
                outFile << ss.str() << endl;
            } else {
                outFile << line << endl;
            }
        }

        inFile.close();
        outFile.close();

        remove("Flight.txt");
        rename("FlightTemp.txt", "Flight.txt");
    }

    static void displayFlights() {
        ifstream inFile("Flight.txt");
        if (!inFile) {
            throw runtime_error("Error: Unable to open file.");
        }

        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
    }

    static void searchFlight(const string& destination) {
        ifstream inFile("Flight.txt");
        if (!inFile) {
            throw runtime_error("Error: Unable to open file.");
        }

        string line;
        bool found = false;
        while (getline(inFile, line)) {
            if (line.find(destination) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No flights found for the destination: " << destination << endl;
        }
    }
};

void saveFlightsToFile(const vector<shared_ptr<Airline>>& flights) {
    ofstream outFile("Flight.txt");
    if (!outFile) {
        throw runtime_error("Error: Unable to open file for writing.");
    }

    for (const auto& flight : flights) {
        outFile << flight->getFlight() << " : "
                << flight->getDestination() << " : "
                << flight->getDeparture() << " : "
                << flight->getSeats() << endl;
    }
    outFile.close();
    cout << "Data saved successfully!" << endl;
}

void reserveSeat(const vector<shared_ptr<Airline>>& flights) {
    string flightNumber;
    cout << "Enter Flight Number: ";
    cin >> flightNumber;

    for (auto& flight : flights) {
        if (flight->getFlight() == flightNumber) {
            try {
                flight->reserveSeat();
                flight->updateSeatCountInFile();
                cout << "Seat reserved successfully!" << endl;
            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            return;
        }
    }
    cout << "Flight not found!" << endl;
}

void cancelReservation(const vector<shared_ptr<Airline>>& flights) {
    string flightNumber;
    cout << "Enter Flight Number: ";
    cin >> flightNumber;

    for (auto& flight : flights) {
        if (flight->getFlight() == flightNumber) {
            flight->cancelReservation();
            flight->updateSeatCountInFile();
            cout << "Reservation cancelled successfully!" << endl;
            return;
        }
    }
    cout << "Flight not found!" << endl;
}

int main() {
    vector<shared_ptr<Airline>> flights = {
        make_shared<Airline>("F401", "New York", "Los Angeles", 150),
        make_shared<Airline>("F502", "Chicago", "Miami", 120),
        make_shared<Airline>("F603", "San Francisco", "New York", 200),
        make_shared<Airline>("F704", "Dallas", "Seattle", 100),
        make_shared<Airline>("F805", "Boston", "Las Vegas", 80),
        make_shared<Airline>("F906", "Denver", "Houston", 90),
        make_shared<Airline>("F1007", "Atlanta", "Washington D.C.", 70),
        make_shared<Airline>("F1108", "Orlando", "Phoenix", 60)
    };

    saveFlightsToFile(flights);

    bool exit = false;
    while (!exit) {
        system("cls");
        cout << "\t Welcome to Airline Management System" << endl;
        cout << "\t ************************************" << endl;
        cout << "\t 1. Reserve a Seat" << endl;
        cout << "\t 2. Display Available Flights" << endl;
        cout << "\t 3. Search for a Flight by Destination" << endl;
        cout << "\t 4. Cancel a Reservation" << endl;
        cout << "\t 5. Exit" << endl;
        cout << "\t Enter Your Choice: ";
        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            Sleep(2000);
            continue;
        }

        switch (choice) {
        case 1:
            Airline::displayFlights();
            reserveSeat(flights);
            Sleep(3000);
            break;
        case 2:
            Airline::displayFlights();
            Sleep(3000);
            break;
        case 3: {
            string destination;
            cout << "Enter Destination: ";
            cin >> destination;
            Airline::searchFlight(destination);
            Sleep(3000);
            break;
        }
        case 4:
            cancelReservation(flights);
            Sleep(3000);
            break;
        case 5:
            exit = true;
            cout << "Thank you for using the Airline Management System. Goodbye!" << endl;
            Sleep(3000);
            break;
        }
    }

    return 0;
}
