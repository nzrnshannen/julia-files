#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int arr[SIZE];
    int count;
}LIST;

void print(LIST L);
void delete(LIST *L, int data); //deleteFirstOccur
void populate(LIST *L);
void initList(LIST *L);
void insertSorted(LIST *L, int data);
bool isEmpty(LIST L);
bool isFull(LIST L);

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

        printf("\n\n");
    }
}

bool isEmpty(LIST L)
{
    return (L.count==0) ? true : false;
}

bool isFull(LIST L)
{
    return (L.count==SIZE) ? true : false;
}

void initList(LIST *L)
{
    L->count=0;
}

void insertSorted(LIST *L, int data)
{
    if(!isFull(*L))
    {
        int x;
        for(x=0; x<L->count && data > L->arr[x]; x++){}

        int ndx = x;
        int y;

        for(y=L->count; y>ndx; y--)
        {
            L->arr[y] = L->arr[y-1];
        }

        L->arr[ndx] = data;
        L->count++;
    }
}

void delete(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int ndx;
        for(ndx=0; ndx<L->count && data!=L->arr[ndx]; ndx++){}

        if(data==L->arr[ndx])
        {
            int x;
            L->count--;
            for(x=ndx; x<L->count; x++)
            {
                L->arr[x] = L->arr[x+1];
            }
        }
    }
}
void populate(LIST *L)
{
    insertSorted(L, 1);
    insertSorted(L, -1);
    insertSorted(L, 0);
    insertSorted(L, 3);
    insertSorted(L, 5);
    insertSorted(L, 3);
}


int main()
{
    LIST myList;
    initList(&myList);

    populate(&myList);
    print(myList);
    delete(&myList, 5);
    print(myList);
    return 0;
}
