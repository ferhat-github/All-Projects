//FerhatKasimKoc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SpeciesDetails{
    float Weight;
    float VerticalLength;
    float DiagonalLength;
    float CrossLength;
    float Height;
    float FishLength;
    char FishingDate[70];
    char City[70];
    struct SpeciesDetails *Next;
};


struct SpeciesNameList {
    char SpeciesName[70];
    struct SpeciesDetails *Details;
    struct SpeciesNameList *Next;
};

struct ListRecord
{
    struct SpeciesNameList* head;
    struct SpeciesNameList* tail;
    int size;
};


struct ListRecord* initializeFishing(const char[]);
void MakeEmptyList(struct ListRecord*);
void addFishData(struct ListRecord*);
void printStatistic(struct ListRecord*);
void addSpeciesList(struct ListRecord*);
void saveUpdatedList(struct ListRecord*);
void searchFishData(struct  ListRecord*);
void deleteFish(struct ListRecord*, float);


int main() {

    struct ListRecord* List;

    List = initializeFishing("fishingArchive.txt");

    printf("The fishingArchive.txt file has been loaded successfully!");


    int Command;
    do{
        printf("\n\n-----MENU---------------------------------------\n");
        printf("1. Add Fish Data\n"
               "2. Delete Fish Data\n"
               "3. Print Fish Statistics\n"
               "4. Search Fish Data\n"
               "5. Add Species List\n"
               "6. Exit\n");

        printf("Enter your option: ");
        scanf("%d", &Command);

        if(Command == 1) {
            addFishData(List);
        }
        else if(Command == 2){
            float tresHold;
            printf("\nProvide fish weight threshold in grams: ");
            scanf("%f", &tresHold);
            deleteFish(List, tresHold);
        }
        else if(Command == 3) {
            printStatistic(List);
        }
        else if(Command == 4) {
            searchFishData(List);
        }
        else if(Command == 5) {
            addSpeciesList(List);
        }
        else{
            saveUpdatedList(List);
            printf("\n\nThe FishingArchive.txt file has been updated successfully!!");
        }
    }while(Command != 6);


    return 0;
}


struct ListRecord* initializeFishing(const char nameOfFile[]) {

    //Creating a DummyNode
    struct ListRecord* L;
    L = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (L == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }
    else {
        MakeEmptyList(L);
    }

    FILE *SourceFile; //Stream Declaration
    SourceFile = fopen(nameOfFile, "r"); //Opening
    if (SourceFile == NULL) {
        printf("Could not open the file.");
        exit(1);
    }


    //Counting lines of the provided file
    int SizeOfFile = 0;
    char tmp;
    while ((tmp = fgetc(SourceFile)) != EOF) {
        if (tmp == '\n') {
            SizeOfFile++;
        }
    }
    SizeOfFile++;
    rewind(SourceFile); //Resets the cursor



    for (int i = 0; i < SizeOfFile; ++i) {

        //A temporary node for species list
        struct SpeciesNameList* TempSpeciesNameNode = (struct SpeciesNameList*) malloc(sizeof(struct SpeciesNameList));
        if(TempSpeciesNameNode == NULL) {
            printf("Out of memory!\n");
            exit(1);
        }

        char c;
        char tmpNameString[70];
        int index = 0;
        //Reading first data of the line, which is name of the species, character by character until semicolon.
        while (fscanf(SourceFile, "%c", &c) == 1 && c != ';') {
            if(c != ' ') {
                tmpNameString[index] = c;
                index++;
            }
        }
        tmpNameString[index] = '\0';
        index = 0;



        //A temporary node for species details.
        struct SpeciesDetails *TempDetailsNode = (struct SpeciesDetails *) malloc(sizeof(struct SpeciesDetails));
        if (TempDetailsNode == NULL) {
            printf("Out of memory!\n");
            exit(1);
        }

        //Reading numerical data
        fscanf(SourceFile, "%f;%f;%f;%f;%f;%f;", &TempDetailsNode->Weight, &TempDetailsNode->VerticalLength,
               &TempDetailsNode->DiagonalLength, &TempDetailsNode->CrossLength, &TempDetailsNode->Height,
               &TempDetailsNode->FishLength);

        //Reading two remaining data which are fishingDate and City
        for (int j = 0; j < 2; ++j) {

            char tmpString[70];

            while (fscanf(SourceFile, "%c", &c) == 1 && c != ';' && c != '\n') {
                if(c != ' ') {
                    tmpString[index] = c;
                    index++;
                }
            }
            tmpString[index] = '\0';
            index = 0;

            //If it is first iteration this means we are now reading FishingDate from the file.
            if (j == 0) {
                strcpy(TempDetailsNode->FishingDate, tmpString);
            } else {
                strcpy(TempDetailsNode->City, tmpString);
            }

        }


        TempSpeciesNameNode->Next = NULL;
        TempDetailsNode->Next = NULL;


        //If the list is empty these steps will be executed.
        if (L->size == 0) {
            strcpy(TempSpeciesNameNode->SpeciesName, tmpNameString);

            TempSpeciesNameNode->Details = TempDetailsNode;
            L->head->Next = TempSpeciesNameNode;
            L->tail = TempSpeciesNameNode;
            L->size++;

        }

            //If the list has at least one species, these steps will be executed.
        else {
            int SpecieExists = 0;
            struct SpeciesNameList* currentName = L->head->Next;

            //Determining whether there is the same species or not.
            while(currentName != NULL) {
                if (strcmp(currentName->SpeciesName, tmpNameString) != 0) {
                    currentName = currentName->Next;
                }
                else {
                    SpecieExists = 1;
                    break;
                }
            }

            //If there is the same species already then we will connect the new species' details to the previous one.
            if(SpecieExists) {

                struct SpeciesDetails* currentNameDetail = currentName->Details;

                while(currentNameDetail->Next != NULL) {
                    currentNameDetail = currentNameDetail->Next;
                }

                currentNameDetail->Next = TempDetailsNode;

            }
                //Adding new species to our species list.
            else {
                strcpy(TempSpeciesNameNode->SpeciesName, tmpNameString);

                TempSpeciesNameNode->Details = TempDetailsNode;
                L->tail->Next = TempSpeciesNameNode;
                L->tail = TempSpeciesNameNode;
                L->size++;

            }

        }

    }

    fclose(SourceFile);
    return L;
}

void MakeEmptyList(struct ListRecord* l) {

    //A dummy done
    l->head = (struct SpeciesNameList *) malloc(sizeof(struct SpeciesNameList));
    if (l->head == NULL) {
        printf("Out of memory!\n");
    }

    l->head->Next = NULL;
    l->tail = l->head;
    l->size = 0;

}


void addFishData(struct ListRecord* L) {

    char ExistsSpecieName[70];
    printf("\nSpecies: ");
    scanf("%s", ExistsSpecieName);

    int SpecieExists = 0;
    struct SpeciesNameList* targetName = L->head->Next;

    do {
        //Determining whether there is the same species or not.
        while (targetName != NULL) {
            if (strcmp(targetName->SpeciesName, ExistsSpecieName) != 0) {
                targetName = targetName->Next;
            }
            else {
                SpecieExists = 1;
                break;
            }
        }

        //being sure that user entered the species name that already exists as the function requires.
        if(SpecieExists == 0) {
            printf("\nThe specie that you have entered does not exist! Please enter again!");
            printf("\nSpecies: ");
            fflush(stdin);
            scanf("%s", ExistsSpecieName);
            targetName = L->head->Next;
        }

    }while(SpecieExists == 0);

    struct SpeciesDetails* targetNameDetails = targetName->Details;

    //Going the last node of the species' details.
    while(targetNameDetails->Next != NULL) {
        targetNameDetails = targetNameDetails->Next;
    }


    struct SpeciesDetails *TempDetailsNode = (struct SpeciesDetails *) malloc(sizeof(struct SpeciesDetails));
    if (TempDetailsNode == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    printf("\nWeight of the fish in grams: ");
    scanf("%f", &TempDetailsNode->Weight);
    printf("\nVertical length in CM: ");
    scanf("%f", &TempDetailsNode->VerticalLength);
    printf("\nDiagonal length in CM: ");
    scanf("%f", &TempDetailsNode->DiagonalLength);
    printf("\nCross length in CM: ");
    scanf("%f", &TempDetailsNode->CrossLength);
    printf("\nHeight in CM: ");
    scanf("%f", &TempDetailsNode->Height);
    printf("\nFish Length in CM: ");
    scanf("%f", &TempDetailsNode->FishLength);
    fflush(stdin);
    printf("\nFishing date: ");
    scanf("%s", TempDetailsNode->FishingDate);
    fflush(stdin);
    printf("\nCity: ");
    scanf("%s", TempDetailsNode->City);

    TempDetailsNode->Next = NULL;
    targetNameDetails->Next = TempDetailsNode;

    printf("\nThe data has been added, successfully!");
}


void printStatistic(struct ListRecord* L) {

    char ExistsSpecieName[70];
    printf("\nProvide the species: ");
    scanf("%s", ExistsSpecieName);

    int SpecieExists = 0;
    struct SpeciesNameList* targetName = L->head->Next;

    do {
        //Determining whether there is the same species or not.
        while (targetName != NULL) {
            if (strcmp(targetName->SpeciesName, ExistsSpecieName) != 0) {
                targetName = targetName->Next;
            } else {
                SpecieExists = 1;
                break;
            }
        }

        //being sure that user entered the species name that already exists as the function requires.
        if(SpecieExists == 0) {
            printf("\nThe specie that you have entered does not exist! Please enter again!");
            printf("\nProvide the species: ");
            fflush(stdin);
            scanf("%s", ExistsSpecieName);
            targetName = L->head->Next;
        }

    }while(SpecieExists == 0);

    //Counting process.
    struct SpeciesDetails* targetNameDetails = targetName->Details;
    int Counter = 0;
    while(targetNameDetails != NULL) {
        targetNameDetails = targetNameDetails->Next;
        Counter++;
    }

    printf("\nThe number of available fish data is %d", Counter);

}

void addSpeciesList(struct ListRecord* L) {

    char Command;
    do {

        char newSpeciesName[70];
        printf("\nThe new species is: ");
        scanf("%s", newSpeciesName);

        int SpecieExists;
        struct SpeciesNameList *currentSpecies = L->head->Next;

        do {
            //Determining whether there is the same species or not.
            SpecieExists = 0;
            while (currentSpecies != NULL) {
                if (strcmp(currentSpecies->SpeciesName, newSpeciesName) != 0) {
                    currentSpecies = currentSpecies->Next;
                } else {
                    SpecieExists = 1;
                    break;
                }
            }
            //being sure that user entered the species name that does not exist as the function requires.
            if (SpecieExists == 1) {
                printf("\nThe species that you have entered exists! Please enter again!");
                printf("\nThe new species is: ");
                fflush(stdin);
                scanf("%s", newSpeciesName);
                currentSpecies = L->head->Next;
            }

        } while (SpecieExists == 1);


        struct SpeciesNameList *TempSpeciesNameNode = (struct SpeciesNameList *) malloc(sizeof(struct SpeciesNameList));
        if (TempSpeciesNameNode == NULL) {
            printf("Out of memory!\n");
            exit(1);
        }
        strcpy(TempSpeciesNameNode->SpeciesName, newSpeciesName);
        TempSpeciesNameNode->Next = NULL;


        struct SpeciesDetails *TempDetailsNode = (struct SpeciesDetails *) malloc(sizeof(struct SpeciesDetails));
        if (TempDetailsNode == NULL) {
            printf("Out of memory!\n");
            exit(1);
        }

        printf("\nProvide the following info:");
        printf("\nWeight of the fish in grams: ");
        scanf("%f", &TempDetailsNode->Weight);
        printf("\nVertical length in CM: ");
        scanf("%f", &TempDetailsNode->VerticalLength);
        printf("\nDiagonal length in CM: ");
        scanf("%f", &TempDetailsNode->DiagonalLength);
        printf("\nCross length in CM: ");
        scanf("%f", &TempDetailsNode->CrossLength);
        printf("\nHeight in CM: ");
        scanf("%f", &TempDetailsNode->Height);
        printf("\nFish Length in CM: ");
        scanf("%f", &TempDetailsNode->FishLength);
        printf("\nFishing date: ");
        scanf("%s", TempDetailsNode->FishingDate);
        printf("\nCity: ");
        scanf("%s", TempDetailsNode->City);

        TempDetailsNode->Next = NULL;
        TempSpeciesNameNode->Details = TempDetailsNode;
        L->tail->Next = TempSpeciesNameNode;
        L->tail = TempSpeciesNameNode;
        L->size++;


        printf("\nDo you want to add more fish (Y/N)?");
        fflush(stdin);
        scanf("%c", &Command);

    }while(Command == 'Y');

}

void saveUpdatedList(struct ListRecord* L) {
    FILE *outputFile = fopen("fishingArchive.txt", "w"); // Declaring a stream

    if (outputFile == NULL) {
        printf("\nCould not open the file for writing.");
        exit(1);
    }

    struct SpeciesNameList* currentSpecies = L->head->Next;
    struct SpeciesDetails *currentDetails;
    struct SpeciesNameList* tempSpecies; //will be used for freeing memory.

    while (currentSpecies != NULL) {
        currentDetails = currentSpecies->Details;

        while (currentDetails != NULL) {
            fprintf(outputFile, "%s;%.0f;%.1f;%.1f;%.1f;%.4f;%.4f;%s;%s",
                    currentSpecies->SpeciesName, currentDetails->Weight,
                    currentDetails->VerticalLength, currentDetails->DiagonalLength,
                    currentDetails->CrossLength, currentDetails->Height,
                    currentDetails->FishLength, currentDetails->FishingDate,
                    currentDetails->City);

            if(currentSpecies->Next != NULL) {
                fprintf(outputFile,"\n");
            }

            struct SpeciesDetails* tempDetails = currentDetails;
            currentDetails = currentDetails->Next;
            free(tempDetails);
        }
        tempSpecies = currentSpecies;
        currentSpecies = currentSpecies->Next;
        free(tempSpecies);
    }
    free(L->head);

    fclose(outputFile);
}



void searchFishData(struct  ListRecord* L) {

    char Command;
    printf("\nEnter your search option (C for city/M for month):");
    fflush(stdin);
    scanf("%c", &Command);

    int targetMonths;
    char targetCity[70];
    int Flag = 0;

    struct SpeciesNameList* currentSpecies = L->head->Next;
    struct SpeciesDetails* currentSpeciesDetails;

    if(Command == 'M') {

        printf("\nEnter the month number: ");
        scanf("%d", &targetMonths);

        //Checking whether user entered the correct input or not.
        while(targetMonths < 0 || targetMonths > 12) {
            printf("\nYou entered the wrong number!!");
            printf("\nEnter the month number: ");
            scanf("%d", &targetMonths);
        }

        //Separating the fishing date to get the month
        int fishDateDay, fishDateMonth, fishDateYear;
        while (currentSpecies != NULL) {
            currentSpeciesDetails = currentSpecies->Details;

            while (currentSpeciesDetails != NULL) {
                sscanf(currentSpeciesDetails->FishingDate, "%d/%d/%d", &fishDateDay, &fishDateMonth, &fishDateYear);

                if (fishDateMonth == targetMonths) {
                    //Printing the fish data for the specified month
                    printf("\n%s;%.0f;%.1f;%.1f;%.1f;%.4f;%.4f;%s;%s",
                           currentSpecies->SpeciesName, currentSpeciesDetails->Weight,
                           currentSpeciesDetails->VerticalLength, currentSpeciesDetails->DiagonalLength,
                           currentSpeciesDetails->CrossLength, currentSpeciesDetails->Height,
                           currentSpeciesDetails->FishLength, currentSpeciesDetails->FishingDate,
                           currentSpeciesDetails->City);
                    Flag = 1;
                }

                currentSpeciesDetails = currentSpeciesDetails->Next;
            }

            currentSpecies = currentSpecies->Next;
        }
        if (Flag != 1) {
            printf("\nNo Species Found!");
        }
    }
    else if(Command == 'C') {

        printf("Enter the target city: ");
        scanf("%s", targetCity);

        while (currentSpecies != NULL) {
            currentSpeciesDetails = currentSpecies->Details;

            while (currentSpeciesDetails != NULL) {
                if (strcmp(targetCity, currentSpeciesDetails->City) == 0) {
                    printf("%s;%.0f;%.1f;%.1f;%.1f;%.4f;%.4f;%s;%s\n",
                           currentSpecies->SpeciesName, currentSpeciesDetails->Weight,
                           currentSpeciesDetails->VerticalLength, currentSpeciesDetails->DiagonalLength,
                           currentSpeciesDetails->CrossLength, currentSpeciesDetails->Height,
                           currentSpeciesDetails->FishLength, currentSpeciesDetails->FishingDate,
                           currentSpeciesDetails->City);
                    Flag = 1;
                }
                currentSpeciesDetails = currentSpeciesDetails->Next;
            }
            currentSpecies = currentSpecies->Next;
        }
        if (Flag != 1) {
            printf("\nNo species found!");
        }
    }
}



void deleteFish(struct ListRecord* L, float tresHold) {
    struct SpeciesNameList* currentSpecies = L->head->Next;
    struct SpeciesNameList* prevSpecies = L->head;
    int count = 0;

    while (currentSpecies != NULL) {
        struct SpeciesDetails* currentDetails = currentSpecies->Details;
        struct SpeciesDetails* prevDetails = NULL;

        while (currentDetails != NULL) {
            //Weight condition
            if (currentDetails->Weight < tresHold) {

                //If it is the first details of the species, these steps will be executed.
                if (prevDetails == NULL) {
                    currentSpecies->Details = currentDetails->Next;
                    free(currentDetails);
                    currentDetails = currentSpecies->Details;
                }
                else {
                    prevDetails->Next = currentDetails->Next;
                    free(currentDetails);
                    currentDetails = prevDetails->Next;
                }
                count++;
            }
            else {
                //If the species' weight is bigger than what the user entered, move to the next details.
                prevDetails = currentDetails;
                currentDetails = currentDetails->Next;
            }
        }

        //If the species has no fish left, delete the species itself
        if (currentSpecies->Details == NULL) {
            prevSpecies->Next = currentSpecies->Next;
            free(currentSpecies);
            currentSpecies = prevSpecies->Next;
            L->size--;
        }
        else {
            prevSpecies = currentSpecies;
            currentSpecies = currentSpecies->Next;
        }
    }

    printf("\n%d fish data was deleted from your list!", count);
}