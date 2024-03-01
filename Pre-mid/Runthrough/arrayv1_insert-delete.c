#include<stdio.h>
#include<stdbool.h>
#include<conio.h>
#include<string.h>

#define MAX 5

typedef struct{
    int data[MAX];
    int count;
}LIST;

void initList(LIST *L);
void insertAtBeginning(LIST *L, int data);
void insertAtEnd(LIST *L, int data);
void insertAtPos(LIST *L, int data, int pos);
void deleteAtBeginning(LIST *L);
void deleteAtEnd(LIST *L);
void deleteAtPos(LIST *L, int pos);
void deleteFirstOccur(LIST *L, int data);
void deleteAllOccur(LIST *L, int data);

void print(LIST L);
void populate(LIST *L);
bool isEmpty(LIST L);
bool isFull(LIST L);

void initList(LIST *L)
{
    L->count = 0;
}

void insertAtBeginning(LIST *L, int data)
{
    if(!isFull(*L))
    {
        int x;
        for(x=L->count; x>0; x--)
        {
            L->data[x] = L->data[x-1];
        }
        L->data[0] = data;
        L->count++;
    }
}

void insertAtEnd(LIST *L, int data)
{
    if(!isFull(*L))
    {
        L->data[L->count] = data;
        L->count++;
    }
}

void insertAtPos(LIST *L, int data, int pos)
{
    if(!isFull(*L))
    {
        if(pos>=1 && pos<=L->count+1)
        {
            // printf("\n***\nInserting %d: \n", data);
            int ndx = pos-1;
            int x;
            for(x=L->count; x>ndx; x--)
            {
                L->data[x] = L->data[x-1]; 
            }

            L->data[ndx] = data;
            L->count++;
        }
    }
}

void deleteAtBeginning(LIST *L)
{
    if(!isEmpty(*L))
    {
        int x;
        int end = L->count-1;
        for(x=0; x<end; x++)
        {
            L->data[x] = L->data[x+1];
        }
        L->count--;
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
    if(!isEmpty(*L))
    {   
        if(pos>=1 && pos<=L->count)
        {
            int ndx = pos-1;
            int x;
            for(x=ndx; x<L->count; x++)
            {
                L->data[x] = L->data[x+1];
            }
            L->count--;
        }
    }
}

void deleteFirstOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int ndx;
        for(ndx=0; ndx<L->count&& L->data[ndx]!=data; ndx++){}
        
        if(ndx!=L->count)
        {
            int x;
            int y=L->count-1;
            for(x=ndx; x<y; x++)
            {
                L->data[x] = L->data[x+1];
            }
            L->count--;
        }
    }
}

void deleteAllOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int x; 
        for(x=0; x<L->count;)
        {
            if(L->data[x] == data) 
            {
                int y;
                int end = L->count-1;
                for(y=x; y<end; y++)
                {
                    L->data[y] = L->data[y+1];
                }
                L->count--;
            }
            else
            {
                x++;
            }
        }
    }
}
void print(LIST L)
{
    if(!isEmpty(L))
    {
        printf("\n===\nList: ");
        int x;
        for(x=0; x<L.count; x++)
        {
            printf("%d ", L.data[x]);
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
    return (L.count==MAX) ? true : false;
}

void populate(LIST *L)
{
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 1);
    insertAtEnd(L, 100);
    insertAtEnd(L, 20);
    insertAtPos(L, 1, 5);
}

int main()
{
    LIST myList;
    initList(&myList);
    populate(&myList);
    print(myList);
    
    deleteAllOccur(&myList, 1);
    print(myList);

    return 0;
};


