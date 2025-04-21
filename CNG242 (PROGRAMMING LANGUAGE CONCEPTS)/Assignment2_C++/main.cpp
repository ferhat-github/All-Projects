/* Ferhat Kasim Koc
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */

#include "University.h"
#include <iostream>
using namespace std;

int main() {
    University metu("METU NCC");

    int Option;


    while (true) {
        cout << "[1] Add a new building to the university" << endl;
        cout << "[2] Add a new room to a selected building" << endl;
        cout << "[3] Print the buildings in the university" << endl;
        cout << "[4] Print the rooms in each building in the university" << endl;
        cout << "[5] Print the rooms in each building in the university based on type" << endl;
        cout << "[6] Print the total number of classrooms and offices in the university" << endl;
        cout << "[7] Print the available offices in each building in the university" << endl;
        cout << "[8] Print the total capacity of all the offices" << endl;
        cout << "[9] Print the suitable classrooms in the university based on the given number of students" << endl;
        cout << "[0] Exit" << endl;
        cout << "Please enter your choice: ";
        cin >> Option;
        cout << endl;

        if (Option == 0) {
            cout << "Thank you for using the university campus management system";
            break;
        }

        switch (Option) {
            case 1: {
                char buildingName[50];
                int size;
                cout << "Please enter name of building: ";
                cin >> buildingName;
                cout << endl << "Please enter size of building: ";
                cin >> size;
                metu.addBuilding(buildingName, size);
                break;
            }
            case 2: {
                if (metu.getNumberOfBuildings() == 0) {
                    cout << "There is no any buildings. Please add one first..." << endl;
                    break;
                }

                cout << "Buildings in " << metu.getName() << " university:" << endl;
                metu.printBuildings();


                int BuildingNo;
                cout << "Please enter the number of building to which the room should be added: ";
                cin >> BuildingNo;
                cout << endl;

                if (BuildingNo < 1 || BuildingNo > metu.getNumberOfBuildings()) {
                    cout << "Invalid building number!" << endl;
                    break;
                }


                int TypeOfRoom;
                cout << "Please enter the type of room(1: Classroom/ 2: Office): ";
                cin >> TypeOfRoom;

                char roomName[50];
                int floorNumber;
                cout << "Please enter the name of the new room: ";
                cin >> roomName;
                cout << "Please enter the floor number of the new room: ";
                cin >> floorNumber;
                cout << endl;

                if (TypeOfRoom == 1) {
                    cout << "Please enter capacity of classroom ";
                    int capacity;
                    cin >> capacity;
                    cout << endl;
                    metu.addRoomToBuilding(BuildingNo - 1, roomName, floorNumber, capacity);

                }
                else if (TypeOfRoom == 2) {
                    cout << "[1] Coordinator Office" << endl;
                    cout << "[2] Standard Office" << endl;
                    cout << "[3] Shared Office for 2 people" << endl;
                    cout << "[4] Shared Office for 3 people" << endl;
                    cout << "[5] Shared Office for 10 people" << endl;
                    cout << "Please enter type of office: ";
                    int TypeOfOffice;
                    cin >> TypeOfOffice;
                    cout << endl;

                    int numPeople;
                    cout << "Please enter number of people in the office: " << endl;
                    cin >> numPeople;
                    cout << endl;

                    metu.addRoomToBuilding(BuildingNo - 1, roomName, floorNumber, TypeOfOffice, numPeople);
                    break;

                }
                else {
                    cout << "Given Room Type Is Invalid!" << endl;
                }
                break;
            }
            case 3:
                metu.printBuildings();
                break;
            case 4:
                cout << "Rooms in " << metu.getName() << " university:" << endl;
                metu.printRooms();
                break;
            case 5: {
                int roomType;
                cout << "Please enter type of room to display:" << endl;
                cout << "[1] Classrooms" << endl;
                cout << "[2] Offices" << endl;
                cin >> roomType;
                cout << endl;

                metu.printRoomsByType(roomType);
                break;
            }
            case 6:
                metu.printRoomTypeStatistics();
                break;
            case 7:
                metu.printAvailableOffices();
                break;
            case 8:
                metu.printTotalCapacityOfOffices();
                break;
            case 9: {
                int numStudents;
                cout << "Please enter number of students: ";
                cin >> numStudents;
                metu.printSuitableClassrooms(numStudents);
                break;
            }
            default: {
                cout << "Invalid choice, please try again." << endl;
                break;
            }
        }
    }


    return 0;
}
