//FerhatKasimKoc 2585164
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NumberOfLines 70

void displayMenu();
void getUserInput(char*);
int startQuiz(char**);
void loadQuestions(char**);
int askQuestion(char**, int);
void saveHighScores(int*, int, char**, char*, char, int);
void loadHighScores(int);
void viewHighScores(char**, int);


int main() {

    printf("Welcome to the C Programming Quiz Game!\n");
    displayMenu();


    char** QuestionArray;
    char** HighestScoresNames;
    int* HighScores;

    //Creating Arrays to store data
    QuestionArray = (char**) malloc(NumberOfLines*sizeof(char*));
    HighestScoresNames = (char**) malloc(5*sizeof(char*));
    HighScores = (int*) malloc(5*sizeof(int));

    if(QuestionArray==NULL || HighScores == NULL || HighestScoresNames == NULL){
        printf("Memory Allocation failed!");
        exit(1);
    }

    for (int i = 0; i <NumberOfLines; ++i) {
        QuestionArray[i] = (char*) malloc(100* sizeof(char)); //Assuming each line of file does not have more than 100 characters.
        HighestScoresNames[i] = (char*) malloc(100* sizeof(char));//Assuming each names does not have more than 100 characters
        if(QuestionArray[i]==NULL || HighestScoresNames[i]==NULL) {
            printf("Memory Allocation failed!");
            exit(1);
        }
    }


    //Fulling HighScores array with negative values. This will help us to make new scores bigger than these "-1" values so that we can assign them.
    for (int i = 0; i < 5; ++i) {
        HighScores[i] = -1;
    }


    char MenuOption, NameOption, NameOfUser[100];
    int Score, ScoreSizeCounter=0;

    //Getting MenuOption from the user.
    getUserInput(&MenuOption);

    //As long as user does not input 3, this loop will be executed.
    while(MenuOption != '3') {

        if(MenuOption == '1') {

            Score = startQuiz(QuestionArray);

            printf("\n\nDo you want to save your score? (Y/N): ");
            getUserInput(&NameOption);
            while(toupper(NameOption) != 'Y' && toupper(NameOption) != 'N') {
                printf("\nWrong Option! Please Enter again: ");
                getUserInput(&NameOption);

            }
            if(toupper(NameOption) == 'Y') {

                printf("\nEnter your name: ");
                scanf("%s", NameOfUser);

                //With the help of this counter, we will be able to determine if there are 5 elements or fewer.
                if(ScoreSizeCounter<5) {
                    saveHighScores(HighScores, Score, HighestScoresNames, NameOfUser, MenuOption, ScoreSizeCounter);
                    ++ScoreSizeCounter;
                }
                else{
                    int flag=0;
                    for (int i = 0; i < 5; ++i) {
                        if(Score > HighScores[i]){
                            flag = 1;
                        }
                    }
                    if(flag == 1) {
                        saveHighScores(HighScores, Score, HighestScoresNames, NameOfUser, MenuOption, ScoreSizeCounter);
                    }
                }
            }
        }
        else if(MenuOption == '2') {

            saveHighScores(HighScores, Score, HighestScoresNames, NameOfUser, MenuOption, ScoreSizeCounter);
            loadHighScores(ScoreSizeCounter);

        }
        else {
            printf("\nWrong option. Please enter again:\n\n");
        }

        displayMenu();
        getUserInput(&MenuOption);

    }
    printf("\n\nGoodbye!");


    for (int i = 0; i < NumberOfLines; ++i) {
        free(QuestionArray[i]);
        if(i<5) {
            free(HighestScoresNames[i]);
        }
    }


    free(QuestionArray);
    free(HighestScoresNames);
    free(HighScores);

    return 0;
}

void displayMenu() {
    printf("\nMenu:\n1. Start Quiz\n2. View High Scores\n3. Quit\n\nEnter your choice: ");
}

void getUserInput(char* Input) {

    char SelectedChoice;

    fflush(stdin);
    scanf("%c", &SelectedChoice);
    fflush(stdin);
    *Input = SelectedChoice;

}

int startQuiz(char** DataArray) {

    printf("Loading quiz questions...");
    loadQuestions(DataArray);

    int QuestionNum, UserScore=0;
    for (QuestionNum = 1; QuestionNum <= 10 ; ++QuestionNum) {
        UserScore += askQuestion(DataArray, QuestionNum);
    }

    printf("\nYou completed the quiz! Your score %d/10", UserScore);

    return UserScore;
}


void loadQuestions(char** DataArray){

    FILE *DATA;

    DATA = fopen("questions.txt","r");
    if(DATA==NULL){
        printf("Cannot open file!");
        exit(1);
    }

    //Reading the file and copying it to the array.
    int i=0;
    while(fgets(DataArray[i],100,DATA) != NULL){
        i++;
    }

    fclose(DATA);
}


int askQuestion(char** Questions, int QuestionNumber) {

    int StartingIndex = (QuestionNumber - 1) * 7; //This StartingIndex variable is the offset of first question and will be used for calculating other questions starting offset.
    int DestinationIndex = StartingIndex + 5; //This DestinationIndex variable is the offset of first question's correct answer and will be used for calculating other questions' correct answer offset.

    printf("\n");

    //Processing question by question
    for(StartingIndex; StartingIndex<DestinationIndex; ++StartingIndex) {
        for (int i = 0; Questions[StartingIndex][i] != '\0' ; ++i) {
            if(Questions[StartingIndex][i] == ':') {//printing question number before the ':'
                printf(" %d%c", QuestionNumber, Questions[StartingIndex][i]);
            }
            else {
                printf("%c", Questions[StartingIndex][i]);
            }
        }
    }

    char UserAnswer;
    int score=0;

    printf("Your Answer: ");
    getUserInput(&UserAnswer);
    while(toupper(UserAnswer) != 'A' && toupper(UserAnswer) != 'B' && toupper(UserAnswer) != 'C' && toupper(UserAnswer) != 'D') {
        printf("\nOption \"%c\" is not exist please enter A, B, C or D: ", UserAnswer);
        getUserInput(&UserAnswer);
    }


    char CorrectAnswer;
    int last_character_index =  strlen(Questions[DestinationIndex]) - 2; //finding correct answer's index of question

    CorrectAnswer = Questions[DestinationIndex][last_character_index];

    if(toupper(UserAnswer) == CorrectAnswer) {
        printf("\nCorrect!");
        score += 1;
    }
    else {
        printf("\nFalse!");
    }

    return score;
}


void saveHighScores(int* ScoreArray, int ScorePassed, char** NameArray, char* NamePassed, char StepActivator, int Size) {


    //With the help of this Step Activator variable, we can determine whether we need to sort passed Score or write to a file
    if(StepActivator == '1') {
        int i;
        //Sorting
        for (i = 4; i >= 0; i--) {
            if (ScorePassed > ScoreArray[i]) {
                if (i != 4) {
                    ScoreArray[i + 1] = ScoreArray[i];
                    strcpy(NameArray[i + 1], NameArray[i]);
                }
            }
            else {
                break;
            }
        }
        ScoreArray[i + 1] = ScorePassed;
        strcpy(NameArray[i + 1], NamePassed);

    }

        //If StepActivator is not '1', which means it is '2' and user wants to see Top 5 High Score, this part will be executed.
    else{

        FILE *HighScoresFiles;

        HighScoresFiles = fopen("HighScores.txt","w");
        if(HighScoresFiles==NULL){
            printf("\nCannot open file!");
            exit(1);
        }

        for (int i = 0; i < Size; ++i) {

            fprintf(HighScoresFiles, "%s - %d/10\n", NameArray[i], ScoreArray[i]);
        }

        fclose(HighScoresFiles);

    }

}

void loadHighScores(int Size) {

    FILE *HighScoresFile;
    HighScoresFile = fopen("HighScores.txt","r");
    if(HighScoresFile==NULL){
        printf("\nCannot open file!");
        exit(1);
    }

    char** HighestNamesArray;
    HighestNamesArray = (char**)malloc(Size*(sizeof(char*)));
    if(HighestNamesArray == NULL) {
        printf("\nAllocation Failed!");
        exit(1);
    }
    for (int i = 0; i < Size; ++i) {
        HighestNamesArray[i] = (char*) malloc(70*sizeof(char));
        if(HighestNamesArray[i] == NULL) {
            printf("\nAllocation Failed!");
            exit(1);
        }
    }


    for (int i = 0; i < Size; ++i) {
        fgets(HighestNamesArray[i], 70, HighScoresFile);
    }

    viewHighScores(HighestNamesArray, Size);


    for (int i = 0; i < Size; ++i) {
        free(HighestNamesArray[i]);
    }
    free(HighestNamesArray);

    fclose(HighScoresFile);
}

void viewHighScores(char** PassedArray, int Size) {

    printf("\n\nTop %d High Scores:\n", Size);
    for (int i = 0; i < Size; ++i) {
        printf("%d. %s", i+1, PassedArray[i]);
    }
}
