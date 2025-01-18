// HotelReservationSystem.cpp
#include "HotelReservationSystem.h"
#include "StandardRoom.h"
#include "Suite.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <fstream>

// Initialize the Reservation ID counter
int Reservation::idCounter = 1;

// Implementation of the Room class
Room::Room(int number, int cap)
    : roomNumber(number), capacity(cap), isAvailable(true) {}

Room::~Room() {}

int Room::getRoomNumber() const {
    return roomNumber;
}

int Room::getCapacity() const {
    return capacity;
}

bool Room::getAvailability() const {
    return isAvailable;
}

void Room::setAvailability(bool availability) {
    isAvailable = availability;
}

// Implementation of the StandardRoom class
const double StandardRoom::baseRate = 100.0;

StandardRoom::StandardRoom(int number, int cap)
    : Room(number, cap) {}

StandardRoom::~StandardRoom() {}

double StandardRoom::calculateCost() const {
    return baseRate;
}

std::string StandardRoom::getRoomType() const {
    return "Standard";
}

// Implementation of the Suite class
const double Suite::baseRate = 200.0;

Suite::Suite(int number, int cap)
    : Room(number, cap) {}

Suite::~Suite() {}

double Suite::calculateCost() const {
    return baseRate;
}

std::string Suite::getRoomType() const {
    return "Suite";
}

// Implementation of the Reservation class
Reservation::Reservation(int roomNum, const std::string& guest)
    : reservationId(idCounter++), roomNumber(roomNum), guestName(guest) {}

Reservation::~Reservation() {}

int Reservation::getReservationId() const {
    return reservationId;
}

int Reservation::getRoomNumber() const {
    return roomNumber;
}

std::string Reservation::getGuestName() const {
    return guestName;
}

// Implementation of the HotelReservationSystem class
HotelReservationSystem::HotelReservationSystem() {
    initializeRooms();
}

HotelReservationSystem::~HotelReservationSystem() {
    // Free memory for the rooms
    for(auto room : rooms) {
        delete room;
    }
}

void HotelReservationSystem::initializeRooms() {
    // For example, 10 standard rooms and 5 suites
    for(int i = 101; i <= 110; ++i) {
        rooms.push_back(new StandardRoom(i, 2));
    }
    for(int i = 201; i <= 205; ++i) {
        rooms.push_back(new Suite(i, 4));
    }
}

void HotelReservationSystem::makeReservation() {
    if (std::none_of(rooms.begin(), rooms.end(), [](Room* room) { return room->getAvailability(); })) {
        std::cout << "No rooms are available for reservation.\n";
        return;
    }

    std::cout << "Available rooms:\n";
    for (auto room : rooms) {
        if (room->getAvailability()) {
            std::cout << "Room number: " << room->getRoomNumber() 
                      << " (Type: " << room->getRoomType() 
                      << ", Capacity: " << room->getCapacity() 
                      << ", Cost: $" << room->calculateCost() << ")\n";
        }
    }

    int roomNumber;
    std::string guestName;

    std::cout << "Enter the room number: ";
    std::cin >> roomNumber;

    // Verify if the room exists and is available
    auto it = std::find_if(rooms.begin(), rooms.end(),
                           [roomNumber](Room* room) { return room->getRoomNumber() == roomNumber; });

    if (it != rooms.end()) {
        if ((*it)->getAvailability()) {
            std::cout << "Enter the guest name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
            std::getline(std::cin, guestName);

            reservations.emplace_back(roomNumber, guestName);
            (*it)->setAvailability(false);
            std::cout << "Reservation successfully created. Reservation ID: " 
                      << reservations.back().getReservationId() << "\n";
        } else {
            std::cout << "The room is not available.\n";
        }
    } else {
        std::cout << "Invalid room number.\n";
    }
}

void HotelReservationSystem::cancelReservation() {
    int reservationId;
    std::cout << "Enter the reservation ID to cancel: ";
    std::cin >> reservationId;

    auto it = std::find_if(reservations.begin(), reservations.end(),
                           [reservationId](const Reservation& res) { return res.getReservationId() == reservationId; });

    if(it != reservations.end()) {
        // Mark the room as available
        auto roomIt = std::find_if(rooms.begin(), rooms.end(),
                                   [it](Room* room) { return room->getRoomNumber() == it->getRoomNumber(); });

        if(roomIt != rooms.end()) {
            (*roomIt)->setAvailability(true);
        }

        reservations.erase(it);
        std::cout << "Reservation successfully canceled.\n";
    } else {
        std::cout << "Reservation ID not found.\n";
    }
}

void HotelReservationSystem::listAvailableRooms() {
    std::cout << "Available rooms:\n";
    std::cout << "Number\tType\tCapacity\tCost\n";
    for(auto room : rooms) {
        if(room->getAvailability()) {
            std::cout << room->getRoomNumber() << "\t" 
                      << room->getRoomType() << "\t" 
                      << room->getCapacity() << "\t\t" 
                      << room->calculateCost() << "\n";
        }
    }
}

void HotelReservationSystem::listAllReservations() {
    if(reservations.empty()) {
        std::cout << "No reservations found.\n";
        return;
    }

    std::cout << "List of reservations:\n";
    std::cout << "ID\tRoom\tGuest\n";
    for(const auto& res : reservations) {
        std::cout << res.getReservationId() << "\t" 
                  << res.getRoomNumber() << "\t\t" 
                  << res.getGuestName() << "\n";
    }
}