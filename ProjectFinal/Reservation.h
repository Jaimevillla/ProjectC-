// Reservation.h
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation {
private:
    static int idCounter;
    int reservationId;
    int roomNumber;
    std::string guestName;

public:
    Reservation(int roomNum, const std::string& guest);
    ~Reservation();

    int getReservationId() const;
    int getRoomNumber() const;
    std::string getGuestName() const;
};

#endif // RESERVATION_H