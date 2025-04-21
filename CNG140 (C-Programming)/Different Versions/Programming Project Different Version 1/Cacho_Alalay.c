//FERHAT KASIM KOÇ


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int roll_a_dice();
int play_computer(int);
int play_user(int);
void scoresheet(int, int, int, int);



int main() {

    int Round_Count, Current_Round, Starting_Computer, Starting_User, Total_Computer=0, Total_User=0;

    srand(time(NULL));


    printf("Welcome to the Cacho Alalay game.\n Let's get started!\n\nHow many rounds would you like to play?");
    scanf("%d", &Round_Count);

    //This loop decides who is gonna play first. If they have same dices, they will roll the dices again.
    do {
        Starting_Computer = roll_a_dice();
        Starting_User = roll_a_dice();

        if(Starting_Computer == Starting_User) {
            printf("\nI have rolled the dice and got %d!\n", Starting_Computer);
            printf("I have rolled the dice for you and you got %d!\n", Starting_User);
            printf("\nRerolling Again!\n");
        }

    }while(Starting_User == Starting_Computer);

    printf("\nI have rolled the dice and got %d!\nI have rolled the dice for you and you got %d!", Starting_Computer, Starting_User);

    if(Starting_Computer > Starting_User) {
        printf("\n\nI go first!");
    }
    else {
        printf("\n\nYou go first!");
    }



    for(Current_Round = 1; Current_Round <= Round_Count; Current_Round++) {

        if(Starting_Computer > Starting_User) {

            printf("\n\nRound %d --- Computer:\n___________________", Current_Round);
            Total_Computer += play_computer(Total_Computer);

            printf("\n\nRound %d --- Player:\n___________________\nGet ready to play!", Current_Round);
            Total_User += play_user(Total_User);

            scoresheet(Current_Round, Round_Count, Total_Computer, Total_User);
        }
        else {

            printf("\n\nRound %d --- Player:\n___________________\nGet ready to play!", Current_Round);
            Total_User += play_user(Total_User);

            printf("\n\nRound %d --- Computer:\n___________________", Current_Round);
            Total_Computer += play_computer(Total_Computer);

            scoresheet(Current_Round, Round_Count, Total_Computer, Total_User);
        }
    }
    return 0;
}




int roll_a_dice() {
    int x;

    x = rand() % 6 + 1;

    return x;
}



int play_user(int Score_Passed) {


    int dice_1, dice_2, dice_3, dice_4, dice_5, Round_Score=0, Total_Score=0;
    int Amount_Of_Ones, Amount_Of_Twos, Amount_Of_Threes, Amount_Of_Fours, Amount_Of_Fives, Amount_Of_Sixes;
    int Escalera_Counter=0, UnFull_Counter=0, Poker_Counter=0, First_Round_Flag_Escalera=0, First_Round_Flag_UnFull=0, First_Round_Flag_Poker=0;
    int Score_Of_Ones, Score_Of_Twos, Score_Of_Threes, Score_Of_Fours, Score_Of_Fives, Score_Of_Sixes, Maximum_Score, Already_Excluded_Flag=0;
    int Keeping_Dice1=0, Keeping_Dice2=0, Keeping_Dice3=0, Keeping_Dice4=0, Keeping_Dice5=0, Selected_Dice_Number;
    int Temp_Keeping_Dice1, Temp_Keeping_Dice2, Temp_Keeping_Dice3, Temp_Keeping_Dice4, Temp_Keeping_Dice5;
    char Kept_Dice;



    dice_1 = roll_a_dice();
    dice_2 = roll_a_dice();
    dice_3 = roll_a_dice();
    dice_4 = roll_a_dice();
    dice_5 = roll_a_dice();

    printf("\nI rolled dices for you and you got\n-> ");

    int tour_counter = 3;
    do {

        //This Variables will be used to calculate the amount of numbers(Between 1-6) that dices become.
        Amount_Of_Ones=0;
        Amount_Of_Twos=0;
        Amount_Of_Threes=0;
        Amount_Of_Fours=0;
        Amount_Of_Fives=0;
        Amount_Of_Sixes=0;

        //If it is not the first tour this information will be printed
        if(tour_counter != 3) {
            printf("\nI rolled the remaining and you got:\n-> ");
        }



        //If dice 1 is not kept, then this will be printed every tour until dice 1 become kept. Same things will be applied to other dices.
        if(Keeping_Dice1 == 0) {
            printf("[Dice 1]: %d ", dice_1);
        }
        //These conditions will help us to calculete how many ones, twos, threes etc. we have. Same thigs will be applied to other dices.
        if(dice_1 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_1 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_1 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_1 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_1 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        if(Keeping_Dice2 == 0) {
            printf("[Dice 2]: %d ", dice_2);
        }

        if(dice_2 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_2 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_2 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_2 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_2 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        if(Keeping_Dice3 == 0) {
            printf("[Dice 3]: %d ", dice_3);
        }

        if(dice_3 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_3 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_3 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_3 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_3 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        if(Keeping_Dice4 == 0) {
            printf("[Dice 4]: %d ", dice_4);
        }

        if(dice_4 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_4 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_4 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_4 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_4 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        if(Keeping_Dice5 == 0) {
            printf("[Dice 5]: %d ", dice_5);
        }

        if(dice_5 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_5 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_5 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_5 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_5 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }



        //If there are 5 of any numbers this condition turns TRUE
        if(Amount_Of_Ones==5 || Amount_Of_Twos==5 || Amount_Of_Threes==5 || Amount_Of_Fours==5 || Amount_Of_Fives==5 || Amount_Of_Sixes==5) {

            printf("\nYou got Grande!");

            Round_Score = 50;
        }

            //If there are 4 of any numbers this condition turns TRUE
        else if(Amount_Of_Ones==4 || Amount_Of_Twos==4 || Amount_Of_Threes==4 || Amount_Of_Fours==4 || Amount_Of_Fives==4 || Amount_Of_Sixes==4) {

            printf("\nYou got Poker!");

            //First_Round_Flag_Poker initialized 0 at first. When tour counter is 3, which means it is first rolling(tour), computer gains 45 score and First_Round_Flag_Poker becomes 1
            //so that while computer rolls remaining dices when it hits this condition again, second if condition (Which is tour_counter != 3 && First_Round_Flag_Poker == 0) won't be True
            //even if tour_counter!=3 is true, because computer already gained 45 point when tour counter==3(which is first rolling).
            //I applied the same logic to UnFull and Escalera cases.
            if(tour_counter == 3){
                Round_Score = 45;
                First_Round_Flag_Poker = 1;
            }
            if(tour_counter != 3 && First_Round_Flag_Poker == 0) {
                Round_Score = 40;
            }
        }


        else if((Amount_Of_Ones==3 || Amount_Of_Twos==3 || Amount_Of_Threes==3 || Amount_Of_Fours==3 || Amount_Of_Fives==3 || Amount_Of_Sixes==3) && (Amount_Of_Ones==2 || Amount_Of_Twos==2 || Amount_Of_Threes==2 || Amount_Of_Fours==2 || Amount_Of_Fives==2 || Amount_Of_Sixes==2)) {

            printf("\nYou got Un Full!");


            if(tour_counter == 3){
                Round_Score = 35;
                First_Round_Flag_Poker = 1;
            }
            if(tour_counter != 3 && First_Round_Flag_Poker == 0) {
                Round_Score = 30;
            }

        }


        else if((dice_1==1 && dice_2==2 && dice_3==3 && dice_4==4 && dice_5==5) || (dice_1==2 && dice_2==3 && dice_3==4 && dice_4==5 && dice_5==6)) {

            printf("\nYou got Escalera!");


            if(tour_counter == 3){
                Round_Score = 25;
                First_Round_Flag_Poker = 1;
            }
            if(tour_counter != 3 && First_Round_Flag_Poker == 0) {
                Round_Score = 20;
            }

        }


        else {

            //Calculating Scores
            Score_Of_Ones = Amount_Of_Ones;
            Score_Of_Twos = Amount_Of_Twos * 2;
            Score_Of_Threes = Amount_Of_Threes * 3;
            Score_Of_Fours = Amount_Of_Fours * 4;
            Score_Of_Fives = Amount_Of_Fives * 5;
            Score_Of_Sixes = Amount_Of_Sixes * 6;
            Maximum_Score = 0;


            // Choosing the maximum score possible
            Selected_Dice_Number = 0;
            if ((Score_Of_Ones > Maximum_Score) && (Amount_Of_Ones >= 2)) {
                Maximum_Score = Score_Of_Ones;
            }
            if ((Score_Of_Twos > Maximum_Score)  && (Amount_Of_Twos >= 2)) {
                Maximum_Score = Score_Of_Twos;
            }
            if ((Score_Of_Threes > Maximum_Score)  && (Amount_Of_Threes >= 2)) {
                Maximum_Score = Score_Of_Threes;
            }
            if ((Score_Of_Fours > Maximum_Score)  && (Amount_Of_Fours >= 2)) {
                Maximum_Score = Score_Of_Fours;
            }
            if ((Score_Of_Fives > Maximum_Score)  && (Amount_Of_Fives >= 2)) {
                Maximum_Score = Score_Of_Fives;
            }
            if ((Score_Of_Sixes > Maximum_Score)  && (Amount_Of_Sixes >= 2)) {
                Maximum_Score = Score_Of_Sixes;
            }

            Round_Score = Maximum_Score;
        }






        //If it is not last turn or there are at least one not kept dice, this condition will be true
        if ((tour_counter != 1) && (Keeping_Dice1==0 || Keeping_Dice2==0 || Keeping_Dice3==0 || Keeping_Dice4==0 || Keeping_Dice5==0)) {

            // Temp_Keeping dices will be used to reload old kept dice information if the user tries to re-roll an already removed dice.
            Temp_Keeping_Dice1 = Keeping_Dice1;
            Temp_Keeping_Dice2 = Keeping_Dice2;
            Temp_Keeping_Dice3 = Keeping_Dice3;
            Temp_Keeping_Dice4 = Keeping_Dice4;
            Temp_Keeping_Dice5 = Keeping_Dice5;


            printf("\nCurrent round score: %d\nWhich ones do you want to keep?", Round_Score);
            fflush(stdin);
            scanf("%c", &Kept_Dice);

            //At first, already excluded flag is 0 but when user tries to keep a dice which is already excluded, Already_Excluded_Flag becomes 1 so that this loop can be executed again.
            while ((Kept_Dice != '\n') || (Already_Excluded_Flag==1)) {



                if (Kept_Dice != ' ') {

                    if (Kept_Dice == '1') {
                        if(Keeping_Dice1 == 1) {
                            printf("\nYou have already excluded Dice 1! Please re-try");
                            Already_Excluded_Flag = 1;
                        }
                        else {
                            Keeping_Dice1 = 1;
                            Already_Excluded_Flag = 0;
                        }
                    }

                    else if (Kept_Dice == '2') {
                        if(Keeping_Dice2 == 1) {
                            printf("\nYou have already excluded Dice 2! Please re-try");
                            Already_Excluded_Flag = 1;
                        }
                        else {
                            Keeping_Dice2 = 1;
                            Already_Excluded_Flag = 0;
                        }
                    }

                    else if (Kept_Dice == '3') {
                        if(Keeping_Dice3 == 1) {
                            printf("\nYou have already excluded Dice 3! Please re-try");
                            Already_Excluded_Flag = 1;
                        }
                        else {
                            Keeping_Dice3 = 1;
                            Already_Excluded_Flag = 0;
                        }
                    }

                    else if (Kept_Dice == '4') {
                        if(Keeping_Dice4 == 1) {
                            printf("\nYou have already excluded Dice 4! Please re-try");
                            Already_Excluded_Flag = 1;
                        }
                        else {
                            Keeping_Dice4 = 1;
                            Already_Excluded_Flag = 0;
                        }
                    }

                    else if (Kept_Dice == '5') {
                        if(Keeping_Dice5 == 1) {
                            printf("\nYou have already excluded Dice 5! Please re-try");
                            Already_Excluded_Flag = 1;
                        }
                        else {
                            Keeping_Dice5 = 1;
                            Already_Excluded_Flag = 0;
                        }
                    }

                }
                //Getting new input from user (Because, Already_Excluded_Flag became 1)
                if(Already_Excluded_Flag == 1) {
                    printf("\nWhich ones do you want to keep?");
                    fflush(stdin);
                    scanf("%c", &Kept_Dice);


                    Keeping_Dice1 = Temp_Keeping_Dice1;
                    Keeping_Dice2 = Temp_Keeping_Dice2;
                    Keeping_Dice3 = Temp_Keeping_Dice3;
                    Keeping_Dice4 = Temp_Keeping_Dice4;
                    Keeping_Dice5 = Temp_Keeping_Dice5;
                }
                else {
                    scanf("%c", &Kept_Dice);
                }

            }
        }


        if(Keeping_Dice1 == 0 ) {
            dice_1 = roll_a_dice();
        }
        if(Keeping_Dice2 == 0 ) {
            dice_2 = roll_a_dice();
        }
        if(Keeping_Dice3 == 0 ) {
            dice_3 = roll_a_dice();
        }
        if(Keeping_Dice4 == 0 ) {
            dice_4 = roll_a_dice();
        }
        if(Keeping_Dice5 == 0 ) {
            dice_5 = roll_a_dice();
        }


        tour_counter--;
    }while((tour_counter != 0) && (Keeping_Dice1==0 || Keeping_Dice2==0 || Keeping_Dice3==0 || Keeping_Dice4==0 || Keeping_Dice5==0));



    Total_Score = Round_Score + Score_Passed;
    printf("\nYour score: %d, Total Score: %d", Round_Score, Total_Score);


    return Round_Score;
}


int play_computer(int Score_Passed) {
    int dice_1, dice_2, dice_3, dice_4, dice_5, Round_Score=0, Total_Score=0;
    int Amount_Of_Ones, Amount_Of_Twos, Amount_Of_Threes, Amount_Of_Fours, Amount_Of_Fives, Amount_Of_Sixes;
    int Escalera_Counter=0, UnFull_Counter=0, Poker_Counter=0, First_Round_Flag_Escalera=0, First_Round_Flag_UnFull=0, First_Round_Flag_Poker=0;
    int Score_Of_Ones, Score_Of_Twos, Score_Of_Threes, Score_Of_Fours, Score_Of_Fives, Score_Of_Sixes, Maximum_Score, A_Flag=0;
    int Keeping_Dice1=0, Keeping_Dice2=0, Keeping_Dice3=0, Keeping_Dice4=0, Keeping_Dice5=0, Selected_Dice_Number;

    dice_1 = roll_a_dice();
    dice_2 = roll_a_dice();
    dice_3 = roll_a_dice();
    dice_4 = roll_a_dice();
    dice_5 = roll_a_dice();

    int tour_counter=3;
    do {
        //This Variables will be used to calculate the amount of numbers(Between 1-6) that dices become.
        Amount_Of_Ones=0;
        Amount_Of_Twos=0;
        Amount_Of_Threes=0;
        Amount_Of_Fours=0;
        Amount_Of_Fives=0;
        Amount_Of_Sixes=0;




        printf("\nI got -> ");

        //If dice 1 is not kept, then this will be printed every tour until dice 1 become kept. Same things will be applied to other dices.
        if(Keeping_Dice1 == 0) {
            printf("[Dice 1]: %d ", dice_1);
        }
        //These conditions will help us to calculete how many ones, twos, threes etc. we have. Same things will be applied to other dices.
        if(dice_1 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_1 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_1 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_1 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_1 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        if(Keeping_Dice2 == 0) {
            printf("[Dice 2]: %d ", dice_2);
        }

        if(dice_2 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_2 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_2 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_2 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_2 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        if(Keeping_Dice3 == 0) {
            printf("[Dice 3]: %d ", dice_3);
        }

        if(dice_3 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_3 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_3 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_3 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_3 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        if(Keeping_Dice4 == 0) {
            printf("[Dice 4]: %d ", dice_4);
        }

        if(dice_4 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_4 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_4 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_4 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_4 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        if(Keeping_Dice5 == 0) {
            printf("[Dice 5]: %d ", dice_5);
        }

        if(dice_5 == 1) {
            Amount_Of_Ones++;
        }
        else if(dice_5 == 2) {
            Amount_Of_Twos++;
        }
        else if(dice_5 == 3) {
            Amount_Of_Threes++;
        }
        else if(dice_5 == 4) {
            Amount_Of_Fours++;
        }
        else if(dice_5 == 5) {
            Amount_Of_Fives++;
        }
        else {
            Amount_Of_Sixes++;
        }




        //If there are 5 of any numbers this condition turns TRUE
        if(Amount_Of_Ones==5 || Amount_Of_Twos==5 || Amount_Of_Threes==5 || Amount_Of_Fours==5 || Amount_Of_Fives==5 || Amount_Of_Sixes==5) {
            printf("\nI got Grande!\nI am keeping dice ");
            if(Keeping_Dice1 == 0 ) {
                printf("1 ");
                Keeping_Dice1 = 1;

            }
            if(Keeping_Dice2 == 0 ) {
                printf("2 ");
                Keeping_Dice2 = 1;

            }
            if(Keeping_Dice3 == 0 ) {
                printf("3 ");
                Keeping_Dice3 = 1;

            }
            if(Keeping_Dice4 == 0 ) {
                printf("4 ");
                Keeping_Dice4 = 1;

            }
            if(Keeping_Dice5 == 0 ) {
                printf("5");
                Keeping_Dice5 = 1;
            }

            Round_Score = 50;
        }


        //If there are 4 of any numbers this condition turns TRUE
        else if(Amount_Of_Ones==4 || Amount_Of_Twos==4 || Amount_Of_Threes==4 || Amount_Of_Fours==4 || Amount_Of_Fives==4 || Amount_Of_Sixes==4) {

            if(Poker_Counter==0) {
                printf("\nI got Poker!\nI am keeping dice ");
                Poker_Counter=1;
            }

            //These conditions keep the dices which show same number(4 same numbers)
            if(Amount_Of_Ones == 4) {
                if(dice_1 == 1 && Keeping_Dice1==0) {
                    printf("1 ");
                    Keeping_Dice1=1;
                }
                if(dice_2 == 1 && Keeping_Dice2==0) {
                    printf("2 ");
                    Keeping_Dice2=1;
                }
                if(dice_3 == 1 && Keeping_Dice3==0) {
                    printf("3 ");
                    Keeping_Dice3=1;
                }
                if(dice_4 == 1 && Keeping_Dice4==0) {
                    printf("4 ");
                    Keeping_Dice4=1;
                }
                if(dice_1 == 4 && Keeping_Dice5==0) {
                    printf("5");
                    Keeping_Dice5=1;
                }
            }
            else if(Amount_Of_Twos == 4) {
                if(dice_1 == 2 && Keeping_Dice1==0) {
                    printf("1 ");
                    Keeping_Dice1=1;
                }
                if(dice_2 == 2 && Keeping_Dice2==0) {
                    printf("2 ");
                    Keeping_Dice2=1;
                }
                if(dice_3 == 2 && Keeping_Dice3==0) {
                    printf("3 ");
                    Keeping_Dice3=1;
                }
                if(dice_4 == 2 && Keeping_Dice4==0) {
                    printf("4 ");
                    Keeping_Dice4=1;
                }
                if(dice_5 == 2 && Keeping_Dice5==0) {
                    printf("5");
                    Keeping_Dice5=1;
                }
            }
            else if(Amount_Of_Threes == 4) {
                if(dice_1 == 3 && Keeping_Dice1==0) {
                    printf("1 ");
                    Keeping_Dice1=1;
                }
                if(dice_2 == 3 && Keeping_Dice2==0) {
                    printf("2 ");
                    Keeping_Dice2=1;
                }
                if(dice_3 == 3 && Keeping_Dice3==0) {
                    printf("3 ");
                    Keeping_Dice3=1;
                }
                if(dice_4 == 3 && Keeping_Dice4==0) {
                    printf("4 ");
                    Keeping_Dice4=1;
                }
                if(dice_5 == 3 && Keeping_Dice5==0) {
                    printf("5");
                    Keeping_Dice5=1;
                }
            }
            else if(Amount_Of_Fours == 4) {
                if(dice_1 == 4 && Keeping_Dice1==0) {
                    printf("1 ");
                    Keeping_Dice1=1;
                }
                if(dice_2 == 4 && Keeping_Dice2==0) {
                    printf("2 ");
                    Keeping_Dice2=1;
                }
                if(dice_3 == 4 && Keeping_Dice3==0) {
                    printf("3 ");
                    Keeping_Dice3=1;
                }
                if(dice_4 == 4 && Keeping_Dice4==0) {
                    printf("4 ");
                    Keeping_Dice4=1;
                }
                if(dice_5 == 4 && Keeping_Dice5==0) {
                    printf("5");
                    Keeping_Dice5=1;
                }
            }
            else if(Amount_Of_Fives == 4) {
                if(dice_1 == 5 && Keeping_Dice1==0) {
                    printf("1 ");
                    Keeping_Dice1=1;
                }
                if(dice_2 == 5 && Keeping_Dice2==0) {
                    printf("2 ");
                    Keeping_Dice2=1;
                }
                if(dice_3 == 5 && Keeping_Dice3==0) {
                    printf("3 ");
                    Keeping_Dice3=1;
                }
                if(dice_4 == 5 && Keeping_Dice4==0) {
                    printf("4 ");
                    Keeping_Dice4=1;
                }
                if(dice_5 == 5 && Keeping_Dice5==0) {
                    printf("5");
                    Keeping_Dice5=1;
                }
            }
            else if(Amount_Of_Sixes == 4) {
                if(dice_1 == 6 && Keeping_Dice1==0) {
                    printf("1 ");
                    Keeping_Dice1=1;
                }
                if(dice_2 == 6 && Keeping_Dice2==0) {
                    printf("2 ");
                    Keeping_Dice2=1;
                }
                if(dice_3 == 6 && Keeping_Dice3==0) {
                    printf("3 ");
                    Keeping_Dice3=1;
                }
                if(dice_4 == 6 && Keeping_Dice4==0) {
                    printf("4 ");
                    Keeping_Dice4=1;
                }
                if(dice_5 == 6 && Keeping_Dice5==0) {
                    printf("5");
                    Keeping_Dice5=1;
                }
            }


            //First_Round_Flag_Poker initialized 0 at first. When tour counter is 3, which means it is first rolling(tour), computer gains 45 score and First_Round_Flag_Poker becomes 1
            //so that while computer rolls remaining dices when it hits this condition again, second if condition (Which is tour_counter != 3 && First_Round_Flag_Poker == 0) won't be True
            //even if tour_counter!=3 is true, because computer already gained 45 point when tour counter==3(which is first rolling).
            //I applied the same logic to UnFull and Escalera cases.
            if(tour_counter == 3){
                Round_Score = 45;
                First_Round_Flag_Poker = 1;
            }
            if(tour_counter != 3 && First_Round_Flag_Poker == 0) {
                Round_Score = 40;
            }
        }

        else if((Amount_Of_Ones==3 || Amount_Of_Twos==3 || Amount_Of_Threes==3 || Amount_Of_Fours==3 || Amount_Of_Fives==3 || Amount_Of_Sixes==3) && (Amount_Of_Ones==2 || Amount_Of_Twos==2 || Amount_Of_Threes==2 || Amount_Of_Fours==2 || Amount_Of_Fives==2 || Amount_Of_Sixes==2)) {

            printf("\nI got Un Full!\nI am keeping dice ");

            if(Keeping_Dice1 == 0 ) {
                printf("1 ");
                Keeping_Dice1 = 1;
            }
            if(Keeping_Dice2 == 0 ) {
                printf("2 ");
                Keeping_Dice2 = 1;
            }
            if(Keeping_Dice3 == 0 ) {
                printf("3 ");
                Keeping_Dice3 = 1;
            }
            if(Keeping_Dice4 == 0 ) {
                printf("4 ");
                Keeping_Dice4 = 1;
            }
            if(Keeping_Dice5 == 0 ) {
                printf("5");
                Keeping_Dice5 = 1;
            }

            if(tour_counter == 3){
                Round_Score = 35;
                First_Round_Flag_UnFull = 1;
            }
            if(tour_counter != 3 && First_Round_Flag_UnFull == 0) {
                Round_Score = 30;
            }
        }

        else if((dice_1==1 && dice_2==2 && dice_3==3 && dice_4==4 && dice_5==5) || (dice_1==2 && dice_2==3 && dice_3==4 && dice_4==5 && dice_5==6)) {

            printf("\nI got Escalera!\nI am keeping dice ");
            if(Keeping_Dice1 == 0 ) {
                printf("1 ");
                Keeping_Dice1 = 1;

            }
            if(Keeping_Dice2 == 0 ) {
                printf("2 ");
                Keeping_Dice2 = 1;

            }
            if(Keeping_Dice3 == 0 ) {
                printf("3 ");
                Keeping_Dice3 = 1;

            }
            if(Keeping_Dice4 == 0 ) {
                printf("4 ");
                Keeping_Dice4 = 1;

            }
            if(Keeping_Dice5 == 0 ) {
                printf("5");
                Keeping_Dice5 = 1;
            }

            if(tour_counter == 3){
                Round_Score = 25;
                First_Round_Flag_Escalera = 1;
            }
            if(tour_counter != 3 && First_Round_Flag_Escalera == 0) {
                Round_Score = 20;
            }
        }


        else {
            //Calculating Scores
            Score_Of_Ones = Amount_Of_Ones;
            Score_Of_Twos = Amount_Of_Twos * 2;
            Score_Of_Threes = Amount_Of_Threes * 3;
            Score_Of_Fours = Amount_Of_Fours * 4;
            Score_Of_Fives = Amount_Of_Fives * 5;
            Score_Of_Sixes = Amount_Of_Sixes * 6;
            Maximum_Score = 0;


            // Choosing the maximum score possible
            Selected_Dice_Number = 0;
            if ((Score_Of_Ones > Maximum_Score) && (Amount_Of_Ones >= 2)) {
                Maximum_Score = Score_Of_Ones;
                //Selected Dice Number variable will help us to understand which number has 4 of itself
                Selected_Dice_Number = 1;
            }
            if ((Score_Of_Twos > Maximum_Score)  && (Amount_Of_Twos >= 2)) {
                Maximum_Score = Score_Of_Twos;
                Selected_Dice_Number = 2;
            }
            if ((Score_Of_Threes > Maximum_Score)  && (Amount_Of_Threes >= 2)) {
                Maximum_Score = Score_Of_Threes;
                Selected_Dice_Number = 3;

            }
            if ((Score_Of_Fours > Maximum_Score)  && (Amount_Of_Fours >= 2)) {
                Maximum_Score = Score_Of_Fours;
                Selected_Dice_Number = 4;

            }
            if ((Score_Of_Fives > Maximum_Score)  && (Amount_Of_Fives >= 2)) {
                Maximum_Score = Score_Of_Fives;
                Selected_Dice_Number = 5;

            }
            if ((Score_Of_Sixes > Maximum_Score)  && (Amount_Of_Sixes >= 2)) {
                Maximum_Score = Score_Of_Sixes;
                Selected_Dice_Number = 6;

            }


            //A Flag is 0 initially.
            //If there are no change at Maximum_Score, computer won't print this because it won't keep any dice.
            if(Maximum_Score != A_Flag) {
                printf("\nI am keeping dice ");
            }
            A_Flag = Maximum_Score;


            Round_Score = Maximum_Score;


            //Printing dices which should be kept.
            if((dice_1 == Selected_Dice_Number) && (Keeping_Dice1 == 0)) {
                printf("1 ");
                Keeping_Dice1 = 1;
            }
            if((dice_2 == Selected_Dice_Number) && (Keeping_Dice2 == 0)) {
                printf("2 ");
                Keeping_Dice2 = 1;
            }
            if((dice_3 == Selected_Dice_Number) && (Keeping_Dice3 == 0)) {
                printf("3 ");
                Keeping_Dice3 = 1;
            }
            if((dice_4 == Selected_Dice_Number) && (Keeping_Dice4 == 0)) {
                printf("4 ");
                Keeping_Dice4 = 1;
            }
            if((dice_5 == Selected_Dice_Number) && (Keeping_Dice5 == 0)) {
                printf("5 ");
                Keeping_Dice5 = 1;
            }
        }



        //re-rolling remaining dices.
        if(Keeping_Dice1 == 0 ) {
            dice_1 = roll_a_dice();
        }
        if(Keeping_Dice2 == 0 ) {
            dice_2 = roll_a_dice();
        }
        if(Keeping_Dice3 == 0 ) {
            dice_3 = roll_a_dice();
        }
        if(Keeping_Dice4 == 0 ) {
            dice_4 = roll_a_dice();
        }
        if(Keeping_Dice5 == 0 ) {
            dice_5 = roll_a_dice();
        }
        Total_Score = Round_Score + Score_Passed;
        printf("\nMy score: %d, Total Score: %d", Round_Score, Total_Score);
        tour_counter--;
    }while((tour_counter != 0) && (Keeping_Dice1==0 || Keeping_Dice2==0 || Keeping_Dice3==0 || Keeping_Dice4==0 || Keeping_Dice5==0));

    return Round_Score;
}




void scoresheet(int Current_Round, int Round_Count, int Computer_Score, int User_Score) {

    printf("\n\nOur score sheet after round %d:", Current_Round);
    printf("\n==============================");

    printf("\nComputer    Player");
    printf("\n%d%13d\n", Computer_Score, User_Score);

    if(Current_Round == Round_Count) {
        if (Computer_Score > User_Score) {
            printf("\n\nCOMPUTER WINS!");
        }
        else if (Computer_Score < User_Score) {
            printf("\n\nPLAYER WINS!");
        }
        else {
            printf("\n\nOUR SCORES ARE EQUAL, WHICH MEANS OUR FRIENDSHIP IS THE WINNER! :)");
        }
    }
}