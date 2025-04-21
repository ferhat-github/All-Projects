#ifndef PLAYER_H
#define PLAYER_H

#include "Grid.h"

class Player {

private:
    int health;
    int score;
    Element** CollectedElements;
    int numElements;
    int Coordinate[2];
    static Grid* gameBoard;

public:

    Player(int, int ,int, int);
    ~Player();

    int getHealth() const;
    void setHealth(int);
    int getScore() const;
    void printer() const;

    void setCoordinate(int, int);
    int getXCoordinate();
    int getYCoordinate();

    void increaseHealth(int);
    void decreaseHealth(int);
    void increaseScore(int);

    void totalHealthAndTotalScore(int);

    void collectedElementsPrinterAndComparison(Element*);
    void extraHealth(int);

    static void initializeGameBoard(int n);
    static Grid* getGameBoard();


};

#endif // PLAYER_H


