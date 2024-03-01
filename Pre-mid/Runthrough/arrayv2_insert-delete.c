#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int arr[SIZE];
    int count;
}arrList, *LIST;

void initList(LIST *L);
void populate(LIST *L);

void insertAtBeginning(LIST *L, int data);
void insertAtEnd(LIST *L, int data);
void insertAtPos(LIST *L, int data, int pos);

void deleteAtBeginning(LIST *L);
void deleteAtPos(LIST *L, int pos);
void deleteAtEnd(LIST *L);
void deleteFirstOccur(LIST *L, int data);
void deleteAllOccur(LIST *L, int data);

bool isEmpty(LIST L);
bool isFull(LIST L);

void print(LIST L);

void initList(LIST *L)
{
    (*L)->count = 0;
}

void populate(LIST *L)
{
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 2);
    insertAtBeginning(L, 2);
    insertAtBeginning(L, 2);
    insertAtPos(L, 2, 2);
}

void insertAtBeginning(LIST *L, int data)
{
    if(!isFull(*L))
    {
        int x;
        for(x=(*L)->count; x>0; x--)
        {
            (*L)->arr[x] = (*L)->arr[x-1];
        }

        (*L)->arr[0] = data;
        (*L)->count++;
    }
}

void insertAtEnd(LIST *L, int data)
{
    if(!isFull(*L))
    {   
        (*L)->arr[(*L)->count] = data;
        (*L)->count++;
    }
}

void insertAtPos(LIST *L, int data, int pos)
{
    if(!isFull(*L) && pos>= 1 && pos<=SIZE)
    {
        int ndx = pos-1;
        int x;
        for(x=(*L)->count; x>ndx; x--)
        {
            (*L)->arr[x] = (*L)->arr[x-1];
        }

        (*L)->arr[ndx] = data;
        (*L)->count++;
    }
}

void deleteAtBeginning(LIST *L)
{
    if(!isEmpty(*L))
    {
        int x;
        (*L)->count--;
        for(x=0; x<(*L)->count; x++)
        {
            (*L)->arr[x] = (*L)->arr[x+1];
        }
    }
}

void deleteAtEnd(LIST *L)
{
    if(!isEmpty(*L))
    {
        (*L)->count--;
    }
}

void deleteAtPos(LIST *L, int pos)
{
    if(!(isEmpty(*L)) && pos>=1 && pos<=SIZE)
    {
        int ndx = pos-1;
        int x;

        (*L)->count--;
        for(x=ndx; x<(*L)->count; x++)
        {
            (*L)->arr[x] = (*L)->arr[x+1];
        }
    }
}

void deleteFirstOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int x;
        for(x=0; x<(*L)->arr[x] && data!= (*L)->arr[x]; x++){}

        if(data==(*L)->arr[x])
        {
            int ndx;
            (*L)->count--;
            for(ndx=x; ndx<(*L)->count; ndx++)
            {
                (*L)->arr[ndx] = (*L)->arr[ndx+1];
            }
        }
    }
}

void deleteAllOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int x;
        for(x=0; x<(*L)->count; )
        {
            if((*L)->arr[x] == data)
            {
                int y;
                (*L)->count--;
                for(y=x; y<(*L)->count; y++)
                {
                    (*L)->arr[y] = (*L)->arr[y+1];
                }

                x = 0;
            }
            else
            {
                x++;
            }
        }
    }
}

bool isEmpty(LIST L)
{
    return (L->count==0) ? true : false;
}

bool isFull(LIST L)
{
    return (L->count==SIZE) ? true : false;
}

void print(LIST L)
{
    if(!isEmpty(L))
    {
        printf("\n===\nList: ");
        int x;
        for(x=0; x<L->count; x++)
        {
            printf("%d ", L->arr[x]);
        }

        printf("\n\n");
    }
}
int main()
{
    arrList test;
    LIST myList = &test;
    initList(&myList);
    populate(&myList);
    print(myList);

    deleteAllOccur(&myList, 2);

    print(myList);
    return 0;
}