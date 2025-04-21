#include <stdio.h>
#include "stdlib.h"
#include "string.h"


struct graphArc{
    int weight;
    struct graphVertex *destination;
    struct graphArc *next;
}Arc;


typedef struct graphVertex {
    struct graphVertex *next;
    char warehouseName[50];
    int inDegree;
    int outDegree;
    int processed;
    struct graphArc *firstArc;
} Vertex;


typedef struct graphHead {
    int count;
    struct graphVertex *first;
} Graph;

struct graphHead * createGraph(void);
void insertVertex(struct graphHead *head, char *data);
int insertArc(struct graphHead *head, char *fromKey, char *toKey ,int weight);
void printAllArcOfVertex(struct  graphVertex *graphVertexName);
void printAllVertex(struct graphHead *graphName);
void printAllVertexWithRoutes(struct graphHead *graphName);
void readRoutes(char *fileName,struct graphHead *warehouseGraph);
void readWarehouseNames(char *fileName, struct graphHead *warehouseGraph);
void getMostDeliveries(struct graphHead *warehouseGraph);
void sendMostDeliveries(struct graphHead *warehouseGraph);
void routesWithHighestDistance(struct graphHead *warehouseGraph);
void routesWithLowestDistance(struct graphHead *warehouseGraph);
int findPath(struct graphVertex *currentVertex, struct graphVertex *destinationVertex, int *totalDistance);
void checkDistance(struct graphHead *warehouseGraph, char *departure, char *destination);

int main (int argc, char *argv[]){
    struct graphHead *warehouseGraph = createGraph();

    readWarehouseNames("WarehouseLocations.txt", warehouseGraph);
    readRoutes("WarehouseRoutes.txt", warehouseGraph);

    printf("\nWarehouse and route data read successfully.\n");

    printf("\nRead warehouse locations:\n");
    printAllVertex(warehouseGraph);

    printf("\nRead routes:\n");
    printAllVertexWithRoutes(warehouseGraph);

    printf("\n");
    getMostDeliveries(warehouseGraph);

    printf("\n");
    sendMostDeliveries(warehouseGraph);

    printf("\n");
    routesWithHighestDistance(warehouseGraph);

    printf("\n");
    routesWithLowestDistance(warehouseGraph);

    printf("\n");
    if(argc > 1){
        checkDistance(warehouseGraph, argv[1], argv[2]);
    }
}

struct graphHead * createGraph(void){
    struct graphHead * head = (struct graphHead *)malloc(sizeof(struct graphHead));
    head->count = 0;
    head->first = NULL;
    return head;
}

void insertVertex(struct graphHead *head, char *data){
    struct graphVertex *vertex = (struct graphVertex *)malloc(sizeof(struct graphVertex));
    vertex->next = NULL;
    strcpy(vertex->warehouseName, data);
    vertex->inDegree = 0;
    vertex->outDegree = 0;
    vertex->firstArc = NULL;
    vertex->processed = 0;
    head->count += 1;
    if(head->first == NULL){
        head->first = vertex;
    }
    else{
        struct graphVertex *temp = head->first;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = vertex;
    }
}

int insertArc(struct graphHead *head, char *fromKey, char *toKey ,int weight){

    //Checking errors.
    if (head == NULL || fromKey == NULL || toKey == NULL) {
        printf("The parameters that you gave is not in desired format!\n");
        return 0;
    }



    //Finding the vertex that we will insert its adjacent
    struct graphVertex *tmp_From_Vertex = head->first; //Temporary pointer to traverse.
    while (tmp_From_Vertex != NULL && strcmp(tmp_From_Vertex->warehouseName, fromKey) != 0) {
        tmp_From_Vertex = tmp_From_Vertex->next;
    }
    //Finding the vertex that is adjacent of the from_Vertex.
    struct graphVertex *tmp_To_Vertex = head->first; //Temporary pointer to traverse.
    while (tmp_To_Vertex != NULL && strcmp(tmp_To_Vertex->warehouseName, toKey) != 0) {
        tmp_To_Vertex = tmp_To_Vertex->next;
    }

    //If at least one of them are not found then we will terminate the function.
    if (tmp_From_Vertex == NULL || tmp_To_Vertex == NULL) {
        printf("At least one of the Vertexes are not found!\n");
        return 0;
    }



    struct graphArc *tmp_ARC = (struct graphArc *)malloc(sizeof(struct graphArc));
    tmp_ARC->weight = weight;
    tmp_ARC->destination = tmp_To_Vertex;
    tmp_ARC->next = NULL;

    //Inserting the new arc to the end of the arc list.
    if (tmp_From_Vertex->firstArc == NULL) {
        tmp_From_Vertex->firstArc = tmp_ARC;
    }
    else {
        struct graphArc *tmp_Current = tmp_From_Vertex->firstArc;
        while (tmp_Current->next != NULL) {
            tmp_Current = tmp_Current->next;
        }
        tmp_Current->next = tmp_ARC;
    }

    tmp_From_Vertex->outDegree++;
    tmp_To_Vertex->inDegree++;

    return 1;

}

void printAllVertex(struct graphHead *graphName){

    if (graphName == NULL || graphName->first == NULL) {
        printf("There is no data to print!\n");
        return;
    }

    struct graphVertex *currentVertex = graphName->first;
    while (currentVertex != NULL) {
        printf("%s\n", currentVertex->warehouseName);
        currentVertex = currentVertex->next;
    }
}


void printAllArcOfVertex(struct  graphVertex *graphVertexName){

    if (graphVertexName == NULL) {
        printf("No verteks exist!\n");
        return;
    }

    struct graphArc *current = graphVertexName->firstArc;
    while (current != NULL) {
        printf(" -%d-> %s |", current->weight, current->destination->warehouseName);
        current = current->next;
    }

    printf("\n");
}

void printAllVertexWithRoutes(struct graphHead *graphName){

    if (graphName == NULL || graphName->first == NULL) {
        printf("There is No data to print.\n");
        return;
    }

    struct graphVertex *currentVertex = graphName->first;
    while (currentVertex != NULL) {
        if(currentVertex->outDegree > 0) {
            printf("%s |", currentVertex->warehouseName);
            printAllArcOfVertex(currentVertex);
        }
        currentVertex = currentVertex->next;

    }
}

void readWarehouseNames(char *fileName, struct graphHead *warehouseGraph){

    FILE *wareHouseSource = fopen(fileName, "r");


    if (wareHouseSource == NULL) {
        printf("The file %s cannot be opened!", fileName);
        return;
    }
    printf("%s has been opened successfully\n", fileName);


    while(!feof(wareHouseSource)) {
        //I am assuming that each name of a Warehouse is not longer than 99 character.
        char temporary_Warehouse[100];
        fscanf(wareHouseSource, "%s", temporary_Warehouse);
        insertVertex(warehouseGraph, temporary_Warehouse);
    }

    fclose(wareHouseSource);

}




void readRoutes(char *fileName,struct graphHead *warehouseGraph){

    FILE *routesSource = fopen(fileName, "r");

    if (routesSource == NULL) {
        printf("The routesSource %s cannot be opened!", fileName);
        return;

    }


    printf("%s has been opened successfully\n", fileName);

    //Assuming that there is no line in the routesSource that has character more than 1000.
    //If in the future there is, then this "line" array size should be updated by the user(the one which will use this code), to a suitable line size.
    char line[1000];
    while (fgets(line, sizeof(line), routesSource)) {

        char *fromVertex = strtok(line, ";");

        char *current = strtok(NULL, "");
        while (current && *current) {

            char *tmp_Distance = strtok(current, ";");
            char *tmp_ToVertex = strtok(NULL, ";" "\n");

            if (tmp_Distance && tmp_ToVertex) {
                int distance = atoi(tmp_Distance);
                insertArc(warehouseGraph, fromVertex, tmp_ToVertex, distance);
            }

            current = strtok(NULL, "");

        }
    }

    fclose(routesSource);
}

void getMostDeliveries(struct graphHead *warehouseGraph){

    if (warehouseGraph == NULL || warehouseGraph->first == NULL) {
        printf("There is no Data to process!\n");
        return;
    }

    int highest_Indegree_Value = 0;

    //This loop will be used to find the highest indegree value. We will use this value to print the vertexes that has this amount of indegree.
    struct graphVertex *tmp_VertexToTraverse = warehouseGraph->first;
    while (tmp_VertexToTraverse != NULL) {

        if (tmp_VertexToTraverse->inDegree > highest_Indegree_Value) {
            highest_Indegree_Value = tmp_VertexToTraverse->inDegree;
        }

        tmp_VertexToTraverse = tmp_VertexToTraverse->next;

    }

    //Printing the vertexes that have the highest indegree value.
    tmp_VertexToTraverse = warehouseGraph->first;
    printf("Warehouses that receive deliveries from the most different locations (%d):\n", highest_Indegree_Value);
    while (tmp_VertexToTraverse != NULL) {

        if (tmp_VertexToTraverse->inDegree == highest_Indegree_Value) {
            printf("- %s\n", tmp_VertexToTraverse->warehouseName);
        }

        tmp_VertexToTraverse = tmp_VertexToTraverse->next;

    }
}

void sendMostDeliveries(struct graphHead *warehouseGraph){

    if (warehouseGraph == NULL || warehouseGraph->first == NULL) {
        printf("There is no Data to process!\n");
        return;
    }

    int highest_Outdegree_Value = 0;

    //This loop will be used to find the highest outdegree value. We will use this value to print the vertexes that has this amount of outdegree.
    struct graphVertex *tmp_VertexToTraverse = warehouseGraph->first;
    while (tmp_VertexToTraverse != NULL) {

        if (tmp_VertexToTraverse->outDegree > highest_Outdegree_Value) {
            highest_Outdegree_Value = tmp_VertexToTraverse->outDegree;
        }

        tmp_VertexToTraverse = tmp_VertexToTraverse->next;

    }

    //Printing the vertexes that have the highest outdegree value.
    tmp_VertexToTraverse = warehouseGraph->first;
    printf("Warehouses that send deliveries to the most different locations (%d):\n", highest_Outdegree_Value);
    while (tmp_VertexToTraverse != NULL) {

        if (tmp_VertexToTraverse->outDegree == highest_Outdegree_Value) {
            printf("- %s\n", tmp_VertexToTraverse->warehouseName);
        }

        tmp_VertexToTraverse = tmp_VertexToTraverse->next;

    }
}

void routesWithHighestDistance(struct graphHead *warehouseGraph) {

    if (warehouseGraph == NULL || warehouseGraph->first == NULL) {
        printf("There is no Data to process!\n");
        return;
    }

    //Assuming that minimum distance is 0.
    int highest_Distance_Value = 0;

    //This loop will be used to find the highest distance value for all arcs. We will use this value to print the arcs that has this amount of distance.
    struct graphVertex *tmp_VertexToTraverse = warehouseGraph->first;
    while (tmp_VertexToTraverse != NULL) {

        struct graphArc *tmp_ARCtoTraverse = tmp_VertexToTraverse->firstArc;
        while (tmp_ARCtoTraverse != NULL) {

            if (tmp_ARCtoTraverse->weight > highest_Distance_Value) {
                highest_Distance_Value = tmp_ARCtoTraverse->weight;
            }

            tmp_ARCtoTraverse = tmp_ARCtoTraverse->next;

        }

        tmp_VertexToTraverse = tmp_VertexToTraverse->next;

    }


    printf("Routes with the highest distance (%d):\n", highest_Distance_Value);

    //Printing the arces that have the highest distance value.
    tmp_VertexToTraverse = warehouseGraph->first;
    while (tmp_VertexToTraverse != NULL) {

        struct graphArc *tmp_ARCtoTraverse = tmp_VertexToTraverse->firstArc;
        while (tmp_ARCtoTraverse != NULL) {

            if (tmp_ARCtoTraverse->weight == highest_Distance_Value) {
                printf("%s -%d-> %s\n",
                       tmp_VertexToTraverse->warehouseName,
                       tmp_ARCtoTraverse->weight,
                       tmp_ARCtoTraverse->destination->warehouseName);
            }

            tmp_ARCtoTraverse = tmp_ARCtoTraverse->next;

        }

        tmp_VertexToTraverse = tmp_VertexToTraverse->next;
    }
}

void routesWithLowestDistance(struct graphHead *warehouseGraph) {

    if (warehouseGraph == NULL || warehouseGraph->first == NULL) {
        printf("There is no Data to process!\n");
        return;
    }

    //Assuming that the highest distance can at most be the maximum integer value in C programming.
    int lowest_Distance_Value = INT_MAX;

    //This loop will be used to find the lowest distance value for all arcs. We will use this value to print the arcs that has this amount of distance.
    struct graphVertex *tmp_VertexToTraverse = warehouseGraph->first;
    while (tmp_VertexToTraverse != NULL) {

        struct graphArc *tmp_ARCtoTraverse = tmp_VertexToTraverse->firstArc;
        while (tmp_ARCtoTraverse != NULL) {

            if (tmp_ARCtoTraverse->weight < lowest_Distance_Value) {
                lowest_Distance_Value = tmp_ARCtoTraverse->weight;
            }

            tmp_ARCtoTraverse = tmp_ARCtoTraverse->next;

        }

        tmp_VertexToTraverse = tmp_VertexToTraverse->next;

    }


    printf("Routes with the smallest distance (%d):\n", lowest_Distance_Value);

    //Printing the arces that have the lowest distance value.
    //Note: We are know that according to given txt files, lowest distance is 5 from Guzelyurt to Kalkanli.
    //But if there is another path that has the same distance value, it will also be printed.
    tmp_VertexToTraverse = warehouseGraph->first;
    while (tmp_VertexToTraverse != NULL) {

        struct graphArc *tmp_ARCtoTraverse = tmp_VertexToTraverse->firstArc;
        while (tmp_ARCtoTraverse != NULL) {

            if (tmp_ARCtoTraverse->weight == lowest_Distance_Value) {
                printf("%s -%d-> %s\n",
                       tmp_VertexToTraverse->warehouseName,
                       tmp_ARCtoTraverse->weight,
                       tmp_ARCtoTraverse->destination->warehouseName);
            }

            tmp_ARCtoTraverse = tmp_ARCtoTraverse->next;

        }

        tmp_VertexToTraverse = tmp_VertexToTraverse->next;
    }
}

int findPath(struct graphVertex *currentVertex, struct graphVertex *destinationVertex, int *totalDistance) {

    if (currentVertex == NULL || destinationVertex == NULL) {
        return 0;
    }

    //If the given current vertex is already points to the destination vertex then we can directly return 1 because already find it.
    if (currentVertex == destinationVertex) {
        printf("%s", currentVertex->warehouseName);
        return 1;
    }

    //If not equals to the destination vertex then we can raise the processed flag of it because we checked whether it equals to or not.
    currentVertex->processed = 1;

    struct graphArc *currentArc = currentVertex->firstArc;
    while (currentArc != NULL) {

        //We dont need to compare the vertexes if its processed flag is 1
        if (!currentArc->destination->processed) {

            //We call  findPath function again to do the same process again and again
            int matchFlag = findPath(currentArc->destination, destinationVertex, totalDistance);
            //If recursively called findPath function returns 1 this means there is a match so we can upgrade the totalDistance and print the weight and warehouseName
            if (matchFlag == 1) {

                *totalDistance += currentArc->weight;
                printf(" <-%d- %s", currentArc->weight, currentVertex->warehouseName);
                return 1;

            }

        }

        currentArc = currentArc->next;
    }

    return 0;
}

void checkDistance(struct graphHead *warehouseGraph, char *departure, char *destination) {

    //Parameters checking.
    if (warehouseGraph == NULL || departure == NULL || destination == NULL) {

        printf("Wrong parameters! Please check it again!\n");
        return;

    }



    //Finding the toVertex
    struct graphVertex *tmp_ToVertex = warehouseGraph->first;
    while (tmp_ToVertex != NULL && strcmp(tmp_ToVertex->warehouseName, destination) != 0) {

        tmp_ToVertex = tmp_ToVertex->next;
    }



    //Finding the fromVertex
    struct graphVertex *tmp_FromVertex = warehouseGraph->first;
    while (tmp_FromVertex != NULL && strcmp(tmp_FromVertex->warehouseName, departure) != 0) {

        tmp_FromVertex = tmp_FromVertex->next;
    }


    //Checking whether both fromVertex and toVertex are exist.
    if (tmp_FromVertex == NULL || tmp_ToVertex == NULL) {

        printf("At least one of the Vertexes are not found!\n");
        return;
    }


    //Reseting all processed flags to 0.
    struct graphVertex *tmp_VertexToTraverse = warehouseGraph->first;
    while (tmp_VertexToTraverse != NULL) {

        tmp_VertexToTraverse->processed = 0;
        tmp_VertexToTraverse = tmp_VertexToTraverse->next;
    }



    int total = 0;

    printf("Searching for a route from %s to %s...\n", departure, destination);
    if (findPath(tmp_FromVertex, tmp_ToVertex, &total) == 1) {
        printf("\nTotal Distance: %d\n", total);

    }
    else {
        printf("\nThere is no path from %s to %s!\n", departure, destination);

    }

}