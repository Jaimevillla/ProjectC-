
// Room.h
#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
protected:
    int roomNumber;
    int capacity;
    bool isAvailable;

public:
    Room(int number, int cap);
    virtual ~Room();

    int getRoomNumber() const;
    int getCapacity() const;
    bool getAvailability() const;
    void setAvailability(bool availability);

    virtual double calculateCost() const = 0; 
    virtual std::string getRoomType() const = 0;
};

#endif // ROOM_H