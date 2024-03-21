#include<stdio.h>
#include<stdbool.h>
#define SIZE 10
#define EMPTY -2
#define DELETED -1

typedef int Dictionary[SIZE];

void initDict(Dictionary D);
void displayDict(Dictionary D);
int hash(int elem);
void insert(Dictionary D, int elem);
void populate(Dictionary D);
bool isMember(Dictionary D, int elem);
void deleteMem(Dictionary D, int elem);

void initDict(Dictionary D)
{
    int x;
    for(x=0; x<SIZE; x++)
    {
        D[x] = EMPTY;
    }
}

void displayDict(Dictionary D)
{
    int x;
    printf("\n===\nDictionary:\n");
    for(x=0; x<SIZE; x++)
    {
        printf("D[%d]: ", x);
        switch(D[x])
        {
            case EMPTY: printf("EMPTY \n"); break;
            case DELETED: printf("DELETED \n"); break;
            default: printf("%d\n", D[x]); break;
        }
    }

    printf("\n");
}

int hash(int elem)
{
    return elem% SIZE;
}

void insert(Dictionary D, int elem)
{
    int key, ctr, numDeleted;
    numDeleted = 0;

    //search if there's an existing elem in the dictionary

    //loop will stop if ctr will be equal to size (which is equal to the key value)
    //loop will stop if D[key] == EMPTY
    //loop will stop if D[key] == elem 
    for(key=hash(elem), ctr = 0; ctr<SIZE && D[key]!=EMPTY && D[key]!=elem; key=hash(key+1), ctr++)
    {
        if(D[key] == DELETED)
        {
            numDeleted++;
        }
    }

    //inserting elem

    if(D[key]==elem)
    {
        printf("\n\t>> Element already exists! <<\n");
    }
    else if(ctr==SIZE && numDeleted==0)
    {
        //if ctr is == to SIZE (which is also the value of key) and numDeled is 0, meaning dictionary is FULL
        printf("\n\t>> No more available space! <<\n");
    }
    else
    {
        //inserting elem
        
        for(key=hash(elem); D[key]!=DELETED && D[key]!=EMPTY; key = hash(key+1)){}

        D[key] = elem;
    }

}

void deleteMem(Dictionary D, int elem)
{
    int ctr, key;
    for(key=hash(elem), ctr=0; ctr<SIZE && D[key]!=EMPTY && D[key]!=elem; ctr++, key=hash(key+1)){}

    if(D[key]==elem)
    {
        D[key] = DELETED;
    }
    else
    {
        printf("\n\t>> Element not found! <<\n");
    }

}

bool isMember(Dictionary D, int elem)
{
    int key, ctr;
    for(key=hash(elem), ctr=0; ctr<SIZE && D[key]!=EMPTY && D[key]!=elem; key=hash(key+1), ctr++){}

    return (ctr<SIZE && D[key]==elem) ? true : false;
}

void populate(Dictionary D)
{
    insert(D, 0);
    insert(D, 11);
    insert(D, 20);
    insert(D, 9);
    insert(D, 8);
    insert(D, 60);

}

int main()
{
    Dictionary myDict;
    initDict(myDict);

    populate(myDict);
    displayDict(myDict);


    printf("\nTest = %d\n", isMember(myDict, 67));

    return 0;
}