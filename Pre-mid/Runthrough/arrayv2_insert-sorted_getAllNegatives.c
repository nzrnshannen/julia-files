#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int data[SIZE];
    int count;
}arrList, *LIST;

void initList(LIST *L);
void populate(LIST *L);
void insertSorted(LIST *L, int data);
arrList getAllNegatives(LIST L);
void displayList(LIST L);
bool isEmpty(LIST L);
bool isFull(LIST L);

bool isEmpty(LIST L)
{
    return (L->count==0) ? true : false;
}

bool isFull(LIST L)
{
    return (L->count==SIZE) ? true : false;
}

void displayList(LIST L)
{
    if(!isEmpty(L))
    {
        printf("\n===\nList: ");
        int x;
        for(x=0; x<L->count; x++)
        {
            printf("%d ", L->data[x]);
        }
        printf("\n\n");
    }
}

void initList(LIST *L)
{
    (*L)->count = 0;
}

void insertSorted(LIST *L, int data)
{
    if(!isFull(*L))
    {
        int x;
        for(x=0; x<(*L)->count && (*L)->data[x] < data; x++){}

        int y;
        for(y=(*L)->count; y>x; y--)
        {
            (*L)->data[y] = (*L)->data[y-1];
        }

        (*L)->data[x] = data;

        (*L)->count++;        
    }
}

arrList getAllNegatives(LIST L)
{
    arrList tempList;
    LIST ptemp = &tempList;
    initList(&ptemp);

    if(!isEmpty(L))
    {
        int x, y=1;
        ptemp->count++;
        
        for(x=0; x<L->count; x++)
        {
            if(L->data[x] < 0)
            {
                if(y>=SIZE)
                {
                    printf("\n\t>> Temp list is full. Last negative element is: %d. << \n", L->data[x]);
                }
                else
                {
                    insertSorted(&ptemp, L->data[x]);
                    printf("\ncount = %d\n", ptemp->count);
                    y++;
                }
            }
        }

        int z;
        for(z=ptemp->count; z>0; z--)
        {
            ptemp->data[z] = ptemp->data[z-1];
        }
        
    

        ptemp->data[z] = y;
        ptemp->count = y;
    }

    return tempList;
}

void populate(LIST *L)
{
    insertSorted(L, -1);
    insertSorted(L, -7);
    insertSorted(L, -5);
    insertSorted(L, -91);
    insertSorted(L, -11);
    insertSorted(L, -2000);
}

int main()
{
    arrList mylist;
    LIST ptr_myList = &mylist;
    initList(&ptr_myList);
    populate(&ptr_myList);
    displayList(ptr_myList);

    arrList negaList;
    negaList = getAllNegatives(ptr_myList);
    displayList(&negaList);
    return 0;
}