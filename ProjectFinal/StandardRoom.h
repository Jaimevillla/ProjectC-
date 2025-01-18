// StandardRoom.h
#ifndef STANDARDROOM_H
#define STANDARDROOM_H

#include "Room.h"

class StandardRoom : public Room {
private:
    static const double baseRate;

public:
    StandardRoom(int number, int cap);
    ~StandardRoom();

    double calculateCost() const override;
    std::string getRoomType() const override;
};

#endif // STANDARDROOM_H