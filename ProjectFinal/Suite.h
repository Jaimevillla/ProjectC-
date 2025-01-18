// Suite.h
#ifndef SUITE_H
#define SUITE_H

#include "Room.h"

class Suite : public Room {
private:
    static const double baseRate;

public:
    Suite(int number, int cap);
    ~Suite();

    double calculateCost() const override;
    std::string getRoomType() const override;
};

#endif // SUITE_H