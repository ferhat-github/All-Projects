#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int boardsize();
void displayBoard(char **, int);
int initializeBoard(char **, int);
int getCoordinates(int, int, int, int, int, int **);
int checkCharacters(int, int, int, int, char **);



int main() {

    int ValidBoardSize, i, j, MaxTURNS;
    char **SYMBOLBOARD; //2 dimensional symbol array that is created randomly
    int **CounterBoard; //Another 2 dimensional array that includes integers. This array will be used for preventing coordinates that is open already.
    char **DISPLAYEDBOARD; //Last 2 dimensional array which will be used for Hidding Symbols and showing opened elements
    char RepeatOrNot;   //Character Variable that is created for determine if the user wants to play the game again.

    srand(time(NULL));

    printf("Welcome to MemoMe!\n");

    do {
        ValidBoardSize = boardsize(); //Getting a BoardSize which obeys desired Board Size Rules.

        SYMBOLBOARD = (char **) malloc(ValidBoardSize * sizeof(char *));
        CounterBoard = (int **) malloc(ValidBoardSize * sizeof(int *));
        DISPLAYEDBOARD = (char **) malloc(ValidBoardSize * sizeof(char *));

        if (*SYMBOLBOARD == NULL || *CounterBoard == NULL || *DISPLAYEDBOARD == NULL) {
            printf("Allocation Failed");
            exit(1);
        }

        for (i = 0; i < ValidBoardSize; i++) {
            SYMBOLBOARD[i] = (char *) malloc(ValidBoardSize * sizeof(char));
            CounterBoard[i] = (int *) malloc(ValidBoardSize * sizeof(int));
            DISPLAYEDBOARD[i] = (char *) malloc(ValidBoardSize * sizeof(char));
            if (SYMBOLBOARD[i] == NULL || CounterBoard[i] == NULL || DISPLAYEDBOARD[i] == NULL) {
                printf("Allocation Failed");
                exit(1);
            }
        }

        initializeBoard(SYMBOLBOARD, ValidBoardSize); //Initializing Our SymbolArray

        for (i = 0; i < ValidBoardSize; i++) {
            for (j = 0; j < ValidBoardSize; j++) {
                CounterBoard[i][j] = 0;
                DISPLAYEDBOARD[i][j] = '@';
            }
        }



        int Flag, Checking, Row1, Column1, Row2, Column2, Player1Score = 0, Player2Score = 0;


        MaxTURNS = ValidBoardSize * ValidBoardSize; //A Game counter which helps us to finish the game when all doors are opened.
        do {
            printf("\n--Player 1 Turn:--\n");

            displayBoard(DISPLAYEDBOARD, ValidBoardSize); //Displaying the current Board.


            Flag = 0; //A variable(Used In While Loop) that is created for being sure if the coordinates that are entered by user are obey Coordinates Rule.
            while (Flag == 0) {
                fflush(stdin);
                printf("\nEnter the coordinates of doors to open:");
                scanf("(%d,%d) (%d,%d)", &Row1, &Column1, &Row2, &Column2);

                // If the coordinates are obey the rules, Flag becomes 1 then condition turns FALSE. Otherwise Flag becomes 0(which means condition remains TRUE) until the user enters the coordinates that obey the rules.
                //NOTE: CounterBoard will help us to determine whether the given coordinates opened already or not.
                Flag = getCoordinates(Row1, Column1, Row2, Column2, ValidBoardSize, CounterBoard);
            }

            Checking = checkCharacters(Row1, Column1, Row2, Column2, SYMBOLBOARD); // "Checking" variable becomes 1 if Elements which pointed by entered coordinates are Equal. Otherwise it is 0.
            if (Checking == 1) {
                DISPLAYEDBOARD[Row1 - 1][Column1 - 1] = SYMBOLBOARD[Row1 - 1][Column1 - 1]; //Changing the elements of DISPLAYEDBOARD with the Symbols from SYMBOLBOARD.
                DISPLAYEDBOARD[Row2 - 1][Column2 - 1] = SYMBOLBOARD[Row2 - 1][Column2 - 1];
                displayBoard(DISPLAYEDBOARD, ValidBoardSize); // Displaying the new DISPLAYEDBOARD
                Player1Score = Player1Score + 2; //Adding the score
                MaxTURNS = MaxTURNS - 2; //Substracting 2 from MaxTURNS
                printf("\nLucky you! Your score: 2, total score:%d\n", Player1Score);
                CounterBoard[Row1 - 1][Column1 - 1] = 1; //Assigning CounterBoard to 1 with respect to the relative coordinates. Therefore we can make sure this coordinates are opened(reserved).
                CounterBoard[Row2 - 1][Column2 - 1] = 1;
            } else {
                DISPLAYEDBOARD[Row1 - 1][Column1 - 1] = SYMBOLBOARD[Row1 - 1][Column1 - 1]; // Tentatively Changing the elements of DISPLAYEDBOARD with the Symbols from SYMBOLBOARD.
                DISPLAYEDBOARD[Row2 - 1][Column2 - 1] = SYMBOLBOARD[Row2 - 1][Column2 - 1];
                displayBoard(DISPLAYEDBOARD, ValidBoardSize);
                Player1Score = Player1Score - 1;
                printf("\nUnlucky! Your score: -1, total score: %d\n", Player1Score);
                DISPLAYEDBOARD[Row1 - 1][Column1 - 1] = '@'; // Reassigning the elements of DISPLAYEDBOARD with '@'
                DISPLAYEDBOARD[Row2 - 1][Column2 - 1] = '@';
            }



            if(MaxTURNS != 0) {
                //Rest of the code is just the copy of the code above.(The part where Player 1 Turn starts)
                printf("\n--Player 2 Turn:--\n");
                Flag = 0;

                displayBoard(DISPLAYEDBOARD, ValidBoardSize);


                while (Flag == 0) {
                    fflush(stdin);
                    printf("\nEnter the coordinates of doors to open:");
                    scanf("(%d,%d) (%d,%d)", &Row1, &Column1, &Row2, &Column2);
                    fflush(stdin);
//          printf("\n%d, %d, %d, %d", Row1, Column1, Row2, Column2);
                    Flag = getCoordinates(Row1, Column1, Row2, Column2, ValidBoardSize, CounterBoard);
                }

                Checking = checkCharacters(Row1, Column1, Row2, Column2, SYMBOLBOARD);
                if (Checking == 1) {
                    DISPLAYEDBOARD[Row1 - 1][Column1 - 1] = SYMBOLBOARD[Row1 - 1][Column1 - 1];
                    DISPLAYEDBOARD[Row2 - 1][Column2 - 1] = SYMBOLBOARD[Row2 - 1][Column2 - 1];
                    displayBoard(DISPLAYEDBOARD, ValidBoardSize);
                    Player2Score = Player2Score + 2;
                    MaxTURNS = MaxTURNS - 2;
                    printf("\nLucky you! Your score: 2, total score:%d\n", Player2Score);
                    CounterBoard[Row1 - 1][Column1 - 1] = 1;
                    CounterBoard[Row2 - 1][Column2 - 1] = 1;
                } else {
                    DISPLAYEDBOARD[Row1 - 1][Column1 - 1] = SYMBOLBOARD[Row1 - 1][Column1 - 1];
                    DISPLAYEDBOARD[Row2 - 1][Column2 - 1] = SYMBOLBOARD[Row2 - 1][Column2 - 1];
                    displayBoard(DISPLAYEDBOARD, ValidBoardSize);
                    Player2Score = Player2Score - 1;
                    printf("\nUnlucky! Your score: -1, total score: %d\n", Player2Score);
                    DISPLAYEDBOARD[Row1 - 1][Column1 - 1] = '@';
                    DISPLAYEDBOARD[Row2 - 1][Column2 - 1] = '@';
                }
            }

        } while (MaxTURNS != 0); // When we fully opened the DISPLAYEDBOARD, MaxTURNS becomes "0" therefore the condition is not TRUE anymore.


        //Determining Who is Winner.
        if (Player1Score > Player2Score) {
            printf("\n***Winner is Player 2!***\n");
        }
        else if(Player1Score < Player2Score) {
            printf("\n***Winner is Player 2!***\n");
        }
        else {
            printf("\n***Both player have the same points. No one Won!***\n");
        }


        //Asking User whether wants to play again or not.
        printf("\nWould you like to play again (Y/N)?");
        fflush(stdin);
        scanf("%c", &RepeatOrNot);

    }while(RepeatOrNot == 'Y'); //If user enters "Y" this condition turns TRUE which means the play will be played again.
    printf("Byee");


    for(i=0; i<ValidBoardSize; i++){
        free(SYMBOLBOARD[i]);
        free(DISPLAYEDBOARD[i]);
        free(CounterBoard[i]);
    }
    free(SYMBOLBOARD);
    free(DISPLAYEDBOARD);
    free(CounterBoard);



    return 0;
}




//This function ask for a BoardSize which obeys Boad Size Rules. If entered value obeys rules then this function turns 1(integer);
int boardsize() {

    int BoardSize, Flag;

    Flag = 1;
    while(Flag == 1) {
        printf("Please specify the board size (2-30):");
        scanf("%d", &BoardSize);

        if (BoardSize > 30 || BoardSize < 2) {
            printf("Board size can only be between 2-30!\n");
        }
        else if(BoardSize%2 != 0) {
            printf("Board size can only be a multiple of two!\n");
        }
        else {
            printf("\nA Board is created for you with the size of %dx%d\n", BoardSize,BoardSize);
            Flag = 0;
        }
    }

    return BoardSize;
}






//This function takes 2 input(an 2 dimensional array and its size)
int initializeBoard(char **TABLE, int n) {
    int i, j, min, IndexNumber;
    min = 33;



    //CREATING A ONE DIMENSIONAL ARRAY RANDOMLY THAT STORES OUR DESIRED SYMBOLS
    char *Symbols;
    Symbols = (char *) malloc(n * sizeof(char));
    if(Symbols==NULL) {
        printf("Allocation Failed");
        exit(1);
    }
    for(i=0; i<n; i++){
        Symbols[i]=min+i;
    }


    //CREATING A SYMBOL COUNTER TO MAKE SURE EACH SYMBOL USED n TIMES
    int *SymbolCounter;
    SymbolCounter = (int *) malloc(n * sizeof(int));
    if(SymbolCounter==NULL) {
        printf("Allocation Failed");
        exit(1);
    }
    for(i=0; i<n; i++){
        SymbolCounter[i]=0;
    }



    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            IndexNumber= rand() % n; //Getting Index Number Randomly

            //While any of the symbols are used n times, which means its counter == n, get again the index number so that we do not use that symbol which used already maximum times.
            while(n <= SymbolCounter[IndexNumber]){
                IndexNumber= rand() % n;
            }

            //Assigning the symbol table(2 dimensional one)
            TABLE[i][j] = Symbols[IndexNumber];
            SymbolCounter[IndexNumber]++;

        }
    }

    free(Symbols);
    free(SymbolCounter);

}


//  This function takes coordinates, ValidBoardSize and 2 dimensional Counter array to determine whether the entered coordinates are obey Coordinate Rules.
int getCoordinates(int Row1, int Column1, int Row2, int Column2, int MaxBoardSize, int **Counter) {

    //Checking whether the entered coordinates are between 2 and BoardSize
    if((Row1 < 1 || Column1 < 1 || Row2 < 1 || Column2 < 1) || (Row1 > MaxBoardSize || Row2 > MaxBoardSize || Column1 > MaxBoardSize || Column2 > MaxBoardSize)) {
        printf("Sorry, wrong coordinates!");
        return 0;
    }

    //Checking whether the entered coordinates are the same or not.
    else if((Row1 == Row2) && (Column1 == Column2)) {
        printf("Sorry, two door coordinates are same!");
        return 0;
    }

    //Checking whether the entered both coordinates are already opened or not.
    else if((Counter[Row1-1][Column1-1] == 1) && (Counter[Row2-1][Column2-1] == 1)) {
        printf("(%d,%d) already opened!\n(%d,%d) already opened!", Row1,Column1,Row2,Column2);
        return 0;
    }

    //Checking whether the entered first coordinate is already opened or not.
    else if(Counter[Row1-1][Column1-1] == 1) {
        printf("(%d,%d) already opened!", Row1,Column1);
        return 0;
    }

    //Checking whether the entered second coordinate is already opened or not.
    else if(Counter[Row2-1][Column2-1] == 1) {
        printf("(%d,%d) already opened!", Row2,Column2);
        return 0;
    }
    else {
        return 1;
    }

}

//This function takes the coordinates and 2 Dimensional Symbol Array to check whether the Cordinates entered by user points the same symbols.
int checkCharacters(int Row1, int Column1, int Row2, int Column2, char **DATA) {

    if(DATA[Row1-1][Column1-1] == DATA[Row2-1][Column2-1])
        return 1;
    else
        return 0;
}


// This Function Displays the '@'Table(2 dimensional Displayed array)
void displayBoard(char **DISPLAYEDTABLE, int Size) {
    int i, j;

    printf(" ");
    for (i = 1; i <= Size; i++) {
        printf("%6d", i);
    }
    printf("\n");

    for (i = 1; i <= Size; i++) {
        printf("%d", i);
        for (j = 1; j <= Size; j++) {
            printf("%6c", DISPLAYEDTABLE[i-1][j-1]);
        }
        if(i != Size) {
            printf("\n");
        }
    }


}