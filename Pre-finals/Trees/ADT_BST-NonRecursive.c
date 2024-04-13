#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define SIZE 50

//linked list
typedef struct cell{
    int label;
    struct cell *LC;
    struct cell *RC;
} cellType, *Tree;

void initTree(Tree *T);
void populate(Tree *T);
void insertMem(Tree *T, int node);
void displayInorder(Tree T);
void displayPreorder(Tree T);
void displayPostOrder(Tree T);
bool isMember(Tree T, int node);
int largestMem(Tree T);
int smallestMem(Tree T);
void deleteMem(Tree *T, int node);
int deleteMax(Tree *T);
int deleteMin(Tree *T);
bool isLeaf(Tree T);
bool hasOneChild(Tree T);
bool hasTwoChildren(Tree T);

void initTree(Tree *T)
{
    *T = NULL;
}

bool isLeaf (Tree T)
{
    return (T->LC == NULL && T->RC == NULL) ? true : false; 
}

bool hasOneChild(Tree T)
{
    return ((T->LC==NULL && T->RC!=NULL) || (T->LC!=NULL && T->RC==NULL)) ? true : false;
}

bool hasTwoChildren(Tree T)
{
    return (T->LC!=NULL && T->RC!=NULL) ? true : false; 
} 
void insertMem(Tree *T, int node)
{
    Tree *trav;
    for(trav=T; *trav!=NULL && (*trav)->label!=node; )
    {
        trav = (node < (*trav)->label) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav==NULL)
    {
        *trav = (Tree)calloc(1, sizeof(cellType));
        (*trav)->label = node;
    }
}

void displayPreorder(Tree T)
{
        Tree tempStack[SIZE], currentCell;
        int top=-1;

    if(T!=NULL)
    {
        printf("\nPreoder: ");
        for(tempStack[++top] = T; top!=-1; )
        {
            currentCell = tempStack[top];

            if(currentCell!=NULL)
            {
                printf("%d ", currentCell->label);
                tempStack[++top] = currentCell->LC;
            }
            else
            {
                currentCell = tempStack[--top]; //performing pop()
                tempStack[top] = currentCell->RC;
            }
        }
    }
    else
    {
        printf("\nEmpty!\n");
    }

    printf("\n");
}

void deleteMem(Tree *T, int node)
{
    if(*T!=NULL)
    {
        Tree *trav;
        for(trav=T; *trav!=NULL && (*trav)->label!=node; )
        {
            trav = (node < (*trav)->label) ? &(*trav)->LC : &(*trav)->RC;
        }

        if(*trav!=NULL)
        {
            Tree temp;
            temp = *trav;

            //case 1 
            if(isLeaf(temp))
            {
                *trav = NULL;
            }

            //case 2
            if(hasOneChild(temp))
            {
                if(temp->LC==NULL)
                {
                    *trav = temp->RC;
                }
                else
                {
                    *trav = temp->LC;
                }
            }

            //case 3
            if(hasTwoChildren(temp))
            {
                //using predecessor
                Tree predNode = temp->LC;
                predNode->RC = temp->RC;
                *trav = predNode;


                //using successor

            }

            free(temp);
        }
    }
}

void populate(Tree *T)
{
    inse-rtMem(T, 78);
    insertMem(T, 7);
    insertMem(T, 91);
    insertMem(T, 84);
    insertMem(T, 99);
}


int main()
{
    Tree myTree_1;+
    initTree(&myTree_1);
    populate(&myTree_1);
    deleteMem(&myTree_1, 91);
    displayPreorder(myTree_1);

    return 0;
}