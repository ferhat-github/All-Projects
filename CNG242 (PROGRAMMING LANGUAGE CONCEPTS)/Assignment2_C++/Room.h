#ifndef ASSIGNMENT2_ROOM_H
#define ASSIGNMENT2_ROOM_H
#include <cstring>
#include <iostream>
using namespace std;

enum OfficeType {
    None, CoordinatorOffice, StandardOffice, SharedOfficeFor2People, SharedOfficeFor3People, SharedOfficeFor10People
};


class Room {
protected:
    char* name;
    int floorNumber;

public:
    Room();
    Room(const char*, int);
    Room(const Room&);
    Room& operator=(const Room&);
    void setName(const char*);
    void setFloorNumber(int);
    const char* getName() const;
    int getFloorNumber() const;
    virtual void printRoom() const;
    virtual ~Room();




    //Note I implemented them so that I can use them for subclasses of Room class.
    virtual int getType() const;
    virtual int getCapacity() const;
    virtual bool isFull() const;
    virtual bool checkSuitability(int) const;
    virtual OfficeType getOfficeType() const;
    virtual int getNumberOfPeople() const;


};

#endif //ASSIGNMENT2_ROOM_H

