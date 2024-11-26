#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <limits>
#include <windows.h>
#include<algorithm>


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

    void setSeats(int newSeatCount) {
        seats = newSeatCount;
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

// Function to add a new flight to the system
void addFlight(vector<shared_ptr<Airline>>& flights) {
    string flightNumber, destination, departure;
    int seats;

    cout << "Enter Flight Number: ";
    cin >> flightNumber;
    cout << "Enter Destination: ";
    cin >> destination;
    cout << "Enter Departure: ";
    cin >> departure;
    cout << "Enter Number of Seats: ";
    cin >> seats;

    flights.push_back(make_shared<Airline>(flightNumber, destination, departure, seats));
    saveFlightsToFile(flights);  // Save the updated list of flights to file
    cout << "New flight added successfully!" << endl;
}

// Function to remove a flight from the system
void removeFlight(vector<shared_ptr<Airline>>& flights) {
    string flightNumber;
    cout << "Enter Flight Number to remove: ";
    cin >> flightNumber;

    auto it = remove_if(flights.begin(), flights.end(), [&flightNumber](const shared_ptr<Airline>& flight) {
        return flight->getFlight() == flightNumber;
    });

    if (it != flights.end()) {
        flights.erase(it, flights.end());
        saveFlightsToFile(flights);  // Save the updated list of flights to file
        cout << "Flight " << flightNumber << " removed successfully!" << endl;
    } else {
        cout << "Flight not found!" << endl;
    }
}

// Function to update the seat count of a flight
void updateSeatCount(vector<shared_ptr<Airline>>& flights) {
    string flightNumber;
    int newSeatCount;

    cout << "Enter Flight Number to update seats: ";
    cin >> flightNumber;

    // Find the flight with the given flight number
    for (auto& flight : flights) {
        if (flight->getFlight() == flightNumber) {
            cout << "Current seat count: " << flight->getSeats() << endl;
            cout << "Enter new seat count: ";
            cin >> newSeatCount;
            flight->setSeats(newSeatCount);  // Update the seat count

            flight->updateSeatCountInFile();  // Update seat count in file
            cout << "Seat count updated successfully!" << endl;
            return;
        }
    }

    cout << "Flight not found!" << endl;
}

void adminPanel(vector<shared_ptr<Airline>>& flights) {
    int choice;
    while (true) {
        system("cls");
        cout << "Admin Panel:\n";
        cout << "1. Add New Flight\n";
        cout << "2. Remove Flight\n";
        cout << "3. Update Flight Seat Count\n";
        cout << "4. Exit Admin Panel\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addFlight(flights);
                break;
            case 2:
                removeFlight(flights);
                break;
            case 3:
                updateSeatCount(flights);
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again!" << endl;
                break;
        }
    }
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
        cout << "\t 5. Admin Panel" << endl;
        cout << "\t 6. Exit" << endl;
        cout << "\t Enter Your Choice: ";
        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            Sleep(2000);
            continue;
        }

        switch (choice) {
            case 1:
                reserveSeat(flights);
                break;
            case 2:
                Airline::displayFlights();
                break;
            case 3:
                {
                    string destination;
                    cout << "Enter destination to search: ";
                    cin >> destination;
                    Airline::searchFlight(destination);
                    break;
                }
            case 4:
                cancelReservation(flights);
                break;
            case 5:
                adminPanel(flights);
                break;
            case 6:
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please try again!" << endl;
                break;
        }

        if (!exit) {
            cout << "\nPress any key to continue...";
            getchar();
            getchar(); // Wait for user input before continuing
        }
    }

    return 0;
}
