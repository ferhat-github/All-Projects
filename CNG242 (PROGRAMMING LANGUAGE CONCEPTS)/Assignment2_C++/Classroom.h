#ifndef ASSIGNMENT2_CLASSROOM_H
#define ASSIGNMENT2_CLASSROOM_H

#include "Room.h"

class Classroom : public Room {
private:
    int capacity;

public:
    Classroom();
    Classroom(const char*, int, int);
    virtual ~Classroom();

    void setCapacity(int capacity);
    int getCapacity() const;
    bool checkSuitability(int) const;
    void printRoom() const;

    //Helper function to distinguish whether it is a Office(with 2) or Class(with 1);
    int getType() const;
};

#endif //ASSIGNMENT2_CLASSROOM_H
