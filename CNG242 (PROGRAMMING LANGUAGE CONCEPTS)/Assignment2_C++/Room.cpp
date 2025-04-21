#include "Room.h"


Room::Room() {
    name = new char[strlen("Undefined") + 1];
    strcpy(name, "Undefined");

    floorNumber = -1;
}

Room::Room(const char* RoomName, int RoomFloorNumber) {
    name = new char[strlen(RoomName) + 1];
    strcpy(name, RoomName);

    floorNumber = RoomFloorNumber;
}

Room::Room(const Room& PassedObject) {
    name = new char[strlen(PassedObject.name) + 1];
    strcpy(name, PassedObject.name);
    floorNumber = PassedObject.floorNumber;
}

Room& Room::operator=(const Room& Object) {
    if (this != &Object) {
        delete[] name;
        name = new char[strlen(Object.name) + 1];
        strcpy(name, Object.name);

        floorNumber = Object.floorNumber;
    }

    return *this;
}

void Room::setName(const char* RoomName) {
    delete[] name;
    name = new char[strlen(RoomName) + 1];
    strcpy(name, RoomName);
}

void Room::setFloorNumber(int RoomFloorNumber) {
    floorNumber = RoomFloorNumber;
}


const char* Room::getName() const{
    return name;
}
int Room::getFloorNumber() const{
    return floorNumber;
}

void Room::printRoom() const{
    cout << "Room name: " << name << "\nFloor number: " << floorNumber << endl;
}

Room::~Room() {
    delete[] name;
}



int Room::getType() const {return 0;}
int Room::getCapacity() const {return 0;}
bool Room::isFull() const {return false;}
bool Room::checkSuitability(int x) const{return true;}
OfficeType Room::getOfficeType() const{return None;}
int Room::getNumberOfPeople() const{return 0;}

