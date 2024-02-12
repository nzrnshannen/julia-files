#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *link;
}nodeType, *LIST;

void initList(LIST *L);
void insertElem(LIST *L, int data);
void displayList(LIST L);
LIST getAllNegatives(LIST L);
void populate(LIST *L);

void initList(LIST *L)
{
    *L = NULL; 
}

void insertElem(LIST *L, int data) 
{
    LIST newNode = (LIST)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->data = data;
        if(*L==NULL)
        {
            *L = newNode;
        }
        else
        {
            LIST *trav;
            for(trav=L; *trav!=NULL; trav = &(*trav)->link){}

            *trav = newNode;
        }

        newNode->link = NULL;
    }
}

void displayList(LIST L)
{
    printf("\n===\nList: ");
    LIST trav;
    for(trav=L; trav!=NULL; trav=trav->link)
    {
        printf("%d ", trav->data);
    }

    printf("\n\n");
}

void populate(LIST *L)
{
    insertElem(L, -1);
    insertElem(L, -2);
    insertElem(L, -3);
    insertElem(L, -4);
}

LIST getAllNegatives(LIST L)
{
    LIST tempList;
    initList(&tempList);

    int countNegative = 0;
    LIST trav;
    for(trav=L; trav!=NULL; trav=trav->link)
    {
        if(trav->data < 0)
        {
            insertElem(&tempList, trav->data);
            countNegative++;
        }
    }

    LIST countNode = (LIST)malloc(sizeof(nodeType));
    if(countNode!=NULL)
    {
        countNode->data = countNegative;

        countNode->link = tempList;
        tempList = countNode;
    }
    
    return tempList;
}

int main()
{
    LIST testList;
    initList(&testList);

    populate(&testList);
    displayList(testList);

    LIST t1 = getAllNegatives(testList);
    displayList(t1);
    return 0;
}