#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define SIZE 10

typedef struct{
    int arr[SIZE];
    int count;
}LIST;

void initList(LIST *L);
void insertSorted(LIST *L, int data);
void delete(LIST *L, int data);
void populate(LIST *L);
LIST getAllNegatives(LIST L);
void print(LIST L);
bool isEmpty(LIST L);
bool isFull(LIST L);

LIST getAllNegatives(LIST L)
{
    LIST tempList;
    initList(&tempList);

    int x, y=1;
    tempList.count+=1;

    for(x=0; x<L.count; x++)
    {
        if(L.arr[x] < 0)
        {
            tempList.arr[y] = L.arr[x];
            tempList.count++;
            y++;
        }
    }

    tempList.arr[0] = y-1;
    return tempList;
}

void insertSorted(LIST *L, int data)
{
    if(!isFull(*L))
    {
        int ndx;
        for(ndx=0; ndx<L->count && L->arr[ndx] < data; ndx++){}

        int x;
        for(x=L->count; x>ndx; x--)
        {
            L->arr[x] = L->arr[x-1];
        }

        L->arr[ndx] = data;
        L->count++;
    }
}

void initList(LIST *L)
{
    L->count = 0;
}

bool isEmpty(LIST L)
{
    return (L.count==0) ? true : false;
}

bool isFull(LIST L)
{
    return (L.count==SIZE) ? true: false;
}

void delete(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int x;
        for(x=0; x<L->count && L->arr[x] != data; x++){}

        if(L->arr[x]==data)
        {
            int y;
            L->count--;
            for(y=x; y<L->count; y++)
            {
                L->arr[y] = L->arr[y+1];
            }
        }
    }
}

void populate(LIST *L)
{
    insertSorted(L, 11);
    insertSorted(L, 1);
    insertSorted(L, -3);
    insertSorted(L, 5);
    insertSorted(L, 7);
}

void print(LIST L)
{
    if(!isEmpty(L))
    {
        printf("\n===\nList: ");
        int x;
        for(x=0; x<L.count; x++)
        {
            printf("%d ", L.arr[x]);
        }

        //trying to print the last element
        if(L.count==SIZE && L.arr[0]!=0)
        {
            printf("%d ", L.arr[SIZE]);
        }
        printf("\n\n");
    }
}

int main()
{
    LIST myList;
    initList(&myList);

    populate(&myList);

    print(myList);

    LIST negativeList;
    initList(&negativeList);
    negativeList = getAllNegatives(myList);

    print(negativeList);
    delete(&negativeList, -1);
    return 0;  
}

