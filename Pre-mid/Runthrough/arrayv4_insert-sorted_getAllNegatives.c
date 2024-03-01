#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int *elemPtr;
    int count;
}arrList, *LIST;


void insertSorted(LIST *L, int data);
LIST getAllNegatives(LIST *L);

void initList(LIST *L);
void delete(LIST *L, int data); //delete first occur
void populate(LIST *L);
void displayList(LIST L);
void expandList(LIST *L);
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

void insertSorted(LIST *L, int data)
{
    if(isFull(*L))
    {
        expandList(L);
    }
    
    int ndx, x;
    for(x=0; x<(*L)->count && (*L)->elemPtr[x] < data; x++){}

    for(ndx=(*L)->count; ndx>x; ndx--)
    {
        (*L)->elemPtr[ndx] = (*L)->elemPtr[ndx-1];
    }

    (*L)->elemPtr[ndx] = data;
    (*L)->count++;
    
}

LIST getAllNegatives (LIST *L)
{
    if(!isEmpty(*L))
    {
        arrList negaList;
        LIST ptrNegaList = &negaList;

        initList(&ptrNegaList);

        int x;
        int y=1;
        for(x=0; x<(*L)->count; x++)
        {
            if((*L)->elemPtr[x] < 0)
            {
                ptrNegaList->elemPtr[y] = (*L)->elemPtr[x];
                y++;
            }
        }

        ptrNegaList->elemPtr[0] = y-1;
        ptrNegaList->count = y;

        return ptrNegaList;
    }
    else
    {
        return NULL;
    }
}

void delete(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        int ndx;
        for(ndx=0; ndx<(*L)->count && (*L)->elemPtr[ndx] != data; ndx++){}

        int x;
        (*L)->count--;
        for(x=ndx; x<(*L)->count; x++)
        {
            (*L)->elemPtr[x] = (*L)->elemPtr[x+1];
        }
    }
}

void expandList(LIST *L)
{
    int INIT_CAP = (*L)->count;
    (*L)->elemPtr = (int*)realloc((*L)->elemPtr, sizeof(int) * INIT_CAP + 1);
    if((*L)->elemPtr==NULL)
    {
        exit(1);
    }
}

bool isEmpty(LIST L)
{
    return (L->count==0) ? true : false;
}

bool isFull(LIST L)
{
    return (L->count>=SIZE) ? true : false;
}

void displayList(LIST L)
{
    if(!isEmpty(L))
    {
        printf("\n===\nList: ");
        int x;
        for(x=0; x<L->count; x++)
        {
            printf("%d ", L->elemPtr[x]);
        }

        printf("\n\n");
    }
}
void populate(LIST *L)
{
    insertSorted(L, -1);
    insertSorted(L, 10);
    insertSorted(L, -3);
    insertSorted(L, -19);
    insertSorted(L, 0);
    insertSorted(L, 7);
}

int main()
{
    arrList listOne;
    LIST ptrListOne = &listOne;

    arrList listTwo;
    LIST ptrListTwo = &listTwo;

    initList(&ptrListOne);
    populate(&ptrListOne);
    displayList(ptrListOne);

    ptrListTwo = getAllNegatives(&ptrListOne); 
    displayList(ptrListTwo);

    free(ptrListOne->elemPtr);  
    free(ptrListTwo->elemPtr);
    return 0;
}
