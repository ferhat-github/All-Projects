#include "Player.h"
#include <iostream>

using namespace std;

bool validCoordinate(int coordinate, int sizeofBoard) {
    if(coordinate < 0 || coordinate > sizeofBoard-1) {
        return false;
    }
    else {
        return true;
    }
}
int main() {

    srand(time(NULL));

    cout << "*************Welcome to the Gold Rush Alaska game!*************" << endl << endl;
    cout << "Before starting the game, please specify the board size(Minimum 5 should be chosen): ";
    int boardSize;
    cin >> boardSize;
    cout << endl;

    while(boardSize < 5) {
        cout << "You cannot choose the board size less than 5! Please choose again: ";
        cin >> boardSize;
        cout << endl;
    }


    Player::initializeGameBoard(boardSize);  // Initialize grid with the specified size

    Player player1(2*boardSize, 0, 0, boardSize);//Initializing  player1 with the given initial health formula (2 times board size)
    Player player2(2*boardSize, boardSize-1, boardSize-1, boardSize);//Initializing  player2 with the given initial health formula (2 times board size)

    Player::getGameBoard()->deployElements();


    cout << endl;
    cout << "Gold Rush Alaska game with size of " << boardSize << "*" << boardSize << " is created" << endl;
    cout << endl;


    int coin = rand() % 2; //Determining who is going to start first to the game
    int turn_size = rand() % (boardSize * boardSize - 20 + 1) + 20;


    for (int currentTurn = 1; currentTurn <= turn_size; ++currentTurn) {


        cout << "Current board is" << endl;
        Player::getGameBoard()->printBoard();


        if ((coin == 0) && (player1.getHealth() > 0)) {

            cout << "Player1's TURN" << endl << "Current Health and Score of Player1 is:" << endl;
            player1.printer();
            cout << "Player1's current location in the board is [" << player1.getXCoordinate() << "," << player1.getYCoordinate() << "]." << endl;

            //Note: I started indexing my board from 0 to n-1 so player should choose cell indexes in this range
            cout << "Where would you like to move (Please enter coordinates in this format: indexX,indexY): ";
            int x, y;
            char comma; //This will be used to store the comma character, we won't use this variable

            //Reading given coordinate in the format "x,y"
            cin >> x >> comma >> y;
            cout << endl;


            //Checking Validity of given coordinates
            while (true) {

                while ((!validCoordinate(x, boardSize) || !validCoordinate(y, boardSize)) || ((x == 0) && (y == 0)) || (x == boardSize - 1 && y == boardSize - 1)) {
                    cout << "Given coordinates are invalid please enter again: ";
                    cin >> x >> comma >> y;
                    cout << endl;
                }

                while (Player::getGameBoard()->isOpened(x, y)) { // Check if cell is opened using getGameBoard()
                    cout << "Given coordinates are already opened please enter again: ";
                    cin >> x >> comma >> y;
                    cout << endl;
                }


                if ((validCoordinate(x, boardSize) && validCoordinate(y, boardSize)) && !Player::getGameBoard()->isOpened(x, y)) { // Check if cell is opened using getGameBoard()
                    break;
                }
            }


            //Setting given coordinates to player1
            player1.setCoordinate(x, y);
            Element* element = Player::getGameBoard()->getElement(x, y);

            if (element != nullptr) {
                player1.collectedElementsPrinterAndComparison(element);
                if (player1.getHealth() <= 0) {
                    cout << "Player1 has died! Rest in Peace Player2" << endl;
                }
            }

            //Setting cell as opened
            Player::getGameBoard()->setOpenedElementsArray(x, y);
            //Calculating total number and total score by traversing whole collected elements again and again
            player1.totalHealthAndTotalScore(boardSize);

            //Switching next turn to Player 2
            coin = 1;
        }
        else if((coin == 1) && (player2.getHealth() > 0)) {

            cout << "Player2's TURN" << endl << "Current Health and Score of Player2 is:" << endl;
            player2.printer();
            cout << "Player2's current location in the board is [" << player2.getXCoordinate() << "," << player2.getYCoordinate() << "]." << endl;


            cout << "Where would you like to move (Please enter coordinates in this format: x,y): ";
            int x, y;
            char comma;//This will be used to store the comma character, we won't use this variable


            //Reading given coordinate in the format "x,y"
            cin >> x >> comma >> y;
            cout << endl;


            //Checking Validity of given coordinates
            while (true) {
                while ((!validCoordinate(x, boardSize) || !validCoordinate(y, boardSize)) || ((x == 0) && (y == 0)) || (x == boardSize - 1 && y == boardSize - 1)) {
                    cout << "Given coordinates are invalid please enter again: ";
                    cin >> x >> comma >> y;
                    cout << endl;
                }
                while (Player::getGameBoard()->isOpened(x, y)) { // Check if cell is opened using getGameBoard()
                    cout << "Given coordinates are already opened please enter again: ";
                    cin >> x >> comma >> y;
                    cout << endl;
                }
                if ((validCoordinate(x, boardSize) && validCoordinate(y, boardSize)) && !Player::getGameBoard()->isOpened(x, y)) { // Check if cell is opened using getGameBoard()
                    break;
                }
            }

            //Setting given coordinates to player2
            player2.setCoordinate(x, y);
            Element* element = Player::getGameBoard()->getElement(x, y);

            if (element != nullptr) {
                player2.collectedElementsPrinterAndComparison(element);
                if (player2.getHealth() <= 0) {
                    cout << "Player2 has died! Rest in Peace dear Player2" << endl;
                }
            }
            //Setting cell as opened
            Player::getGameBoard()->setOpenedElementsArray(x, y);

            //Calculating total number and total score by traversing whole collected elements again and again
            player2.totalHealthAndTotalScore(boardSize);

            //Switching next turn to Player1
            coin = 0;
        }

        if(Player::getGameBoard()->getGoldSize() <= 0) {
            cout << "All Golds Are Found! All Players Will Die!" << endl;
            player1.setHealth(0);
            player2.setHealth(0);
        }


        //If both players are dead, there is no point to continue the game, so the game is finished
        if((player1.getHealth() <= 0) && (player2.getHealth() <= 0)) {
            break;
        }
    }


    cout << endl;
    cout << "Game Over!" << endl;
    cout << "Final Table:" << endl;


    cout << "Player 1: ";
    player1.printer();
    cout << "Player 2: ";
    player2.printer();

    if (player1.getScore() > player2.getScore()) {
        cout << "Player1 Wins!" << endl;
    }
    else if (player1.getScore() < player2.getScore()) {
        cout << "Player2 Wins!" << endl;
    }
    else {
        cout << "It's a draw!" << endl;
    }

    return 0;
}
