#include "Office.h"

Office::Office() : Room("Undefined", -1){
    officeType = None;
    numberOfPeople = 0;
}

Office::Office(const char* RoomName, int RoomFloorNumber, OfficeType type, int NumPeople) : Room(RoomName, RoomFloorNumber){
    officeType = type;
    numberOfPeople = NumPeople;
}

Office::~Office() {}

void Office::setOfficeType(OfficeType type) {
    officeType = type;
}



void Office::setNumberOfPeople(int NumPeople) {
    numberOfPeople = NumPeople;
}

OfficeType Office::getOfficeType() const {
    return officeType;
}

int Office::getNumberOfPeople() const {
    return numberOfPeople;
}

bool Office::isFull() const {
    return numberOfPeople >= getCapacity();
}

int Office::getCapacity() const {
    if (officeType == CoordinatorOffice || officeType == StandardOffice) {
        return 1;
    }
    else if (officeType == SharedOfficeFor2People) {
        return 2;
    }
    else if (officeType == SharedOfficeFor3People) {
        return 3;
    }
    else if (officeType == SharedOfficeFor10People) {
        return 10;
    }
    else {
        return 0;
    }
}

void Office::printRoom() const {

    cout << "Office name = " << name << endl;
    cout << "Office floor number = " << floorNumber << endl;
    cout << "Office type = ";


    switch (officeType) {
        case CoordinatorOffice:
            cout << "Coordinator Office";
            break;
        case StandardOffice:
            cout << "Standard Office";
            break;
        case SharedOfficeFor2People:
            cout << "Shared Office for 2 people";
            break;
        case SharedOfficeFor3People:
            cout << "Shared Office for 3 people";
            break;
        case SharedOfficeFor10People:
            cout << "Shared Office for 10 people";
            break;
        default:
            cout << "None";
            break;
    }

    cout << endl;
    cout << "Number of people in office = " << numberOfPeople << endl;
    cout << "Office capacity = " << getCapacity() << endl;
    cout << "Office is ";
    if(isFull()) {
        cout << "full"  << endl;
    }
    else {
        cout << "not full"  << endl;
    }
}

int Office::getType() const {
    return 2;
}
