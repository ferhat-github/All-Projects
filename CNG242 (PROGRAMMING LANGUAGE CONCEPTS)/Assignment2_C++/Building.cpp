#include "Building.h"

Building::Building() {
        name = new char[strlen("Undefined") + 1];
    strcpy(name, "Undefined");
    sizeInSquareMeters = -1;
    numberOfRooms = 0;

    for (int i = 0; i < 100; ++i) {
        rooms[i] = NULL;
    }
}

Building::Building(const char* buildingName, int size) {
    name = new char[strlen(buildingName) + 1];
    strcpy(name, buildingName);
    sizeInSquareMeters = size;
    numberOfRooms = 0;

    for (int i = 0; i < 100; ++i) {
        rooms[i] = NULL;
    }
}

Building::~Building() {
    delete[] name;
    for (int i = 0; i < numberOfRooms; i++) {
        delete rooms[i];
    }
}

Building::Building(const Building& PassedObject) {
    this->name = new char[strlen(PassedObject.name) + 1];
    strcpy(name, PassedObject.name);
    this->sizeInSquareMeters = PassedObject.sizeInSquareMeters;
    this->numberOfRooms = PassedObject.numberOfRooms;

    for (int i = 0; i < numberOfRooms; ++i) {
        this->rooms[i] = PassedObject.rooms[i];
    }
}

Building& Building::operator=(const Building& Object) {
    if (this != &Object) {
        delete[] name;
        this->name = new char[strlen(Object.name) + 1];
        strcpy(name, Object.name);
        this->sizeInSquareMeters = Object.sizeInSquareMeters;
        this->numberOfRooms = Object.numberOfRooms;



        for (int i = 0; i < numberOfRooms; ++i) {
            delete rooms[i];
            if(Object.rooms[i]->getType() == 1) {
                this->rooms[i] = new Classroom(Object.rooms[i]->getName(), Object.rooms[i]->getFloorNumber(), Object.rooms[i]->getCapacity());
            }
            else {
                this->rooms[i] = new Office(Object.rooms[i]->getName(), Object.rooms[i]->getFloorNumber(), Object.rooms[i]->getOfficeType(), Object.rooms[i]->getNumberOfPeople());
            }
            this->rooms[i] = Object.rooms[i];
        }
    }

    return *this;
}



void Building::setName(const char* GivenName) {
    delete[] name;
    name = new char[strlen(GivenName) + 1];
    strcpy(name, GivenName);
}

void Building::setSize(int GivenSize) {
    sizeInSquareMeters = GivenSize;
}

const char* Building::getName() const {
    return name;
}

int Building::getSize() const {
    return sizeInSquareMeters;
}

int Building::getNumberOfRooms() const {
    return numberOfRooms;
}



void Building::addRoom(const char* roomName, int floorNumber, int capacity) {
    if (numberOfRooms >= 100)
        return;

    rooms[numberOfRooms++] = new Classroom(roomName, floorNumber, capacity);
}

void Building::addRoom(const char* roomName, int floorNumber, int TypeOffice, int numberOfPeople) {
    if (numberOfRooms >= 100)
        return;

    OfficeType x;
    if(TypeOffice == 1) {
        x = CoordinatorOffice;
    }
    else if(TypeOffice == 2) {
        x = StandardOffice;
    }
    else if(TypeOffice == 3) {
        x = SharedOfficeFor2People;
    }
    else if(TypeOffice == 4) {
        x = SharedOfficeFor3People;
    }
    else if(TypeOffice == 5) {
        x = SharedOfficeFor10People;
    }


    rooms[numberOfRooms++] = new Office(roomName, floorNumber, x, numberOfPeople);
}

void Building::printBuilding() const {
    cout << "Building Name = " << name << endl <<"Building Size = " << sizeInSquareMeters << endl << "Building Number of Rooms = " << numberOfRooms << endl << endl;
}

void Building::printRooms() const {
    for (int i = 0; i < numberOfRooms; i++) {
        rooms[i]->printRoom();
    }
}


void Building::printRoomsByType(int type) const {
    for (int i = 0; i < numberOfRooms; ++i) {
        if (rooms[i]->getType() == type) {
            if(type == 1) {
                cout << "All Classrooms in " << name << " building:" << endl;
            }
            else {
                cout << "Offices in " << name << " building:" << endl;
            }
            rooms[i]->printRoom();
        }
    }
}


int Building::getNumberOfClassrooms() const {
    int count = 0;
    for (int i = 0; i < numberOfRooms; i++) {
        if (rooms[i]->getType() == 1) {
            count++;
        }
    }
    return count;
}

int Building::getTotalCapacity() const {
    int totalCapacity = 0;
    for (int i = 0; i < numberOfRooms; ++i) {
        if (rooms[i]->getType() == 2) {
            totalCapacity += rooms[i]->getCapacity();
        }
    }
    return totalCapacity;
}

int Building::getNumberOfOffices() const {
    int count = 0;
    for (int i = 0; i < numberOfRooms; ++i) {
        if (rooms[i]->getType() == 2) {
            count++;
        }
    }
    return count;
}

void Building::printAvailableOffices() const {
    cout << "Available offices in " << name << " building:" << endl;
    for (int i = 0; i < numberOfRooms; ++i) {
        if (rooms[i]->getType() == 2 && !rooms[i]->isFull()) {
            rooms[i]->printRoom();
        }
    }
}




void Building::printSuitableClassrooms(int numStudents) const {
    cout << "Classrooms which are suitable for " << numStudents << " students in: " << name << " building" << endl;
    for (int i = 0; i < numberOfRooms; ++i) {
        if (rooms[i]->getType() == 1 && rooms[i]->checkSuitability(numStudents)) {
            rooms[i]->printRoom();
        }
    }
}



