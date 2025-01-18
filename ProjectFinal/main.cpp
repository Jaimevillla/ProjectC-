// main.cpp
#include "HotelReservationSystem.h"
#include <iostream>
#include <fstream>

void displayMenu() {
    std::cout << "\n=== Hotel Reservation System ===\n";
    std::cout << "1. Make a reservation\n";
    std::cout << "2. Cancel a reservation\n";
    std::cout << "3. List available rooms\n";
    std::cout << "4. List all reservations\n";
    std::cout << "5. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    HotelReservationSystem system;
    int choice;

    while(true) {
        displayMenu();
        std::cin >> choice;

        try {
            if(std::cin.fail()) {
                throw std::invalid_argument("Invalid input. Please enter a number.");
            }

            switch(choice) {
                case 1:
                    system.makeReservation();
                    break;
                case 2:
                    system.cancelReservation();
                    break;
                case 3:
                    system.listAvailableRooms();
                    break;
                case 4:
                    system.listAllReservations();
                    break;
                case 5:
                    std::cout << "Exiting the system. Goodbye!\n";
                    return 0;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        } catch(const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
        }
    }

    return 0;
}