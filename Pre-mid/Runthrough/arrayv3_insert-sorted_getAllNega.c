#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 5

typedef struct{
    int *elemPtr;
    int count;
}LIST;

void initList(LIST *L);
void populate(LIST *L);
void insertSorted(LIST *L, int data);
LIST getAllNegatives(LIST L);
void display(LIST L);
void expandList(LIST *L);
bool isFull(LIST L);
bool isEmpty(LIST L);


void initList(LIST *L)
{
    L->count = 0;
    L->elemPtr = (int*)malloc(sizeof(int) * SIZE);
    if(L->elemPtr==NULL)
    {
        exit(1);
    }
}

bool isFull(LIST L)
{
    return (L.count>=SIZE) ? true : false;
}

bool isEmpty(LIST L)
{
    return (L.count==0) ? true : false;
}

void insertSorted(LIST *L, int data)
{
    if(isFull(*L))
    {
        expandList(L);
    }

    int x;
    for(x=0; x<L->count && L->elemPtr[x] < data; x++){}

    int y;
    for(y=L->count; y>x; y--)
    {
        L->elemPtr[y] = L->elemPtr[y-1];
    }

    L->elemPtr[x] = data;
    L->count++;
}

LIST getAllNegatives(LIST L)
{
    LIST tempList;
    initList(&tempList);

    if(!isEmpty(L))
    {
        int x, y=1;

        for(x=0; x<L.count; x++)
        {
            if(L.elemPtr[x] < 0)
            {
                if(isFull(tempList))
                {
                    expandList(&tempList);
                }
                tempList.elemPtr[y] = L.elemPtr[x];
                y++;
            }
        }

        tempList.count = y;
        tempList.elemPtr[0] = y-1;
    }

    return tempList;
}

void display(LIST L)
{
    if(!isEmpty(L))
    {
        printf("\n===\nList: ");
        int x;
        for(x=0; x<L.count; x++)
        {
            printf("%d ", L.elemPtr[x]);
        }

        printf("\n\n");
    }
}

void expandList(LIST *L)
{
    int INIT_CAP = L->count;
    L->elemPtr = (int*)realloc(L->elemPtr, sizeof(int) * INIT_CAP + 1);
    if(L->elemPtr==NULL)
    {
        exit(1);
    }
}

void populate(LIST *L)
{
    insertSorted(L, -1);
    insertSorted(L, -9);
    insertSorted(L, -5);
    insertSorted(L, -66);
    insertSorted(L, -1);
    insertSorted(L, -77);
    insertSorted(L, -3);
}

int main()
{
    LIST myList;
    initList(&myList);
    populate(&myList);
    display(myList);

    LIST negaList = getAllNegatives(myList);
    display(negaList);

    free(myList.elemPtr);
    free(negaList.elemPtr);
    return 0;
}