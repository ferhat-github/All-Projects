//Ferhat Kasım Koç
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Data {
    char full_name[40];
    float x_initial;
    float x_final;
    float y_initial;
    float y_final;
    float width;
    float height;

};
typedef struct Data SIGNATURES;

SIGNATURES *Load_SignaturesTable(char *, int *);
void Display_SignaturesTable(SIGNATURES *, int);
int Search(SIGNATURES *, int, char *);
void Sort(SIGNATURES*, int);

int main(int argc, char *argv[]) {


    int TotalNumOfSignatures = 0, Position,FileExist;
    char sourceFileName[40]; //Assuming the given name are not more than 39 character


    if (argc < 2) {
        printf("No Given Arguments\n Please give the File name: ");
        gets(sourceFileName);
    }
    else {
        strcpy(sourceFileName, argv[1]); //Copying it to a variable which is more understandable
    }


    FileExist=1;
    //Check whether there is a file with given name
    while (FileExist) {

        FILE *Test = fopen(sourceFileName, "r");
        if (Test != NULL) {
            FileExist = 0;
            fclose(Test);
        } else {
            printf("This file does not exist, please enter again: ");
            fflush(stdin);
            gets( sourceFileName);
            fclose(Test);
        }
    }




    //Array Of Structure
    SIGNATURES *Table = Load_SignaturesTable(sourceFileName, &TotalNumOfSignatures);


    //This Function takes Our Structure Array and its Total Row size, then displays it.
    Display_SignaturesTable(Table, TotalNumOfSignatures);
    int choice = 0;



    while (choice != 3) {

        printf("\n\nTo search for a signature, please press 1\n");
        printf("To sort signatures based on width or height, please press 2\n");
        printf("To exit, please press 3\n");
        printf("Your choice:"); //Getting Users Choice
        scanf("%d", &choice);
        fflush(stdin);


        if (choice == 1) {

            int ValidName = 1;

            //This while loop starts with 1 (True Condition). When Search function gets a Valid Name which matches with Name of the signature owner, it becomes 0 (false condition) so that we don't need to get the TargetFullName again.
            while(ValidName) {
                char TargetFullName[40];
                printf("\nEnter the name of the signature owner:");
                gets(TargetFullName);

                //Position function takes our Table and its size, and Targer name. Then, searches for given target name whether it exists or not. If it exists, it returns its index as an integer. If it does not exist, it returns -1 as an integer.
                Position = Search(Table, TotalNumOfSignatures, TargetFullName);


                //Printing Details.
                if (Position != -1) {
                    printf("\n%s start signing at x=%.0f and y=%.0f and finalized at x=%.0f and y=%.0f. Hence, %s has a signature of width %.0f and height %.0f.",
                           Table[Position].full_name, Table[Position].x_initial, Table[Position].y_initial,
                           Table[Position].x_final, Table[Position].y_final, Table[Position].full_name,
                           Table[Position].width, Table[Position].height);
                    ValidName = 0;

                } else {
                    printf("That owner does not exist! Please try again!");
                }
            }

        }

        if (choice == 2) {

            //This Function Takes our Structure Array and its size in order to sort it with respect to user's choice.
            Sort(Table, TotalNumOfSignatures);

            //This Function Takes our  Structure Array and its size in order to display it.
            Display_SignaturesTable(Table, TotalNumOfSignatures);




        }

    }



    free(Table);
    return 0;
}

//This Function Takes the File's Name and an integer address which is called TotalNumOfSignatures in main function.
SIGNATURES *Load_SignaturesTable(char *Name, int *Size) {
    int count = 0; //This integer will be used for count the size of the Signatures.


    FILE *SourceFile; //Declearing Stream
    SourceFile = fopen(Name, "r"); //Opening
    if (SourceFile == NULL) {
        printf("Could not open the file.");
        exit(1);
    }

    char c;
    //This loop will be true untill it reads the End Of The File
    while ((c = fgetc(SourceFile)) != EOF) {
        if (c == '\n') // if the character is a "new line", this means we got one signature, so count should be incremented by 1
            count++;

    }
    count++; // This is for the last line



    *Size = count; // count will be assigned to the variable which "Size" points to;
    rewind(SourceFile);

    // Creating an Structure array
    SIGNATURES *SignaturesTable;

    // SignaturesTable Memory Allocation
    SignaturesTable = (SIGNATURES *) malloc(sizeof(SIGNATURES) * count);
    if (SignaturesTable == NULL) {
        printf("Failed to allocate memory.");
        exit(1);
    }

    int i = 0;
    char line[150];

    //Getting Line By Line the Data
    while (fgets(line, 150, SourceFile)) {
        char *token;
        int flag = 0;
        //Assigning our structure arrays elements
        token = strtok(line, ";");
        while (token != NULL) {
            if (flag == 0)
                strcpy(SignaturesTable[i].full_name, token);
            else if (flag == 1)
                SignaturesTable[i].x_initial = atoi(token);
            else if (flag == 2)
                SignaturesTable[i].x_final = atoi(token);
            else if (flag == 3)
                SignaturesTable[i].y_initial = atoi(token);
            else if (flag == 4) {
                // Deleting the '\n' character at the end of the token
                if (token[strlen(token) - 1] == '\n')
                    token[strlen(token) - 1] = '\0';
                SignaturesTable[i].y_final = atoi(token);
            }

            token = strtok(NULL, ";");
            flag++;
        }
        i++;
    }

    //Calculating the Width and Height of each person.
    for (int j = 1; j < count; ++j) {
        SignaturesTable[j].width = SignaturesTable[j].x_final - SignaturesTable[j].x_initial;
        SignaturesTable[j].height = SignaturesTable[j].y_final - SignaturesTable[j].y_initial;
    }

    //Closing the stream
    fclose(SourceFile);
    return SignaturesTable;
}


//This function takes the array of structure from the main function and its size, then displays it.
void Display_SignaturesTable(SIGNATURES *inTable, int Size) {

    if (inTable == NULL || Size == 0) {
        printf("The table has not been loaded\n");
        exit(1);
    }
    else {
        printf("The signature records file (signatures.txt) has been successfully loaded!\n The following records have been loaded:\n\n");
    }



    char *Title[7] = {"full name", "x_initial", "x_final", "y_initial", "y_final", "width", "height"};

    //Printing the titles of properties.
    for(int j = 0; j<7; j++) {
        printf("%-17s", Title[j]);
    }
    printf("\n");

    //Printing details of each individual.
    for (int i = 1; i < Size; i++) {

        printf("%-17s", inTable[i].full_name);
        printf("%-17.0f", inTable[i].x_initial);
        printf("%-17.0f", inTable[i].x_final);
        printf("%-17.0f", inTable[i].y_initial);
        printf("%-17.0f", inTable[i].y_final);
        printf("%-17.0f", inTable[i].width);
        printf("%-17.0f", inTable[i].height);
        printf("\n");
    }

}


// This Function takes an array of structure, its size, and a target name. Then search for target name whether it exists or does not exist.
int Search(SIGNATURES *Table, int Size, char *searchName) {

    for (int i = 0; i < Size; i++) {
        if (strstr(Table[i].full_name, searchName) != NULL) {
            return i;
        }
    }
    return -1;
}

//This function takes the array of structure and its size from the main function in order to sort the elements with respect to their width or height
void Sort(SIGNATURES *Table, int Size) {

    char Option;
    printf("\nSort by (w: width, h: height):");
    fflush(stdin);
    scanf("%c", &Option); //getting users choice
    fflush(stdin);


    // If user inputs w to sort them with respect to their Width, this condition turns 1.
    if(Option == 'w') {
        //BubbleSort algorithm to sort
        //a temporary structure called temp.
        SIGNATURES temp;

        for (int i = 0; i < Size - 1; i++) {
            //we set j to 1 because the first individual's index is 1.
            for (int j = 1; j < Size - i - 1; j++) {
                if (Table[j].width < Table[j + 1].width) {
                    temp = Table[j];
                    Table[j] = Table[j + 1];
                    Table[j + 1] = temp;
                }
            }
        }
    }

    // If user inputs h to sort them with respect to their height, this condition turns 1.
    if(Option == 'h') {


        SIGNATURES temp;

        for (int i = 0; i < Size-1; i++) {
            for (int j = 1; j < Size - i - 1; j++) {
                if (Table[j].height < Table[j + 1].height) {
                    temp = Table[j];
                    Table[j] = Table[j + 1];
                    Table[j + 1] = temp;
                }
            }
        }
    }
}
