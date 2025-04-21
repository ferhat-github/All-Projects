//Ferhat Kasım KOÇ

#include <stdio.h>
#define LF 10

int main() {
    int Selected_Option, Selected_Base, A, B, Bin, D, Bout, Base2_Rules, Base16_Rules, Binary_Rule, k, LessThanThreeRule, MoreThanThreeRule, ValidNumberRuleBase16, DigitRuleBase16;
    char digit1, digit2, digit3, digit4, MainInput, LineFeed;

    //The part where the user select the option.
    printf("Welcome to Full Subtractor!\n\n ");
    printf("\t(1) Compute and Display the outputs\n");
    printf("\t(2) Quit\n");
    printf("You Choose:");
    scanf("%d", &Selected_Option);

// Diving Option1 which is Computing and Displaying the outputs.
    while(Selected_Option == 1) {
        fflush(stdin); // Cleaning the Buffer.
        printf("You have chosen option %d\n\n", Selected_Option);
        printf("Which base will you use to enter input (base 2 or base 16)?");
        scanf("%d", &Selected_Base);

        // If user inputs "2", calculations according to Base2 will start.
        if(Selected_Base == 2) {

            // Base2_Rules is started as 1 but at the end of loop, if all Base2_Rules are satisfied it will turn 0.
            Base2_Rules = 1 ;
            while(Base2_Rules) {

                fflush(stdin); // Cleaning the Buffer.
                printf("Please enter input:");
                scanf("%c", &MainInput); // MainInput assigned as the leftmost character of the User's input.
                digit1 = MainInput;

                // Until Reaching Line Feed of MainInput this condition will happen.
                while(MainInput != LF) {
                    if(digit1 != LF) {
                        scanf("%c", &MainInput);
                        digit2 = MainInput;
                        if(digit2 == LF) break;
                    }
                    if(digit2 != LF) {
                        scanf("%c", &MainInput);
                        digit3 = MainInput;
                        if(digit3 == LF) break;
                    }
                    if(digit3 != LF) {
                        scanf("%c", &MainInput);
                        digit4 = MainInput;
                        if(digit4 != LF) break;
                    }
                }

                //Rules About Base2
                LessThanThreeRule = ((digit1 == LF) || (digit2 == LF) || (digit3 == LF)); //If any of the first three digits equals LF this means the input is less than three bits. Therefore LessThanThreeRule turns 1
                MoreThanThreeRule = (digit4 != LF); // If digit4 is not equal to LF this means the input is more than three bits. Therefore MoreThanThreeRule turns 1
                Binary_Rule = (((digit1 == '0') || (digit1 == '1')) && ((digit2 == '0') || (digit2 == '1') || (digit2 == LF)) && ((digit3 == '0') || (digit3 == '1') || ((digit2 == LF) || digit3 == LF)));
                if(!Binary_Rule)
                    printf("Invalid number in base 2! Please try again!\n");
                else if(LessThanThreeRule)
                    printf("You entered less than 3 bits! Please try again!\n");
                else if(MoreThanThreeRule)
                    printf("You entered more than 3 bits! Please try again!\n");
                else
                    Base2_Rules = 0;
            }

            //Turning Character values to integer values and assigning them to A, B and Bin
            A = digit1 - '0';
            B = digit2 - '0';
            Bin = digit3 - '0';
            //Calculations of D and Bout values...
            if (A == B) {
                k = 0;
            }
            else {
                k = 1;
            }
            if(k == Bin) {
                D = 0;
            }
            else {
                D = 1;
            }
            Bout = ((!A && Bin) || (!A && B) || (B && Bin));
            printf("D is %d Bout is %d\n", D, Bout);

        }



        else {
            // If user do not inputs "2",this means they want to input values according to base16
            Base16_Rules = 1;
            while(Base16_Rules) {

                fflush(stdin);
                printf("Please enter input:");
                scanf("%c%c", &MainInput, &LineFeed);
                ValidNumberRuleBase16 = ((((MainInput >= 'A') && (MainInput <= 'F')) || ((MainInput >= '0') && (MainInput <= '9'))) && (LineFeed == LF));  // If the users inputs the value between A-F and 0-9 and  LineFeed=LF(Which means the user entered only 1 digit) this rule turns 1
                DigitRuleBase16 = (((MainInput > '7') && (MainInput <= '9')) || ((MainInput >= 'A') && (MainInput <= 'F'))); // If the user enters the value between these interval this value turns 1
                if(!ValidNumberRuleBase16) { // If ValidNumberRuleBase16 turned 0 which means does not satisfy our expected base16 value then this condition turns 1. If satisfy then this condition turns 0
                    printf("Invalid number in base 16! Please try again!\n");
                }
                else if(DigitRuleBase16) { //If input entered from user satisfy the DigitRuleBase16(Which means turns it 1) therefore this means it is not possible to convert it to 3 digit.
                    printf("Not possible to convert it to 3-digit binary number. Please try again!\n");
                }
                else { // if both if statement above this line can be skipped, this means the user entered the expected values in terms of digit rules and valid number rules of base 16. Therefore we can now calculate our A, B, Bin values with respect to given input from the user.
                    if( MainInput == '0') {
                        A = 0;
                        B = 0;
                        Bin = 0;
                        Base16_Rules = 0;
                    }
                    else if( MainInput == '1') {
                        A = 0;
                        B = 0;
                        Bin = 1;
                        Base16_Rules = 0;
                    }
                    else if( MainInput == '2') {
                        A = 0;
                        B = 1;
                        Bin = 0;
                        Base16_Rules = 0;
                    }
                    else if( MainInput == '3') {
                        A = 0;
                        B = 1;
                        Bin = 1;
                        Base16_Rules = 0;
                    }
                    else if( MainInput == '4') {
                        A = 1;
                        B = 0;
                        Bin = 0;
                        Base16_Rules = 0;
                    }
                    else if( MainInput == '5') {
                        A = 1;
                        B = 0;
                        Bin = 1;
                        Base16_Rules = 0;
                    }
                    else if( MainInput == '6') {
                        A = 1;
                        B = 1;
                        Bin = 0;
                        Base16_Rules = 0;
                    }
                    else {
                        A = 1;
                        B = 1;
                        Bin = 1;
                        Base16_Rules = 0;
                    }

                }

            }

            //Calculations of D and Bout values...
            if (A == B) {
                k = 0;
            }
            else {
                k = 1;
            }
            if(k == Bin) {
                D = 0;
            }
            else {
                D = 1;
            }
            Bout = ((!A && Bin) || (!A && B) || (B && Bin));

            printf("D is %d Bout is %d\n", D, Bout);
            fflush(stdin);
        }

        // Asking to the user again to choose what they what. All these steps will happen again until the user inputs 2 which is Quit.

        printf("\nWelcome to Full Subtractor!\n\n ");
        printf("\t(1) Compute and Display the outputs\n");
        printf("\t(2) Quit\n");
        printf("You Choose:");
        scanf("%d", &Selected_Option);
    }


    printf("You have chosen option %d\n", Selected_Option);
    printf("BYEE!!");
    return 0;
}