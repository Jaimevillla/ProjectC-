
// HotelReservationSystem.h
#ifndef HOTELRESERVATIONSYSTEM_H
#define HOTELRESERVATIONSYSTEM_H

#include <vector>
#include "Room.h"
#include "Reservation.h"

class HotelReservationSystem {
private:
    std::vector<Room*> rooms;
    std::vector<Reservation> reservations;

    void initializeRooms(); 

public:
    HotelReservationSystem();
    ~HotelReservationSystem();

    void makeReservation();
    void cancelReservation();
    void listAvailableRooms();
    void listAllReservations();
};

#endif // HOTELRESERVATIONSYSTEM_H