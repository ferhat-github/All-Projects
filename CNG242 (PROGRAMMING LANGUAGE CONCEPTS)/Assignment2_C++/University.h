#ifndef ASSIGNMENT2_UNIVERSITY_H
#define ASSIGNMENT2_UNIVERSITY_H

#include "Building.h"

class University {
private:
    char* name;
    Building* buildings[20];
    int numberOfBuildings;

public:
    University();
    University(const char*);
    virtual ~University();
    University(const University&);
    University& operator=(const University&);
    void setName(const char*);
    const char* getName() const;
    int getNumberOfBuildings() const;
    Building& getBuilding(int);

    void addBuilding(const char*, int);
    void addRoomToBuilding(int, const char*, int, int, int);
    void addRoomToBuilding(int, const char*, int, int);

    void printBuildings() const;
    void printRooms() const;
    void printRoomsByType(int type) const;
    void printRoomTypeStatistics() const;
    void printAvailableOffices() const;
    void printTotalCapacityOfOffices() const;
    void printSuitableClassrooms(int numStudents) const;
};
#endif //ASSIGNMENT2_UNIVERSITY_H
