#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}nodeType, *LIST;


bool isEmpty(LIST L);
void displayList(LIST L);
void initList(LIST *L);
void populate(LIST *L);
void insertSorted(LIST *L, int data);
void delete(LIST *L); //delete at end
LIST getAllNegatives(LIST L);
void clearList(LIST *L);

bool isEmpty(LIST L)
{
    return (L==NULL)? true: false;
}

void displayList(LIST L)
{
    if(!isEmpty(L))
    {
        printf("\n===\nList: ");
        LIST trav;
        for(trav=L; trav!=NULL; trav=trav->next)
        {
            printf("%d ", trav->data);
        }

        printf("\n\n");
    }
}

void initList(LIST *L)
{
    *L = NULL;
}

void insertSorted(LIST *L, int data)
{
    LIST newNode = (LIST)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->data = data;
        
        LIST *trav;
        for(trav=L; *trav!=NULL && (*trav)->data < data; trav=&(*trav)->next){}

        newNode->next = *trav;
        *trav = newNode;
    }
}

void delete(LIST *L)
{
    if(!isEmpty(*L))
    {
        LIST *trav;
        for(trav=L; (*trav)->next!=NULL; trav=&(*trav)->next){}

        LIST temp;
        temp = *trav;
        *trav = NULL;
        free(temp);
    }
}

LIST getAllNegatives(LIST L)
{
    LIST tempList;
    int count=0;
    initList(&tempList);

    LIST trav;
    for(trav=L; trav!=NULL; trav=trav->next)
    {
        if(trav->data < 0)
        {
            insertSorted(&tempList, trav->data);
            count++;
        }
    }

    LIST countNode = (LIST)malloc(sizeof(nodeType));
    if(countNode!=NULL)
    {
        countNode->data = count;
        countNode->next = tempList;
        tempList = countNode;
    }

    return tempList;
}

void populate(LIST *L)
{
    insertSorted(L, 1);
    insertSorted(L, 9);
    insertSorted(L, -11);
    insertSorted(L, 2);
}

void clearList(LIST *L)
{
    while(!isEmpty(*L))
    {
        LIST clr;
        clr = *L;
        *L = (*L)->next;
        free(clr);
    }
}

int main()
{
    LIST myList;
    initList(&myList);
    populate(&myList);

    displayList(myList);

    LIST secondList = getAllNegatives(myList);
    displayList(secondList);
    clearList(&myList);
    return 0;
}
