#ifndef UNTITLED_AVLTREE_H
#define UNTITLED_AVLTREE_H

#endif //UNTITLED_AVLTREE_H


struct SpeciesDetails{
    char SpeciesName[70];
    float FishLength;
    char FishingDate[20];
    char City[70];
    struct SpeciesDetails *Next;
};

struct SpeciesWeightTree {
    float Weight;
    struct SpeciesDetails *Details;
    struct SpeciesWeightTree *LeftChild;
    struct SpeciesWeightTree *RightChild;
    int Height;

};


struct SpeciesWeightTree* readData(char *);
void displayIndex(struct SpeciesWeightTree*);
struct SpeciesWeightTree* insertFish(struct SpeciesWeightTree*, char*, float, float, char*, char*);
void heaviestFish(struct SpeciesWeightTree*);
void longestFish(struct SpeciesWeightTree*);
void findLongestFishNode(struct SpeciesWeightTree*, struct SpeciesDetails**, float*);



struct SpeciesWeightTree* CreateTree(void);
struct SpeciesWeightTree* MakeEmptyTree(struct SpeciesWeightTree* );
struct SpeciesWeightTree* SingleRotateWithLeft(struct SpeciesWeightTree*);
struct SpeciesWeightTree* SingleRotateWithRight(struct SpeciesWeightTree*);
struct SpeciesWeightTree* DoubleRotateWithLeft(struct SpeciesWeightTree*);
struct SpeciesWeightTree* DoubleRotateWithRight(struct SpeciesWeightTree*);
int AVLTreeHeight(struct SpeciesWeightTree*);
int Max(int, int);


struct SpeciesWeightTree* CreateTree(void) {
    return NULL;
}


struct SpeciesWeightTree* MakeEmptyTree(struct SpeciesWeightTree* t) {
    if (t != NULL) {

        t->LeftChild = MakeEmptyTree(t->LeftChild);
        t->RightChild = MakeEmptyTree(t->RightChild);

        struct SpeciesDetails* details = t->Details;
        struct SpeciesDetails* nextDetails;
        //Deleting details nodes

        while (details != NULL) {
            nextDetails = details->Next;
            free(details);
            details = nextDetails;
        }

        free(t);
    }
    return NULL;
}


struct SpeciesWeightTree* SingleRotateWithLeft(struct SpeciesWeightTree* k2) {
    struct SpeciesWeightTree* k1 = k2->LeftChild;
    k2->LeftChild = k1->RightChild;
    k1->RightChild = k2;

    k1->Height = Max(AVLTreeHeight(k1->RightChild), AVLTreeHeight(k1->LeftChild));
    k2->Height = Max(AVLTreeHeight(k2->RightChild), AVLTreeHeight(k2->LeftChild));

    return k1;
}

struct SpeciesWeightTree* SingleRotateWithRight(struct SpeciesWeightTree* k1) {
    struct SpeciesWeightTree* k2 = k1->RightChild;
    k1->RightChild = k2->LeftChild;
    k2->LeftChild = k1;

    k1->Height = Max(AVLTreeHeight(k1->RightChild), AVLTreeHeight(k1->LeftChild)) + 1;
    k2->Height = Max(AVLTreeHeight(k2->RightChild), AVLTreeHeight(k2->LeftChild)) + 1;

    return k2;
}

struct SpeciesWeightTree* DoubleRotateWithLeft(struct SpeciesWeightTree* k3) {
    k3->LeftChild = SingleRotateWithRight(k3->LeftChild);
    return SingleRotateWithRight(k3);
}

struct SpeciesWeightTree* DoubleRotateWithRight(struct SpeciesWeightTree* k3) {
    k3->RightChild = SingleRotateWithLeft(k3->RightChild);
    return SingleRotateWithRight(k3);
}

int Max(int x, int y) {
    if (x >= y) {
        return x;
    }
    else {
        return y;
    }
}

int AVLTreeHeight(struct SpeciesWeightTree* t)
{
    if (t == NULL) {
        return -1;
    }
    else {
        return t->Height;
    }
}