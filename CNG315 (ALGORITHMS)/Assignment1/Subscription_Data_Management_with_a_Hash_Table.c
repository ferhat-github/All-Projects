//FerhatKasimKOC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 100
#define MAX_SERVICE_NAME_LENGTH 50
#define MAX_COUNTRY_LENGTH 50


typedef struct {
    int subscriptionID;
    char serviceName[50];
    float serviceCharge;
    int devicesRegistered;
    char startDate[11];
    char endDate[11];
    char status[10];
    char country[MAX_COUNTRY_LENGTH];
} Subscription;


typedef struct {
    char name[MAX_NAME_LENGTH];
    int subscriptionCount;
    float subscriptionCostTotal;
    Subscription *subscriptions;
    int subscriptionCapacity;
} Customer;



void menu();
void printCustomers(Customer *customers, int no_of_customers);
int countCustomers(FILE *inFile);
void readSubscriptions(FILE *inFile, Customer *customers, int no_of_customers);
Customer* createHashTable(int hashTableSize);
Customer* addCustomer(Customer *hashTable, Customer addedCustomer, int *hashTableSize, int criteria);
Customer* rehash(Customer *hashTable, int *hashTableSize, int criteria);
void printTable(Customer *hashTable, int hashTableSize);
void searchTable(Customer *hashTable, int hashTableSize, char searchName[], int criteria);

int main() {

    FILE *inFile;
    int no_of_customers = 0;
    Customer *customers;
    Customer *hashTable;

    inFile = fopen("subscriptions.txt", "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }
    no_of_customers = countCustomers(inFile);
    printf("There are %d unique customers\n", no_of_customers);

    customers = (Customer*) malloc(no_of_customers * sizeof(Customer));
    fclose(inFile);
    inFile = fopen("subscriptions.txt", "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }

    readSubscriptions(inFile, customers, no_of_customers);
    if (customers == NULL) {
        printf("\nCustomers have NOT been read successfully!\n");
        exit(1);
    }
    printCustomers(customers, no_of_customers);

    int hashTableSize = 11;
    char criteria;

    hashTable = createHashTable(hashTableSize);

    printf("Enter your hashing criteria: ");
    printf("1. Linear Probing 2. Quadratic Probing  3. Double Hashing\n");
    fflush(stdin);
    scanf("%c", &criteria);

    while (criteria != '1' && criteria != '2' && criteria != '3'){
        printf("Error! Please enter a valid hashing criteria: ");
        fflush(stdin);
        scanf("%c", &criteria);
    }
    fflush(stdin);

    int i;
    for (i = 0; i < no_of_customers; i++){
        hashTable = addCustomer(hashTable, customers[i], &hashTableSize, criteria - '0');
        printf("%s has been added to the table, the hash table now can be seen below:\n", customers[i].name);
        printTable(hashTable, hashTableSize);
        printf("\n");
    }

    char command = 0;
    int exit = 0;
    char searchName[81];
    while (exit != 1) {
        menu();
        printf("\nCommand: ");
        fflush(stdin);
        scanf("%c", &command);

        if (command == '1') {
            printf("Enter the customer's name: ");
            fflush(stdin);
            scanf("%s", searchName);
            searchTable(hashTable, hashTableSize, searchName, criteria - '0');
        }
        else if (command == '2'){
            printTable(hashTable, hashTableSize);
        }
        else if (command == '3'){
            exit = 1;
            printf("Goodbye!\n");
        }
        else{
            printf("Please enter a valid command!\n");
        }
    }



    free(customers);
    free(hashTable);

    return 0;
}

void menu () {
    printf("Please choose one of the following options:\n"
           "(1) Search a customer\n"
           "(2) Display hashtable\n"
           "(3) Exit\n");
}

void printCustomers(Customer* customers, int no_of_customers) {
    printf("List of customers:\n");
    int i, j;
    for (i = 0; i < no_of_customers; ++i) {
        // Print customer details
        if (customers[i].subscriptionCount > 0) {
            printf("Name: %s, number of subscriptions = %d, total amount paid for subscriptions = %.2f, "
                   "average amount paid per subscription = %.2f\n",
                   customers[i].name, customers[i].subscriptionCount,
                   customers[i].subscriptionCostTotal, customers[i].subscriptionCostTotal / customers[i].subscriptionCount);
        } else {
            printf("Name: %s, number of subscriptions = %d, total amount paid for subscriptions = %.2f, "
                   "average amount paid per subscription = N/A\n",
                   customers[i].name, customers[i].subscriptionCount, customers[i].subscriptionCostTotal);
        }
    }
}

int countCustomers(FILE *inFile) {

    //In subscriptions.txt file, I am assuming that there are no empty lines.
    //If there are 3 customers then the file should have 4 lines(1 for information order line, 3 for customers)
    //And also I am assuming that the last line does not have new line character(\n) so I am adding +1 manually.
    int lineCounting = 0;
    char tmpChar;
    while ((tmpChar = fgetc(inFile)) != EOF) {
        if (tmpChar == '\n') {
            lineCounting++;
        }
    }
    rewind(inFile);

    char temporary_line[256];
    //Just to move on next line because first line is just order information.
    fgets(temporary_line, sizeof(temporary_line), inFile);



    char** singleNamesArray;
    singleNamesArray = (char **)malloc(lineCounting * sizeof(char *));
    for (int i = 0; i < lineCounting; i++) {
        singleNamesArray[i] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
    }

    //Just to move on next line because first line is just order information.
    fgets(temporary_line, sizeof(temporary_line), inFile);


    int uniqueCounter = 0;
    int uniqueFlag;
    while(!feof(inFile)) {

        char c;
        char tmpNameString[MAX_NAME_LENGTH];
        int position = 0;
        //Reading first data of the line, which is name of the species, character by character until semicolon.
        while (fscanf(inFile, "%c", &c) == 1 && c != ';') {
            if(c != ' ') {
                tmpNameString[position] = c;
                position++;
            }
        }
        tmpNameString[position] = '\0';

        fgets(temporary_line, sizeof(temporary_line), inFile);


        uniqueFlag = 1;

        for (int i = 0; i < uniqueCounter; i++) {
            if (strcmp(singleNamesArray[i], tmpNameString) == 0) {
                uniqueFlag = 0; // Name already exists
                break;
            }
        }

        if (uniqueFlag) {
            strcpy(singleNamesArray[uniqueCounter], tmpNameString); // Add new unique name
            uniqueCounter++;
        }


    }



    // Free allocated memory for singleNamesArray
    for (int i = 0; i < lineCounting; i++) {
        free(singleNamesArray[i]);
    }
    free(singleNamesArray);

    rewind(inFile); // Reset file pointer to the beginning
    return uniqueCounter;

}



void readSubscriptions(FILE *inFile, Customer *customers, int no_of_customers) {

    char temporary_line[256];
    fgets(temporary_line, sizeof(temporary_line), inFile); // Skiping the information line which is line 1


    int customerPosition = 0;

    while (!feof(inFile)) {

        fgets(temporary_line, sizeof(temporary_line), inFile);
        char tmpNameString[MAX_NAME_LENGTH], tmpServiceName[MAX_SERVICE_NAME_LENGTH], tmpStartDate[11], tmpEndDate[11], tmpStatus[10], tmpCountry[MAX_COUNTRY_LENGTH];
        int tmpSubscriptionID, tmpDevicesRegistered;
        float tmpServiceCharge;



        sscanf(temporary_line, "%[^;];%d;%[^;];%f;%d;%[^;];%[^;];%[^;];%[^\n]", tmpNameString, &tmpSubscriptionID, tmpServiceName, &tmpServiceCharge, &tmpDevicesRegistered, tmpStartDate, tmpEndDate, tmpStatus, tmpCountry);

        int customerExistFlag = 0; //This will be used for checking whether the customer exist or not.
        int foundedCustomerIndex;
        //Finding the proper position
        for (int i = 0; i < customerPosition; i++) {
            if (strcmp(customers[i].name, tmpNameString) == 0) {
                customerExistFlag = 1;
                foundedCustomerIndex = i;
                break;
            }
        }

        if (customerExistFlag) {
            //If the customer exist, then we will update their properties.
            Customer *alreadyExistsCustomer = &customers[foundedCustomerIndex];
            alreadyExistsCustomer->subscriptionCount++;
            alreadyExistsCustomer->subscriptionCostTotal += tmpServiceCharge;


            //If customer's subscription size exceed or equal to customer's subscription capacity, then we will extend the subscription capacity by 1
            if (alreadyExistsCustomer->subscriptionCount >= alreadyExistsCustomer->subscriptionCapacity) {

                alreadyExistsCustomer->subscriptionCapacity += 1;
                alreadyExistsCustomer->subscriptions = (Subscription *)realloc(alreadyExistsCustomer->subscriptions, alreadyExistsCustomer->subscriptionCapacity * sizeof(Subscription));
            }


            Subscription *tmpSubscription = &alreadyExistsCustomer->subscriptions[alreadyExistsCustomer->subscriptionCount - 1];

            tmpSubscription->subscriptionID = tmpSubscriptionID;
            strcpy(tmpSubscription->serviceName, tmpServiceName);
            tmpSubscription->devicesRegistered = tmpDevicesRegistered;
            tmpSubscription->serviceCharge = tmpServiceCharge;


            strcpy(tmpSubscription->startDate, tmpStartDate);
            strcpy(tmpSubscription->endDate, tmpEndDate);
            strcpy(tmpSubscription->status, tmpStatus);
            strcpy(tmpSubscription->country, tmpCountry);

        }
        //If customer does not exist, this means we need to add a new one
        else {

            Customer *tmpCustomer = &customers[customerPosition];
            strcpy(tmpCustomer->name, tmpNameString);
            tmpCustomer->subscriptionCount = 1;
            tmpCustomer->subscriptionCostTotal = tmpServiceCharge;
            tmpCustomer->subscriptionCapacity = 2; //Initially it will be set to 2 (Assuming)


            tmpCustomer->subscriptions = (Subscription *)malloc(tmpCustomer->subscriptionCapacity * sizeof(Subscription));
            Subscription *tmpSubscription = &tmpCustomer->subscriptions[0];

            tmpSubscription->subscriptionID = tmpSubscriptionID;
            tmpSubscription->serviceCharge = tmpServiceCharge;
            tmpSubscription->devicesRegistered = tmpDevicesRegistered;


            strcpy(tmpSubscription->serviceName, tmpServiceName);
            strcpy(tmpSubscription->startDate, tmpStartDate);
            strcpy(tmpSubscription->endDate, tmpEndDate);
            strcpy(tmpSubscription->status, tmpStatus);
            strcpy(tmpSubscription->country, tmpCountry);


            customerPosition++;
        }
    }
}





Customer* createHashTable(int hashTableSize) {

    //This is for creating a new empty hash table with the given table size.
    Customer* hashedEmptyTable = (Customer*)malloc(hashTableSize * sizeof(Customer));
    if (hashedEmptyTable == NULL) {
        printf("Memory allocation failed for hash table.\n");
        exit(1);
    }

    //This is for initializing default values.
    for (int i = 0; i < hashTableSize; i++) {
        strcpy(hashedEmptyTable[i].name, "unassigned");
        hashedEmptyTable[i].subscriptionCount = 0;
        hashedEmptyTable[i].subscriptionCostTotal = 0;
        hashedEmptyTable[i].subscriptions = NULL;
        hashedEmptyTable[i].subscriptionCapacity = 0;
    }

    return hashedEmptyTable;
}


//This function is just add one customer to our hash table when it is called.
Customer* addCustomer(Customer *hashTable, Customer addedCustomer, int *hashTableSize, int criteria) {

    //This is for turning string key into numeric key as it is required in assignment.
    int hashingKeyValue = 0;
    for (int i = 0; i < strlen(addedCustomer.name); i++) {
        hashingKeyValue ^= (int)addedCustomer.name[i];
    }



    int tableSize = *hashTableSize;
    int position;
    //This for applying hashing mechanism with desired way.
    for (int i = 0; i < tableSize; i++) {
        //If criteria is 1, Linear probing will be applied.
        if (criteria == 1) {
            position = (hashingKeyValue + i) % tableSize;
        }
        //If criteria is 2, Quadratic probing will be applied.
        else if (criteria == 2) {
            position = (hashingKeyValue + i * i) % tableSize;
        }
        //If criteria is 3, DoubleHashing will be applied.
        else {
            int secondHashing = 7 - (hashingKeyValue % 7);
            position = (hashingKeyValue + i * secondHashing) % tableSize;
        }

        //If an empty place is found then we insert our customer to there.
        if (strcmp(hashTable[position].name, "unassigned") == 0) {
            hashTable[position] = addedCustomer;
            break;
        }
    }

    //After adding one customer to our hashtable we should check load factor.
    //Calculating customer size in our hash table.
    //Note: We are assuming that name "unassigned" indicates empty places so we are discarding them.
    int customerCounter = 0;
    for (int j = 0; j < tableSize; j++) {
        if (strcmp(hashTable[j].name, "unassigned") != 0) {
            customerCounter++;
        }
    }
    float loadFactor = (float)customerCounter / (float)tableSize;

    //Checking if rehashing is required
    if (loadFactor > 0.5) {
        hashTable = rehash(hashTable, hashTableSize, criteria);
    }

    return hashTable;
}



Customer* rehash(Customer *hashTable, int *hashTableSize, int criteria) {

    //Finding the new table size according to this logic;
    //Old table size should be multiplied by 2 and rounded to the next prime number.
    int updatedTableSize = *hashTableSize * 2;
    int primeFlag = 0;

    while (!primeFlag) {
        primeFlag = 1;
        for (int i = 2; i * i <= updatedTableSize; i++) {
            if (updatedTableSize % i == 0) {
                primeFlag = 0;
                updatedTableSize++;
                break;
            }
        }
    }


    //Creating the new has table with the calculated new size.
    Customer* newHashTable = createHashTable(updatedTableSize);

    // Rehashing the customers from the old hash table into the new hash table.
    for (int i = 0; i < *hashTableSize; i++) {


        if (strcmp(hashTable[i].name, "unassigned") != 0) {


            Customer tmpCustomer = hashTable[i];
            int hashingKeyValue = 0;
            for (int j = 0; j < strlen(tmpCustomer.name); j++) {
                hashingKeyValue ^= (int)tmpCustomer.name[j];
            }

            int position;
            for (int z = 0; z < updatedTableSize; z++) {
                //If criteria is 1, Linear probing will be applied.
                if (criteria == 1) {
                    position = (hashingKeyValue + z) % updatedTableSize;
                }
                //If criteria is 2, Quadratic probing will be applied.
                else if (criteria == 2) {
                    position = (hashingKeyValue + z * z) % updatedTableSize;
                }
                //If criteria is 3, DoubleHashing will be applied.
                else if (criteria == 3) {
                    int secondHashing = 7 - (hashingKeyValue % 7);
                    position = (hashingKeyValue + z * secondHashing) % updatedTableSize;
                }


                //If an empty place is found then we insert our customer to there.
                if (strcmp(newHashTable[position].name, "unassigned") == 0) {
                    newHashTable[position] = tmpCustomer;
                    break;
                }
            }
        }
    }


    free(hashTable);

    *hashTableSize = updatedTableSize;

    return newHashTable;
}



void printTable(Customer *hashTable, int hashTableSize) {

    //These are will be used just for printing the header line
    char indexHeader[6] = "Index";
    char nameHeader[5] = "Name";
    char totalSubscriptionHeader[20] = "Total Subscriptions";
    char totalCostHeader[10] = "TotalCost";
    printf("%-28s%-28s%-28s%-28s\n", indexHeader, nameHeader, totalSubscriptionHeader, totalCostHeader);


    for (int i = 0; i < hashTableSize; i++) {
        printf("%-28d", i);

        //For printing empty places
        if (strcmp(hashTable[i].name, "unassigned") == 0) {
            printf("\n");
        }
        //If it is not empty we will print each detail.
        else {
            // Filled slot: print customer details
            printf("%-28s%-28d%-28.2f\n",hashTable[i].name, hashTable[i].subscriptionCount, hashTable[i].subscriptionCostTotal);
        }
    }
}






void searchTable(Customer *hashTable, int hashTableSize, char searchName[], int criteria) {


    //This is for turning string hashingKeyValue into numeric hashingKeyValue as it is required in assignment.
    int hashingKeyValue = 0;
    for (int i = 0; i < strlen(searchName); i++) {
        hashingKeyValue ^= (int)searchName[i];
    }


    int foundSuccessfullyFlag = 0;

    int position;
    for (int i = 0; i < hashTableSize; i++) {
        if (criteria == 1) {
            position = (hashingKeyValue + i) % hashTableSize;
        }
        else if (criteria == 2) {
            position = (hashingKeyValue + i * i) % hashTableSize;
        }
        else if (criteria == 3) {
            int hash2 = 7 - (hashingKeyValue % 7);
            position = (hashingKeyValue + i * hash2) % hashTableSize;
        }


        if (strcmp(hashTable[position].name, searchName) == 0) {

            foundSuccessfullyFlag = 1;
            printf("Customer found: %s\n", hashTable[position].name);
            printf("More information about customer:\n");
            printf("Number of subscriptions: %d\n", hashTable[position].subscriptionCount);
            printf("Total cost: %.2f\n", hashTable[position].subscriptionCostTotal);

            //Printin all Subscription details of the relevant customer.
            printf("\nSubscriptions:\n");
            for (int j = 0; j < hashTable[position].subscriptionCount; j++) {
                Subscription tmpSubscription = hashTable[position].subscriptions[j];
                printf("Subscription %d:\n", j + 1);
                printf("Subscription ID: %d\n", tmpSubscription.subscriptionID);
                printf("Service Name: %s\n", tmpSubscription.serviceName);
                printf("Service Charge: %.2f\n", tmpSubscription.serviceCharge);
                printf("Devices Registered: %d\n", tmpSubscription.devicesRegistered);
                printf("Start Date: %s\n", tmpSubscription.startDate);
                printf("End Date: %s\n", tmpSubscription.endDate);
                printf("Status: %s\n", tmpSubscription.status);
                printf("\n");
            }
            break;
        }

        //If we reach an empty place, this means we don't have that customer in our table so we can end the loop.
        if (strcmp(hashTable[position].name, "unassigned") == 0) {
            break;
        }
    }

    if (!foundSuccessfullyFlag) {
        printf("Customer not found.\n");
    }
}

