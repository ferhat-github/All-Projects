//FerhatKasimKoc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"



int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("You entered less arguments than expected!");
        exit(1);
    }

    char *fileName = argv[1];

    // Check if the file exists
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File '%s' does not exist!!\n", fileName);
        exit(1);
    }
    fclose(file);

    struct SpeciesWeightTree *myTree = readData(fileName);


    printf("********Welcome to Fishdom Analysis********");


    int Command;
    do{
        printf("\n*******************************************");
        printf("\nMENU\n");
        printf("1. Display the full index of fishdom\n"
               "2. Display the heaviest fishes\n"
               "3. Display the longest fishes\n"
               "4. Exit\n"
               "*******************************************\n"
               "Enter your option: ");

        fflush(stdin);
        scanf("%d", &Command);
        printf("\n");

        if (Command == 1) {
            displayIndex(myTree);
        }
        else if (Command == 2) {
            heaviestFish(myTree);
        }
        else if (Command == 3) {
            longestFish(myTree);
        }
        else if (Command == 4) {
            printf("\n\nBye!\n");
            MakeEmptyTree(myTree);   // Cleaning the memory
        }
        else {
            printf("\n\nInvalid option! Please enter a valid option.\n");
        }
    } while (Command != 4);





    return 0;
}

struct SpeciesWeightTree* readData(char* fileName) {

    FILE *SourceFile; //Stream Declaration
    SourceFile = fopen(fileName, "r"); //Opening in reading mode
    if (SourceFile == NULL) {
        printf("Could not open the file.");
        exit(1);
    }

    //Counting lines of the provided file
    int SizeOfFile = 0;
    char tmp1;
    while ((tmp1 = fgetc(SourceFile)) != EOF) {
        if (tmp1 == '\n') {
            SizeOfFile++;
        }
    }
    //SizeOfFile++; //for last line(since last line does not have '\n')

    //NOTE! I did not add +1 to SizeOfFile for last line because I already consider the first line which is just an info line.


    rewind(SourceFile);

    char tmp2;
    while ((tmp2 = fgetc(SourceFile)) != '\n') {
        //Skip the first line
    }



    struct SpeciesWeightTree* myTree = CreateTree();


    for (int i = 0; i < SizeOfFile; ++i) {

        char c;
        char name[70], date[20], city[70];
        float weight, length;
        int index = 0;


        while (fscanf(SourceFile, "%c", &c) == 1 && c != ',') {
            name[index] = c;
            index++;
        }
        name[index] = '\0';
        index = 0;


        fscanf(SourceFile, "%f,%f,", &weight, &length);

        //Reading two remaining data which are fishingDate and City
        for (int j = 0; j < 2; ++j) {

            if(j == 0) {
                while (fscanf(SourceFile, "%c", &c) == 1 && c != ',' && c != '\n') {
                    if(c != ' ') {
                        date[index] = c;
                        index++;
                    }
                }
                date[index] = '\0';
                index = 0;
            }
            else {
                while (fscanf(SourceFile, "%c", &c) == 1 && c != ',' && c != '\n') {
                    if(c != ' ') {
                        city[index] = c;
                        index++;
                    }
                }
                city[index] = '\0';
                index = 0;
            }
        }


        myTree = insertFish(myTree, name, weight, length, date, city);


    }
    fclose(SourceFile);

    return myTree;
}



struct SpeciesWeightTree* insertFish(struct SpeciesWeightTree* t, char* Name, float Weight, float Length, char* Date, char* City) {

    if (t == NULL) {
        /*Create and return a one-node tree */
        t = malloc(sizeof(struct SpeciesWeightTree));
        if (t == NULL) {
            printf("Out of memory space!!!\n");
        }
        else {
             struct SpeciesDetails* DetailsNode = (struct SpeciesDetails*) malloc(sizeof(struct SpeciesDetails));
             if(DetailsNode == NULL) {
                 printf("Out of memory space!!!\n");
             }
             else {
                 t->Weight = Weight;
                 t->RightChild = NULL;
                 t->LeftChild = NULL;
                 t->Height = 0;
                 t->Details = DetailsNode;

                 strcpy(DetailsNode->SpeciesName, Name);
                 DetailsNode->FishLength = Length;
                 strcpy(DetailsNode->FishingDate, Date);
                 strcpy(DetailsNode->City, City);
                 DetailsNode->Next = NULL;
             }
        }
    }
    else if (Weight<t->Weight) {
        t->LeftChild = insertFish(t->LeftChild, Name, Weight, Length, Date, City);

        if (AVLTreeHeight(t->LeftChild) - AVLTreeHeight(t->RightChild) == 2) {
            if (Weight < t->LeftChild->Weight) {
                t = SingleRotateWithRight(t);
            }
            else {
                t = DoubleRotateWithRight(t);
            }
        }
    }
    else if (Weight > t->Weight) {
        t->RightChild = insertFish(t->RightChild, Name, Weight, Length, Date, City);;

        if (AVLTreeHeight(t->RightChild) - AVLTreeHeight(t->LeftChild) == 2) {
            if (Weight > t->RightChild->Weight) {
                t = SingleRotateWithLeft(t);
            } else {
                t = DoubleRotateWithLeft(t);
            }
        }
    }
    //else means the given weight already exists, so we do not need to create a new weight node.
    //Instead we should create a details node to store details of given fish.
    else {
        struct SpeciesDetails* newDetailsNode = (struct SpeciesDetails*)malloc(sizeof(struct SpeciesDetails));
        if (newDetailsNode == NULL) {
            printf("Out of memory space!!!\n");
        }
        else {

            struct SpeciesDetails* temp = t->Details;
            while (temp->Next != NULL) {
                temp = temp->Next;
            }

            strcpy(newDetailsNode->SpeciesName, Name);
            newDetailsNode->FishLength = Length;
            strcpy(newDetailsNode->FishingDate, Date);
            strcpy(newDetailsNode->City, City);
            temp->Next = newDetailsNode;
            newDetailsNode->Next = NULL;
        }

    }
    t->Height = Max(AVLTreeHeight(t->LeftChild), AVLTreeHeight(t->RightChild)) + 1;

    return t;
}






void displayIndex(struct SpeciesWeightTree* myTree) {
    if (myTree != NULL) {
        displayIndex(myTree->LeftChild);

        struct SpeciesDetails* details = myTree->Details;
        while (details != NULL) {
            printf("%s,%.0f,%.1f,%s,%s\n", details->SpeciesName, myTree->Weight, details->FishLength, details->FishingDate, details->City);
            details = details->Next;
        }

        displayIndex(myTree->RightChild);
    }
}




// My heaviestFish function's complexity is O(n) since it will traverse the rightmost node of the tree iteratively.
// But there is a more efficient way which is finding the rightmost node recursively and therefore time complexity will be O(log n);
void heaviestFish(struct SpeciesWeightTree* myTree) {
    if (myTree == NULL) {
        printf("The given tree is empty!\n");
        return;
    }

    // A Traverser
    struct SpeciesWeightTree* current = myTree;

    // Finding the rightmost node of the tree which is the heaviest one.
    while (current->RightChild != NULL) {
        current = current->RightChild;
    }


    struct SpeciesDetails* details = current->Details;
    while (details != NULL) {
        printf("%s,%.0f,%.1f,%s,%s\n", details->SpeciesName, current->Weight, details->FishLength, details->FishingDate, details->City);
        details = details->Next;
    }

}


// Time complexity of this function is  O(nlogn) where n is the number of nodes of our tree.
// The reason is that the function calls findLongestFishNode and that findLongestFishNode function traverses each node recursively O(logn), and traverses each details node of tree iteratively O(n).
// So time complexity is O(nlogn)
// It seems the most efficient way to find the longest fish and its data is this way where time complexity is O(nlogn).
void longestFish(struct SpeciesWeightTree* myTree) {
    if (myTree == NULL) {
        printf("The given tree is empty!\n");
        return;
    }

    struct SpeciesDetails* longestFishDetails = NULL;
    float longestFishWeight;
    findLongestFishNode(myTree, &longestFishDetails, &longestFishWeight);

    if (longestFishDetails != NULL) {
        printf("%s,%.0f,%.1f,%s,%s\n", longestFishDetails->SpeciesName, longestFishWeight, longestFishDetails->FishLength, longestFishDetails->FishingDate, longestFishDetails->City);
    } else {
        printf("No fish details available.\n");
    }
}

void findLongestFishNode(struct SpeciesWeightTree* tree, struct SpeciesDetails** longestFishDetails, float* longestFishWeight) {
    if (tree != NULL) {

        findLongestFishNode(tree->LeftChild, longestFishDetails, longestFishWeight);

        struct SpeciesDetails* details = tree->Details;
        while (details != NULL) {
            if (*longestFishDetails == NULL || details->FishLength > (*longestFishDetails)->FishLength) {
                *longestFishDetails = details;
                *longestFishWeight = tree->Weight;
            }
            details = details->Next;
        }

        findLongestFishNode(tree->RightChild, longestFishDetails, longestFishWeight);
    }
}






