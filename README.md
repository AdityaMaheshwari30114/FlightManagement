# Flight Management System
The **Flight Management System**is a console-based application designed to streamline the management of airline flights. It provides features for users to reserve and cancel seats, search for flights, and view flight details. Administrators can manage flights, update seat counts, and add or remove flights from the system.

---

## Features

### User Features:
- **Reserve a Seat**: Passengers can reserve seats on available flights.
- **Cancel Reservation**: Cancel existing reservations easily.
- **View Available Flights**: Display all available flights with their details.
- **Search Flights**: Search for flights by destination.

### Admin Features:
- **Add New Flights**: Add flights with details like flight number, destination, departure, and seat count.
- **Remove Flights**: Remove flights from the system.
- **Update Seat Count**: Modify the number of seats for a specific flight.
- **Dynamic File Management**: Update flight information in real-time via file operations.

---

## File Structure
- **`Flight.txt`**: Stores flight information, updated dynamically during runtime.
- **flightManagement.cpp**: Contains all the logic for passenger and admin functionalities.

---

## Prerequisites
Ensure you have the following:
- A C++ compiler (e.g., GCC or Visual Studio).
- A Windows environment for compatibility with the `system("cls")` and `Sleep` functions.
- `Flight.txt` file in the same directory as the executable for data persistence.

---

## How to Run

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/AdityaMaheshwari30114/FlightManagementSystem.git
   ```

2. **Compile the Program**:
   ```bash
   g++ main.cpp -o FlightManagementSystem
   ```

3. **Run the Executable**:
   ```bash
   ./FlightManagementSystem
   ```

4. Follow the on-screen menu to access features.

---

## Menu Options
### Main Menu:
1. Reserve a Seat
2. Display Available Flights
3. Search for a Flight by Destination
4. Cancel a Reservation
5. Admin Panel
6. Exit

### Admin Panel:
1. Add New Flight
2. Remove Flight
3. Update Flight Seat Count
4. Exit Admin Panel

---

## Code Highlights
- **Object-Oriented Design**: The `Airline` class encapsulates flight details and operations.
- **Dynamic Memory Management**: Utilizes `shared_ptr` to manage flights.
- **File Handling**: Ensures flight data persistence using `Flight.txt`.
- **Error Handling**: Includes runtime error handling for robustness.
  
---

## Code Highlights
- Contributions are welcome! Feel free to fork the repository and submit a pull request.
---

