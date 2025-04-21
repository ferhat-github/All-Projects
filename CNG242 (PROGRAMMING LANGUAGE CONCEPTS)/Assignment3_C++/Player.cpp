#include "Player.h"
#include <iostream>


Grid* Player::gameBoard = nullptr;

Player::Player(int givenHealth, int x, int y, int size) {

    health = givenHealth;
    score = 0;
    numElements = 0;
    Coordinate[0] = x;
    Coordinate[1] = y;

    //Dynamically creating CollectedElements array to store maximum size*size elements in it.
    CollectedElements = new Element*[size * size];
    for (int i = 0; i < size*size; ++i) {
        CollectedElements[i] = nullptr;
    }

}

Player::~Player() {
    delete[] CollectedElements;
}




void Player::increaseHealth(int amount) {
    health += amount;
}

void Player::decreaseHealth(int amount) {
    health -= amount;
}

void Player::increaseScore(int amount) {
    score += amount;
}

int Player::getHealth() const {
    return health;
}

int Player::getScore() const {
    return score;
}

void Player::setCoordinate(int x, int y) {
    Coordinate[0] = x;
    Coordinate[1] = y;
}

int Player::getXCoordinate() {
    return Coordinate[0];
}

int Player::getYCoordinate() {
    return Coordinate[1];
}



void Player::printer() const {
    cout << "Health: " << health << ", Score: " << score << endl;
}

//This function will be used for adding founded elements to our CollectedElements array.
//Also this function maintains when player found an WildAnimal, whether it should be added to our CollectedElements array or not.
//If player successfully find whether the rolled dice is odd or even, then founded animal should not be added to our CollectedElements array because we dont want to consider its damage
//But If player cannot quess right then founded animal should be added our CollectedElements array so that we can consider its damage when we traverse the array.
void Player::collectedElementsPrinterAndComparison(Element* element) {

    element->printing();

    if (element->getCharacter() == 'F' || element->getCharacter() == 'I' || element->getCharacter() == 'S') {
        CollectedElements[numElements++] = element;
    }
    else if (element->getCharacter() == 'G') {
        CollectedElements[numElements++] = element;
        gameBoard->setGoldSize(gameBoard->getGoldSize() - 1);
    }
    else if (element->getCharacter() == 'B' || element->getCharacter() == 'W') {
        cout << "Oops there is  a wild animal :'(  Don't worry I will role a dice for you. If you correctly quess whether the rolled dice is odd number or even number you can escape from the animal (Write E for Even, O for Odd): ";
        char guess;
        cin >> guess;
        cout << endl;

        int dice = 1 + rand() % 6;

        if ((dice % 2 == 0 && guess == 'E') || (dice % 2 != 0 && guess == 'O')) {
            cout << "You guessed correctly! You can escape from the animal!" << endl;
        }
        else {
            cout << "You guessed wrong! The dice rolled is " << dice << ". You will receive " << element->getEffect() << " damage!" << endl;
            CollectedElements[numElements++] = element;
        }
    }
}

//This function traverses whole collected elements and calculates current health and score by being called after each turn.
void Player::totalHealthAndTotalScore(int n) {

    health = 2*n;
    score = 0;
    for (int i = 0; i < numElements; ++i) {
        Element* element = CollectedElements[i];
        if (element->getCharacter() == 'F' || element->getCharacter() == 'I' || element->getCharacter() == 'S') {
            increaseHealth(element->getEffect());
        }
        else if (element->getCharacter() == 'G') {
            increaseScore(element->getEffect());
        }
        else if(element->getCharacter() == 'B' || element->getCharacter() == 'W') {
            decreaseHealth(element->getEffect());
        }
    }
    extraHealth(n);
}


//This is an extra function that I created for not making previous function look complicated.
//This function basically counts golds and woods and adds extra health to the player based on the formula given in the Assignment3Pdf
void Player::extraHealth(int n) {

    int goldCount = 0;
    int woodCount = 0;

    for (int i = 0; i < numElements; ++i) {
        if (CollectedElements[i]->getCharacter() == 'G') {
            goldCount++;
        }
        else if (CollectedElements[i]->getCharacter() == 'I') {
            woodCount++;
        }
    }

    int goldBonus = (n / 4) * (goldCount / 3);
    int woodBonus = (n / 8) * (woodCount / 2);

    increaseHealth(goldBonus + woodBonus);
}



//This will be used to access private member function and initialize it
void Player::initializeGameBoard(int n) {
    gameBoard = new Grid(n);
}

//This will be used to use gameBoard(a Grid object)'s member function.
Grid* Player::getGameBoard() {
    return gameBoard;
}

void Player::setHealth(int h) {
    health = h;
}
