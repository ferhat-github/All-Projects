#ifndef ASSIGNMENT2_BUILDING_H
#define ASSIGNMENT2_BUILDING_H

#include "Office.h"
#include "Classroom.h"

class Building {
private:
    char* name;
    int sizeInSquareMeters;
    Room* rooms[100];
    int numberOfRooms;

public:
    Building();
    Building(const char*, int);
    ~Building();
    Building(const Building&);
    Building& operator=(const Building&);
    void setName(const char*);
    void setSize(int);
    const char* getName() const;
    int getSize() const;
    int getNumberOfRooms() const;


    void addRoom(const char*, int, int);
    void addRoom(const char*, int, int, int);


    void printBuilding() const;
    void printRooms() const;
    void printRoomsByType(int type) const;

    int getNumberOfClassrooms() const;
    int getNumberOfOffices() const;
    int getTotalCapacity() const;
    void printAvailableOffices() const;
    void printSuitableClassrooms(int numStudents) const;

};

#endif //ASSIGNMENT2_BUILDING_H
