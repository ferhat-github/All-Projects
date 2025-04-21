#include "Grid.h"
#include "Element.h"

Grid::Grid(int n) {

    size = n;
    GoldSize = 0;
    srand(time(NULL));

    board = new Element**[size];
    OpenedElements = new int*[size];
    for (int i = 0; i < size; ++i) {
        OpenedElements[i] = new int[size];
        board[i] = new Element*[size];
        for (int j = 0; j < size; ++j) {
            board[i][j] = nullptr;
            OpenedElements[i][j] = 0;
        }
    }
}


Grid::~Grid() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            delete board[i][j];
        }
        delete[] board[i];
        delete[] OpenedElements[i];
    }
    delete[] board;
    delete[] OpenedElements;
}


//This is the main deplotElements function that calls other subfunctions to deploy each element
void Grid::deployElements() {
    int elementCount = 2 * (size * size) / 25;



    deployBear(elementCount/2);
    deployWood(elementCount);

    deployFood(elementCount);
    deployMedicalSupplies(elementCount);
    deployWolf(elementCount);
    deployGold(elementCount);


}

void Grid::deployFood(int amount) {
    for (int i = 0; i < amount; ++i) {
        int x, y;
        do {
            x = rand() % size;
            y = rand() % size;
        }while ((board[x][y] != nullptr) || (x == 0 && y== 0) || (x == size-1 && y == size-1)); //While chosen cell has an element or is LeftmostTop cell or is RightmostBottom cell(they are reserved for initial position of Player1 and Player2), new coordinates will be searched.
        board[x][y] = new Food(size);
    }
}

void Grid::deployMedicalSupplies(int amount) {
    for (int i = 0; i < amount; ++i) {
        int x, y;
        do {
            x = rand() % size;
            y = rand() % size;
        }while ((board[x][y] != nullptr) || (x == 0 && y== 0) || (x == size-1 && y == size-1)); //While chosen cell has an element or is LeftmostTop cell or is RightmostBottom cell(they are reserved for initial position of Player1 and Player2), new coordinates will be searched.
        board[x][y] = new MedicalSupplies(size);
    }
}

void Grid::deployWolf(int amount) {
    for (int i = 0; i < amount; ++i) {
        int x, y;
        do {
            x = rand() % size;
            y = rand() % size;
        }while ((board[x][y] != nullptr) || (x == 0 && y== 0) || (x == size-1 && y == size-1)); //While chosen cell has an element or is LeftmostTop cell or is RightmostBottom cell(they are reserved for initial position of Player1 and Player2), new coordinates will be searched.
        board[x][y] = new Wolf(size);
    }
}

void Grid::deployGold(int amount) {
    GoldSize = amount;
    for (int i = 0; i < amount; ++i) {
        int x, y;
        do {
            x = rand() % size;
            y = rand() % size;
        }while ((board[x][y] != nullptr) || (x == 0 && y== 0) || (x == size-1 && y == size-1)); //While chosen cell has an element or is LeftmostTop cell or is RightmostBottom cell(they are reserved for initial position of Player1 and Player2), new coordinates will be searched.
        board[x][y] = new Gold();
    }
}

void Grid::deployBear(int amount) {

    for (int i = 0; i < amount; ++i) {
        int x1, x2, x3, y1, y2, y3;
        bool validPlacement = false;

        //MaxAttempts will be used to avoid the infinite loop when there is really not a suitable place for a bear to insert.
        int maxAttempts = 250;
        int attempts = 0;

        while (!validPlacement && attempts < maxAttempts) {
            attempts++;


            int direction = rand() % 3;

            //Horizontal Inserting
            if(direction == 0) {
                x2 = rand() % size;
                y2 = rand() % size;
                x1 = x2;
                y1 = y2 - 1;
                x3 = x2;
                y3 = y2 + 1;
            }

            //Vertical Inserting
            else if(direction == 1) {
                x2 = rand() % size;
                y2 = rand() % size;
                x1 = x2 - 1;
                y1 = y2;
                x3 = x2 + 1;
                y3 = y2;
            }

            //Diagonal Inserting
            else {
                int diagonalDirection = rand() % 2;
                x2 = rand() % size;
                y2 = rand() % size;

                //Tilted to the left
                if(diagonalDirection == 0) {
                    x1 = x2 - 1;
                    y1 = y2 - 1;
                    x3 = x2 + 1;
                    y3 = y2 + 1;
                }

                //Tilted to the right
                else {
                    x1 = x2 - 1;
                    y1 = y2 + 1;
                    x3 = x2 + 1;
                    y3 = y2 - 1;
                }
            }

            //Checking
            if ((x1 >= 0 && 1 < size && y1 >= 0 && y1 < size && board[x1][y1] == nullptr && !(x1 == 0 && y1 == 0) && !(x1 == size-1 && y1 == size-1)) &&
                (x2 >= 0 && x2 < size && y2 >= 0 && y2 < size && board[x2][y2] == nullptr && !(x2 == 0 && y2 == 0) && !(x2 == size-1 && y2 == size-1)) &&
                (x3 >= 0 && x3 < size && y3 >= 0 && y3 < size && board[x3][y3] == nullptr && !(x3 == 0 && y3 == 0) && !(x3 == size-1 && y3 == size-1))) {

                validPlacement = true;
                board[x1][y1] = new Bear(size);
                board[x2][y2] = new Bear(size);
                board[x3][y3] = new Bear(size);
            }
        }
    }
}

void Grid::deployWood(int amount) {

    for (int i = 0; i < amount; ++i) {
        int x1, x2, y1, y2;
        bool validPlacement = false;

        while (!validPlacement) {
            //0 for horizontal, 1 for vertical, 2 for diagonal
            int direction = rand() % 3;

            //0 for left or up, 1 for right or down
            int extraCellsDirection = rand() % 2;

            //Horizontal Inserting
            if (direction == 0) {
                x1 = rand() % size;
                y1 = rand() % size;
                x2 = x1;

                //Inserting Left
                if (extraCellsDirection == 0 && y1 > 0) {
                    y2 = y1 - 1;

                }
                //Inserting Right
                else if (extraCellsDirection == 1 && y1 < size - 1) {
                    y2 = y1 + 1;
                }
                else {
                    continue;
                }

                if (y2 >= 0 && y2 < size && board[x1][y1] == nullptr && board[x2][y2] == nullptr && !(x1 == 0 && y1 == 0) && !(x2 == 0 && y2 == 0) && !(x1 == size-1 && y1 == size-1) && !(x2 == size-1 && y2 == size-1)) {
                    validPlacement = true;
                }
            }

            //Vertical Inserting
            else if (direction == 1) {
                x1 = rand() % size;
                y1 = rand() % size;
                y2 = y1;

                //Inserting Up
                if (extraCellsDirection == 0 && x1 > 0) {
                    x2 = x1 - 1;

                }

                //Inserting Down
                else if (extraCellsDirection == 1 && x1 < size - 1) {
                    x2 = x1 + 1;
                }
                else {
                    continue;
                }

                if (x2 >= 0 && x2 < size && board[x1][y1] == nullptr && board[x2][y2] == nullptr && !(x1 == 0 && y1 == 0) && !(x2 == 0 && y2 == 0) && !(x1 == size-1 && y1 == size-1) && !(x2 == size-1 && y2 == size-1)) {
                    validPlacement = true;
                }
            }

            //Diagonal Inserting
            else {
                x1 = rand() % size;
                y1 = rand() % size;

                int extraCellsDirection2 = rand() % 4;

                switch (extraCellsDirection2) {

                    //Left-Up
                    case 0:
                        x2 = x1 - 1;
                        y2 = y1 - 1;
                        break;

                    case 1:
                        //Right-Up
                        x2 = x1 - 1;
                        y2 = y1 + 1;
                        break;
                    case 2:
                        //Right-Down
                        x2 = x1 + 1;
                        y2 = y1 + 1;
                        break;
                    case 3:
                        //Left-Down
                        x2 = x1 + 1;
                        y2 = y1 - 1;
                        break;
                }

                if (x2 >= 0 && x2 < size && y2 >= 0 && y2 < size && board[x1][y1] == nullptr && board[x2][y2] == nullptr && !(x1 == 0 && y1 == 0) && !(x2 == 0 && y2 == 0) && !(x1 == size-1 && y1 == size-1) && !(x2 == size-1 && y2 == size-1)) {
                    validPlacement = true;
                }
            }
        }

        //After confirming a valid placement, create new Wood elements
        board[x1][y1] = new Wood(size);
        board[x2][y2] = new Wood(size);
    }
}



void Grid::printBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != nullptr && OpenedElements[i][j] == 1)
                cout << board[i][j]->getCharacter() << " ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}




Element* Grid::getElement(int x, int y) {
    if (x >= 0 && x < size && y >= 0 && y < size)
        return board[x][y];
    else {
        return nullptr;
    }
}


bool Grid::isOpened(int x, int y) {
    if(OpenedElements[x][y] == 0) {
        return false;
    }
    else {
        return true;
    }
}

//By making releated cells Opened indicator 1 (by using this OpenedElements array) we can understand that coordinate is opened
void Grid::setOpenedElementsArray(int x, int y) {
    OpenedElements[x][y] = 1;
}

void Grid::setGoldSize(int amount) {
    GoldSize = amount;
}

int Grid::getGoldSize() {
    return GoldSize;
}
