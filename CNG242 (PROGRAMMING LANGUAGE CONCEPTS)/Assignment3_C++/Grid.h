#ifndef ASSIGNMENT3_GRID_H
#define ASSIGNMENT3_GRID_H

#include "Element.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Grid {
private:
    int size;
    Element*** board;
    int **OpenedElements;
    int GoldSize;

public:
    Grid(int n);
    ~Grid();

    void deployElements();

    void deployFood(int);
    void deployMedicalSupplies(int);
    void deployWolf(int);
    void deployGold(int);
    void deployBear(int);
    void deployWood(int);



    void printBoard();
    Element* getElement(int, int);
    bool isOpened(int,int);
    void setOpenedElementsArray(int, int);
    void setGoldSize(int);
    int getGoldSize();
};

#endif //ASSIGNMENT3_GRID_H
