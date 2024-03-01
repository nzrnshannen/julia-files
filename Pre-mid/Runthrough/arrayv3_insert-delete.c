#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define SIZE 5

typedef struct{
    int *elemPtr;
    int count;
}LIST;

void initList(LIST *L);
void populate(LIST *L);
void insertAtBeginning(LIST *L, int data);
void insertAtEnd(LIST *L, int data);
void insertAtPos(LIST *L, int data, int pos);
void deleteAtBeginning(LIST *L);
void deleteAtEnd(LIST *L);
void deleteAtPos(LIST *L, int pos);
void deleteFirstOccur(LIST *L, int data);
void deleteAllOccur(LIST *L, int data);
void displayList(LIST L);
void expandList(LIST *L);
bool isEmpty(LIST L);
bool isFull(LIST L);

void initList(LIST *L)
{
    L->count=0;
    L->elemPtr = (int*)malloc(sizeof(int) * SIZE);
    if(L->elemPtr==NULL)
    {
        exit(1);
    }
}

bool isEmpty(LIST L)
{
    return (L.count==0) ? true : false;
}

bool isFull(LIST L)
{
    return (L.count>=SIZE) ? true : false;
}

void displayList(LIST L)
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

void insertAtBeginning(LIST *L, int data)
{
    if(isFull(*L))
    {
        expandList(L);
    }

    int x;
    for(x=L->count; x>0; x--)
    {
        L->elemPtr[x] = L->elemPtr[x-1];
    }

    L->elemPtr[0] = data;
    L->count++;
}

void insertAtEnd(LIST *L, int data)
{
    if(isFull(*L))
    {
        expandList(L);
    }

    L->elemPtr[L->count] = data;
    L->count++;
}

void insertAtPos(LIST *L, int data, int pos)
{
    if(isFull(*L))
    {
        expandList(L);
    }

    if(pos>=1 && pos<=L->count+1)
    {
        int ndx = pos-1;
        int x;
        for(x=L->count; x>ndx; x--)
        {
            L->elemPtr[x] = L->elemPtr[x-1];
        }

        L->elemPtr[ndx] = data;
        L->count++;
    }
}

void deleteAtBeginning(LIST *L)
{
    if(!isEmpty(*L))
    {
        int x;
        L->count--;
        for(x=0; x<L->count; x++)
        {
            L->elemPtr[x] = L->elemPtr[x+1];
        }
    }
}

void deleteAtEnd(LIST *L)
{
    if(!isEmpty(*L))
    {
        L->count--;
    }
}

void deleteAtPos(LIST *L, int pos)
{
    if(!isEmpty(*L) && pos>=1 && pos<=L->count)
    {
        int ndx;
        L->count--;
        for(ndx=pos-1; ndx<L->count; ndx++)
        {
            L->elemPtr[ndx] = L->elemPtr[ndx+1];
        }
    }
}

void deleteFirstOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int ndx;
        for(ndx=0; ndx < L->count && data!=L->elemPtr[ndx]; ndx++){}

        if(data==L->elemPtr[ndx])
        {
            int x;
            L->count--;
            for(x=ndx; x<L->count; x++)
            {
                L->elemPtr[x] = L->elemPtr[x+1];
            }
        }   
    }
}

void deleteAllOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int x;
        for(x=0; x<L->count; )
        {
            if(L->elemPtr[x]==data)
            {
                int ndx;
                L->count--;
                for(ndx=x; ndx<L->count; ndx++)
                {
                    L->elemPtr[ndx] = L->elemPtr[ndx+1];
                }
                x=0;
            }
            else
            {
                x++;
            }
        }
    }
}

void populate(LIST *L)
{
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 3);
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 5);
    insertAtEnd(L, 6);
    insertAtPos(L, 1, 4);
}

int main()
{
    LIST myList;
    initList(&myList);
    populate(&myList);
    displayList(myList);

    deleteAllOccur(&myList, 1);
    displayList(myList);
    free(myList.elemPtr);
    return 0;
}