#include "University.h"
#include <cstring>
#include <iostream>
using namespace std;

University::University() {
    name = new char[strlen("Undefined") + 1];
    strcpy(name, "Undefined");
    numberOfBuildings = 0;

    for (int i = 0; i < 20; ++i) {
        buildings[i] = NULL;
    }
}

University::University(const char* universityName) {
    name = new char[strlen(universityName) + 1];
    strcpy(name, universityName);
    numberOfBuildings = 0;

    for (int i = 0; i < 20; ++i) {
        buildings[i] = NULL;
    }
}

University::~University() {
    delete[] name;
    for (int i = 0; i < numberOfBuildings; ++i) {
        delete buildings[i];
    }
}

University::University(const University& PassedObject) {
    name = new char[strlen(PassedObject.name) + 1];
    strcpy(name, PassedObject.name);
    numberOfBuildings = PassedObject.numberOfBuildings;

    for (int i = 0; i < numberOfBuildings; ++i) {
        buildings[i] = new Building(*PassedObject.buildings[i]);
    }
}

University& University::operator=(const University& Object) {
    if (this != &Object) {
        delete[] name;
        for (int i = 0; i < numberOfBuildings; ++i) {
            delete buildings[i];
        }

        name = new char[strlen(Object.name) + 1];
        strcpy(name, Object.name);
        numberOfBuildings = Object.numberOfBuildings;

        for (int i = 0; i < numberOfBuildings; ++i) {
            buildings[i] = new Building(*Object.buildings[i]);
        }
    }
    return *this;
}

void University::setName(const char* universityName) {
    delete[] name;
    name = new char[strlen(universityName) + 1];
    strcpy(name, universityName);
}

const char* University::getName() const {
    return name;
}

int University::getNumberOfBuildings() const {
    return numberOfBuildings;
}



void University::addBuilding(const char* buildingName, int size) {
    if (numberOfBuildings >= 20) {
        cout << "You cannot add more than 20 buildings!" << endl;
    }
    else {
        buildings[numberOfBuildings++] = new Building(buildingName, size);
    }
}

void University::printBuildings() const {
    for (int i = 0; i < numberOfBuildings; ++i) {
        cout << "[" << i + 1 << "] ";
        buildings[i]->printBuilding();
    }
}

void University::printRooms() const {
    for (int i = 0; i < numberOfBuildings; ++i) {
        cout << "All rooms in " << buildings[i]->getName() << " building:" << endl;
        buildings[i]->printRooms();
        cout << endl;
    }
}


void University::printRoomsByType(int type) const {

    if(type == 1) {
        cout << "Classrooms in " << name << " university:" << endl;
    }
    else {
        cout << "Offices in " << name << " university:" << endl;
    }

    for (int i = 0; i < numberOfBuildings; ++i) {
        buildings[i]->printRoomsByType(type);
    }
}

void University::printRoomTypeStatistics() const {

    int classrooms = 0, offices = 0;

    for (int i = 0; i < numberOfBuildings; ++i) {
        classrooms += buildings[i]->getNumberOfClassrooms();
        offices += buildings[i]->getNumberOfOffices();
    }

    cout << "Room Type statistics for METU NCC university:" << endl;
    cout << "Number of offices: " << offices << endl;
    cout << "Number of classrooms: " << classrooms << endl;

}

void University::printAvailableOffices() const {
    cout << "Available offices in " << name << " university:" << endl;
    for (int i = 0; i < numberOfBuildings; ++i) {
        buildings[i]->printAvailableOffices();
    }
}


void University::printTotalCapacityOfOffices() const {
    int totalCapacity = 0;
    for (int i = 0; i < numberOfBuildings; ++i) {
        totalCapacity += buildings[i]->getTotalCapacity();
    }
    cout << "Total capacity of offices: " << totalCapacity << endl;
}

void University::printSuitableClassrooms(int numStudents) const {
    cout << "Suitable classes in " << name << " university for" << numStudents << " students:" << endl;
    for (int i = 0; i < numberOfBuildings; ++i) {
        buildings[i]->printSuitableClassrooms(numStudents);
    }
}

Building& University::getBuilding(int index) {
    return *buildings[index];
}

void University::addRoomToBuilding(int buildingIndex, const char* roomName, int floorNumber, int officeType, int numberOfPeople) {

    buildings[buildingIndex]->addRoom(roomName, floorNumber, officeType, numberOfPeople);
}
void University::addRoomToBuilding(int buildingIndex, const char* roomName, int floorNumber, int capacity) {

    buildings[buildingIndex]->addRoom(roomName, floorNumber, capacity);
}