#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 5

typedef struct{
    int *elemPtr;
    int count;
}arrList, *LIST;

void initList(LIST *L);
void populate(LIST *L);
void insertAtEnd(LIST *L, int data);
void insertAtBeginning(LIST *L, int data);
void insertAtPos(LIST *L, int data, int pos);
void deleteAtEnd(LIST *L);
void deleteAtBeginning(LIST *L);
void deleteAtPos(LIST *L, int pos);
void deleteAllOccur(LIST *L, int data);
void deleteFirstOccur(LIST *L, int data);
void displayList(LIST *L);
bool isEmpty(LIST L);
bool isFull(LIST L);

void initList(LIST *L)
{
    (*L)->count = 0;
    (*L)->elemPtr = (int*)malloc(sizeof(int) * SIZE);
    if((*L)->elemPtr==NULL)
    {
        exit(1);
    }
}

void populate(LIST *L)
{
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 3);
    insertAtBeginning(L, 1);
    insertAtEnd(L, 5);
    insertAtEnd(L, 6);
    insertAtPos(L, 100, 7);
}

void insertAtEnd(LIST *L, int data)
{
    if(isFull(*L))
    {
        int INIT_CAP = (*L)->count;
        (*L)->elemPtr = (int*)realloc((*L)->elemPtr, sizeof(int) * INIT_CAP + 1);
        if((*L)->elemPtr==NULL)
        {
            exit(1);
        }
    }

    (*L)->elemPtr[(*L)->count] = data;
    (*L)->count++;
}

void insertAtBeginning(LIST *L, int data)
{
    if(isFull(*L))
    {
        int INIT_CAP = (*L)->count;
        (*L)->elemPtr = (int*)realloc((*L)->elemPtr, sizeof(int) * INIT_CAP+1);
        if((*L)->elemPtr==NULL)
        {
            exit(1);
        }
    }   

    int x;
    for(x=(*L)->count; x>0; x--)
    {
        (*L)->elemPtr[x] = (*L)->elemPtr[x-1];
    }

    (*L)->elemPtr[0] = data;
    (*L)->count++;
}

void insertAtPos(LIST *L, int data, int pos)
{
    if(pos>=1 && pos <= (*L)->count+1)
    {
        if(isFull(*L))
        {
            int INIT_CAP = (*L)->count;
            (*L)->elemPtr = (int*)realloc((*L)->elemPtr, sizeof(int) * INIT_CAP + 1);
            if((*L)->elemPtr==NULL)
            {
                exit(1);
            }
        }   

        int ndx = pos-1;
        int x;
        for(x=(*L)->count; x>ndx; x--)
        {
            (*L)->elemPtr[x] = (*L)->elemPtr[x-1];
        }
        (*L)->elemPtr[ndx] = data;
        (*L)->count++;
    }
}

void deleteAtBeginning(LIST *L)
{
    if(!isEmpty(*L))
    {
        (*L)->count--;
        int x;
        for(x=0; x<(*L)->count; x++)
        {
            (*L)->elemPtr[x] = (*L)->elemPtr[x+1];
        }
    }
}

void deleteAtPos(LIST *L, int pos)
{
    if(!isEmpty(*L) && pos>=1 && pos<=(*L)->count)
    {
        int ndx = pos-1;
        (*L)->count--;

        int x;
        for(x=ndx; x<(*L)->count; x++)
        {
            (*L)->elemPtr[x] = (*L)->elemPtr[x+1];
        }
        
    }
}

void deleteFirstOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int x;
        for(x=0; x<(*L)->count && (*L)->elemPtr[x]!=data; x++){}

        if((*L)->elemPtr[x]==data)
        {
            (*L)->count--;
            int y;
            for(y=x; y<(*L)->count; y++)
            {
                (*L)->elemPtr[y] = (*L)->elemPtr[y+1];
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
            if((*L)->elemPtr[x]==data)
            {
                (*L)->count--;
                int y;
                for(y=x; y<(*L)->count; y++)
                {
                    (*L)->elemPtr[y] = (*L)->elemPtr[y+1];
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

void displayList(LIST *L)
{
    if(!isEmpty(*L))
    {
        printf("\n===\nList: ");
        int x;
        for(x=0; x<(*L)->count; x++)
        {
            printf("%d ", (*L)->elemPtr[x]);
        }

        printf("\n\n");
    }
}

void deleteAtEnd(LIST *L)
{
    if(!isEmpty(*L))
    {
        (*L)->count--;
    }
}
bool isEmpty(LIST L)
{
    return (L->count==0) ? true: false;
}

bool isFull(LIST L)
{
    return (L->count>=SIZE)? true: false;
}


int main()
{
    arrList listOne;
    LIST ptrListOne = &listOne;
    initList(&ptrListOne);
    populate(&ptrListOne);
    displayList(&ptrListOne);

    deleteAllOccur(&ptrListOne, 1);
    displayList(&ptrListOne);
    free(ptrListOne->elemPtr);
    return 0;
}