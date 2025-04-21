#include "Classroom.h"

Classroom::Classroom() : Room("Undefined", -1){
    capacity = -1;
}

Classroom::Classroom(const char* RoomName, int RoomFloorNumber, int CapacityOfClassroom) : Room(RoomName, RoomFloorNumber){
    capacity = CapacityOfClassroom;
}

Classroom::~Classroom() {}

void Classroom::setCapacity(int CapacityOfClassroom) {
    capacity = CapacityOfClassroom;
}

int Classroom::getCapacity() const {
    return capacity;
}

bool Classroom::checkSuitability(int NumStudents) const {
    return NumStudents <= capacity;
}

void Classroom::printRoom() const {
    cout << "Classroom name = " << name << endl;
    cout << "Classroom floor number = " << floorNumber << endl;
    cout << "Classroom capacity = " << capacity << endl;
}


int Classroom::getType() const {
    return 1;
}
