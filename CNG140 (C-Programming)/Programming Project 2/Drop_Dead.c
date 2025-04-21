//Ferhat Kasim KOC

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int roll_a_dice();
int play_computer(int);
int play_user(int);
void scoresheet(int, int, int, int);
int main() {

    int StartingDiceComputer, StartingDiceUser, Round=0, RoundCounter, TotalScoreOfComputer=0, TotalScoreOfUser=0;
    srand(time(NULL));

    printf("Welcome to the Drop Dead game.\nLet's get started!\n\nHow many rounds would you like to play?");
    scanf("%d", &RoundCounter);


//Determining the starting dice of the Computer and the User
    do {
        StartingDiceComputer = roll_a_dice();
        StartingDiceUser = roll_a_dice();

        if(StartingDiceComputer == StartingDiceUser) {
            printf("\nI have rolled the dice and got %d!\n", StartingDiceComputer);
            printf("I have rolled the dice for you and you got %d!\n", StartingDiceUser);
            printf("I'm rolling the dice again.\n");
        }

    }while(StartingDiceUser == StartingDiceComputer); //If the dice are the same then the dice will be rolled again


    printf("\nI have rolled the dice and got %d!\n", StartingDiceComputer);
    printf("I have rolled the dice for you and you got %d!", StartingDiceUser);

    //This loop will be executed as many as the number of rounds the user wants(RoundCounter).
    for(Round=1; Round<=RoundCounter; Round++) {


        //If the Computer's starting dice are larger than the User's, the game will be played in that order(Computer starts first).
        if(StartingDiceComputer > StartingDiceUser) {
            printf("\n\nRound %d -- My Turn:", Round);
            printf("\n___________________________________________________________________");
            TotalScoreOfComputer += play_computer(TotalScoreOfComputer); //TotalScoreOfComputer value is at first = 0. It will pass its value to the play_computer() function, then will be summed with the return value of play_computer() and then again it will pass its summed value to the play_computer() function when it called.

            printf("\n\nRound %d -- Your Turn:", Round);
            printf("\n___________________________________________________________________");
            printf("\nAre you ready to play!");
            TotalScoreOfUser += play_user(TotalScoreOfUser); //TotalScoreOfUser value is at first = 0. It will pass its value to the play_user() function, then will be summed with the return value of play_user() and then again it will pass its summed value to the play_user() function when it called.

            //Round, RoundCounter, TotalScoreOfComputer, TotalScoreOfUser(Order is IMPORTANT) values are sent to the scoresheet function for processing.
            scoresheet(Round, RoundCounter, TotalScoreOfComputer, TotalScoreOfUser);

        }


        //If the User's starting dice are larger than the Computer's, the game will be played in that order(User starts first).
        if(StartingDiceComputer < StartingDiceUser) {
            printf("\n\nRound %d -- Your Turn:", Round);
            printf("\n___________________________________________________________________");
            printf("\nAre you ready to play!");
            TotalScoreOfUser += play_user(TotalScoreOfUser); //TotalScoreOfUser value is at first = 0. It will pass its value to the play_user() function, then will be summed with the return value of play_user() and then again it will pass its summed value to the play_user() function when it called.

            printf("\n\nRound %d -- My Turn:", Round);
            printf("\n___________________________________________________________________");
            TotalScoreOfComputer += play_computer(TotalScoreOfComputer); //TotalScoreOfComputer value is at first = 0. It will pass its value to the play_computer() function, then will be summed with the return value of play_computer() and then again it will pass its summed value to the play_computer() function when it called.

            //Round, RoundCounter, TotalScoreOfComputer, TotalScoreOfUser(Order is IMPORTANT) values are sent to the scoresheet function for processing.
            scoresheet(Round, RoundCounter, TotalScoreOfComputer, TotalScoreOfUser);

        }


    }
    return 0;
}



//This function returns an integer value between 1 and 6 (both included).
int roll_a_dice() {
    return rand() % 6 + 1;
}


//This function is our computer that plays the game.
//This function takes the value of TotalScoreOfComputer from main function as an integer and assigns it TOTAL_FROM_MAIN variable then calculates and returns the desired score.
int play_computer(int TOTAL_FROM_MAIN) {
    int dice1, dice2, dice3, dice4, dice5, score, Total_Score_Of_Dice=0, i, j, Grand_Total;
    int ExcludedDice1, ExcludedDice2, ExcludedDice3, ExcludedDice4, ExcludedDice5;
    int ScoreKiller1, ScoreKiller2, ScoreKiller3, ScoreKiller4, ScoreKiller5;


    dice1 = roll_a_dice();
    dice2 = roll_a_dice();
    dice3 = roll_a_dice();
    dice4 = roll_a_dice();
    dice5 = roll_a_dice();

//Until all 5 dices become 0, this loop will be executed.
    do{
        score=0;
        printf("\nI got ");

        //Until dice1 becomes 0(only if when dice1 becomes 2 or 5) this will be executed. (Same applied other dices.)
        if(dice1 != 0) {
            printf("[Dice 1]: %d ", dice1);
            if(dice1 == 2 || dice1 == 5) {
                //dice1 became 2or5. Therefore, this dice should not be part of other turns(should be excluded).  (Same applied other dices.)
                dice1 = 0;
                ExcludedDice1 = 0;  //This value will be used when we exclude dice1 from our game.  (Same applied other dices.)
                ScoreKiller1 = 0;   //This value will be used when we want to make the score directly 0 because dice1 is 2 or 5.   (Same applied other dices.)
            }
            else {
                //dice1 is neither 2 nor 5. Therefore, we can add the value of dice1 to the score and roll dice1 again.  (Same applied other dices.)
                score += dice1;
                dice1 = roll_a_dice();
            }
        }
        if(dice2 != 0) {
            printf("[Dice 2]: %d ", dice2);
            if(dice2 == 2 || dice2 == 5) {
                dice2 = 0;
                ExcludedDice2 = 0;
                ScoreKiller2 = 0;
            }
            else {
                score += dice2;
                dice2 = roll_a_dice();
            }
        }
        if(dice3 != 0) {
            printf("[Dice 3]: %d ", dice3);
            if(dice3 == 2 || dice3 == 5) {
                dice3 = 0;
                ExcludedDice3 = 0;
                ScoreKiller3 = 0;
            }
            else {
                score += dice3;
                dice3 = roll_a_dice();
            }
        }
        if(dice4 != 0) {
            printf("[Dice 4]: %d ", dice4);
            if(dice4 == 2 || dice4 == 5) {
                dice4 = 0;
                ExcludedDice4 = 0;
                ScoreKiller4 = 0;
            }
            else {
                score += dice4;
                dice4 = roll_a_dice();
            }
        }
        if(dice5 != 0) {
            printf("[Dice 5]: %d ", dice5);
            if(dice5 == 2 || dice5 == 5) {
                dice5 = 0;
                ExcludedDice5 = 0;
                ScoreKiller5 = 0;
            }
            else {
                score += dice5;
                dice5 = roll_a_dice();
            }
        }


        //This loop allows us to make the score=0 when any dice become 2 or 5.(Because when any dice become 2 or 5, they will make their ScoreKiller variable 0. Therefore, if condition turns TRUE)
        //Note: Each body part of if statement can be executed once each round. Because when it is executed, its ScoreKiller variable becomes 1. Therefore, if condition turns FALSE.
        for(j=0; j<1; j++) {
            if(ScoreKiller1 == 0) {
                score = 0;
                ScoreKiller1 = 1;
            }
            if(ScoreKiller2 == 0) {
                score = 0;
                ScoreKiller2 = 1;
            }
            if(ScoreKiller3 == 0) {
                score = 0;
                ScoreKiller3 = 1;
            }
            if(ScoreKiller4 == 0) {
                score = 0;
                ScoreKiller4 = 1;
            }
            if(ScoreKiller5 == 0) {
                score = 0;
                ScoreKiller5 = 1;
            }

        }



        //When all dices become 0 this means the round is over for that player(Computer)
        if(dice1 == 0 && dice2 == 0 && dice3 == 0 && dice4 == 0 && dice5 == 0) {
            printf("\nDrop Dead!");
        }


        //Total_Score_Of_Dice is sum of scores that collected from current round.
        Total_Score_Of_Dice += score;
        //Grand_Total is sum of scores from current round(Total_Score_Of_Dice) and previous rounds(TOTAL_FROM_MAIN).
        Grand_Total = Total_Score_Of_Dice + TOTAL_FROM_MAIN;
        printf("\nMy score: %d Total score: %d\n", score, Grand_Total);


        //When score is 0(Which means there is one or more dice that became 2 or 5 therefore these dices became 0) and there are is one or more dice that didn't become 2 or 5 yet, this condition turns TRUE.
        if((score==0) && (dice1 != 0 || dice2 != 0 || dice3 != 0 || dice4 != 0 || dice5 != 0)) {
            //This loop allows us to print Excluded dice or dices.
            for (i = 0; i < 1; i++) {
                if (ExcludedDice1 == 0) {
                    printf("Dice 1 ");
                    ExcludedDice1 = 1; //When "Dice 1" printed, ExcludedDice1 variable becomes 1. This allows us to print "Dice 1" once because dice1 can be excluded only one time each round of Computer.  (Same applied other dice Exclusion)
                }
                if (ExcludedDice2 == 0) {
                    printf("Dice 2 ");
                    ExcludedDice2 = 1;
                }
                if (ExcludedDice3 == 0) {
                    printf("Dice 3 ");
                    ExcludedDice3 = 1;
                }
                if (ExcludedDice4 == 0) {
                    printf("Dice 4 ");
                    ExcludedDice4 = 1;
                }
                if (ExcludedDice5 == 0) {
                    printf("Dice 5 ");
                    ExcludedDice5 = 1;
                }

                printf("are excluded!\n");

            }

        }


    }while((dice1!=0 || dice2!=0 || dice3!=0 || dice4!=0 || dice5!=0));

    return Total_Score_Of_Dice;
}





//This function is just a copy of play_computer() function.
//Note: The variables that created in this function (play_user()) are different. These variables can only be accessed and edited in play_user() function!
//This function takes the value of TotalScoreOfUser from main function as an integer and assigns it TOTAL_FROM_MAIN variable then calculates and returns the desired score.
int play_user(int TOTAL_FROM_MAIN) {
    int dice1, dice2, dice3, dice4, dice5, score, Total_Score_Of_Dice=0, PrintedTotal, i, j, k, Grand_Total;
    int ExcludedDice1, ExcludedDice2, ExcludedDice3, ExcludedDice4, ExcludedDice5;
    int ScoreKiller1, ScoreKiller2, ScoreKiller3, ScoreKiller4, ScoreKiller5;


    dice1 = roll_a_dice();
    dice2 = roll_a_dice();
    dice3 = roll_a_dice();
    dice4 = roll_a_dice();
    dice5 = roll_a_dice();

    k = 0;

    do{
        score=0;

        if(k == 1) {
            printf("\nI rolled and you got\n");
        }

        if(k == 0) {
            printf("\nI rolled them for you and you got\n");
            k = 1;
        }


        if(dice1 != 0) {
            printf("[Dice 1]: %d ", dice1);
            if(dice1 == 2 || dice1 == 5) {
                dice1 = 0;
                ExcludedDice1 = 0;
                ScoreKiller1 = 0;
            }
            else {
                score += dice1;
                dice1 = roll_a_dice();
            }
        }
        if(dice2 != 0) {
            printf("[Dice 2]: %d ", dice2);
            if(dice2 == 2 || dice2 == 5) {
                dice2 = 0;
                ExcludedDice2 = 0;
                ScoreKiller2 = 0;
            }
            else {
                score += dice2;
                dice2 = roll_a_dice();
            }
        }
        if(dice3 != 0) {
            printf("[Dice 3]: %d ", dice3);
            if(dice3 == 2 || dice3 == 5) {
                dice3 = 0;
                ExcludedDice3 = 0;
                ScoreKiller3 = 0;
            }
            else {
                score += dice3;
                dice3 = roll_a_dice();
            }
        }
        if(dice4 != 0) {
            printf("[Dice 4]: %d ", dice4);
            if(dice4 == 2 || dice4 == 5) {
                dice4 = 0;
                ExcludedDice4 = 0;
                ScoreKiller4 = 0;
            }
            else {
                score += dice4;
                dice4 = roll_a_dice();
            }
        }
        if(dice5 != 0) {
            printf("[Dice 5]: %d ", dice5);
            if(dice5 == 2 || dice5 == 5) {
                dice5 = 0;
                ExcludedDice5 = 0;
                ScoreKiller5 = 0;
            }
            else {
                score += dice5;
                dice5 = roll_a_dice();
            }
        }




        for(j=0; j<1; j++) {
            if(ScoreKiller1 == 0) {
                score = 0;
                ScoreKiller1 = 1;
            }
            if(ScoreKiller2 == 0) {
                score = 0;
                ScoreKiller2 = 1;
            }
            if(ScoreKiller3 == 0) {
                score = 0;
                ScoreKiller3 = 1;
            }
            if(ScoreKiller4 == 0) {
                score = 0;
                ScoreKiller4 = 1;
            }
            if(ScoreKiller5 == 0) {
                score = 0;
                ScoreKiller5 = 1;
            }

        }



        if(dice1 == 0 && dice2 == 0 && dice3 == 0 && dice4 == 0 && dice5 == 0) {
            printf("\nDrop Dead!");
        }

        Total_Score_Of_Dice += score;
        Grand_Total = Total_Score_Of_Dice + TOTAL_FROM_MAIN;
        printf("\nYour score: %d Total score: %d\n", score, Grand_Total);

        if((score==0) && (dice1 != 0 || dice2 != 0 || dice3 != 0 || dice4 != 0 || dice5 != 0)) {

            for (i = 0; i < 1; i++) {
                if (ExcludedDice1 == 0) {
                    printf("Dice 1 ");
                    ExcludedDice1 = 1;
                }
                if (ExcludedDice2 == 0) {
                    printf("Dice 2 ");
                    ExcludedDice2 = 1;
                }
                if (ExcludedDice3 == 0) {
                    printf("Dice 3 ");
                    ExcludedDice3 = 1;
                }
                if (ExcludedDice4 == 0) {
                    printf("Dice 4 ");
                    ExcludedDice4 = 1;
                }
                if (ExcludedDice5 == 0) {
                    printf("Dice 5 ");
                    ExcludedDice5 = 1;
                }

                printf("are excluded!\n");

            }

        }


    }while((dice1!=0 || dice2!=0 || dice3!=0 || dice4!=0 || dice5!=0));

    return Total_Score_Of_Dice;
}




//This function takes inputs from main function and process them to create a ScoreSheet
void scoresheet(int R, int RCounter, int ComputerScore, int UserScore) {

    printf("\n\nOur score sheet after round %d:", R);
    printf("\n==============================");

    printf("\nMy score    Your score");
    printf("\n%d%13d\n", ComputerScore, UserScore);

//Deciding who is the winner.
    if(R == RCounter) {
        if (ComputerScore > UserScore) {
            printf("\nI AM THE WINNER!");
        } else if (ComputerScore < UserScore) {
            printf("\nYOU ARE THE WINNER!");
        } else {
            printf("\nOUR SCORES ARE EQUAL. THEREFORE, OUR FRIENDSHIP IS THE WINNER! :)");
        }
    }

}



