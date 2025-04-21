#ifndef ASSIGNMENT2_OFFICE_H
#define ASSIGNMENT2_OFFICE_H
#include "Room.h"



class Office : public Room {
private:
    OfficeType officeType;
    int numberOfPeople;

public:
    Office();
    Office(const char*, int, OfficeType, int);
    virtual ~Office();

    void setOfficeType(OfficeType);
    void setNumberOfPeople(int);
    OfficeType getOfficeType() const;
    int getNumberOfPeople() const;

    bool isFull() const;
    int getCapacity() const;
    void printRoom() const;

    //Helper function to distinguish whether it is a Office(with 2) or Class(with 1);
    int getType() const;
};

#endif //ASSIGNMENT2_OFFICE_H

