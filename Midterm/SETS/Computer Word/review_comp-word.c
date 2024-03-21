#include<stdio.h>
#include<stdbool.h>

typedef unsigned int SET;

void initSet(SET *A);
void insert(SET *A, int n);
void delete(SET *A, int n);
void populateA(SET *A);
void populateB(SET *B);
void display(SET S);

//set operations
int isMember(SET A, int n);
SET unionSet(SET A, SET B);
SET intersectionSet(SET A, SET B);
SET differenceSet(SET A, SET B);

bool isSubset(SET A, SET B);
bool isSuperset(SET A, SET B);

void initSet(SET *A)
{
    *A = 0;
}

void insert(SET *A, int n)
{
    if(n>=0 && n<sizeof(SET)*8)
    {
        *A |= 1 << n;
    }
}

void delete(SET *A, int n)
{
    unsigned int mask = 1;
    if(n>=0 && n<sizeof(SET) * 8)
    {
        *A &= ~(mask << n);
    }
}

SET unionSet(SET A, SET B)
{
    return A | B;
}

SET intersectionSet (SET A, SET B)
{
    return A & B;
}

SET differenceSet(SET A, SET B)
{
    return A &~ B;
}

bool isSubset(SET A, SET B)
{
    return ((A & B) == A) ? true : false;
}

bool isSuperset(SET B, SET A)
{
    return((B & A) == A) ? true : false; //same with isSubset
}

void display(SET S)
{
    int x, size;
    unsigned char mask = 1;
    size = sizeof(SET) * 8;

    for(x=0; x<size; x++)
    {
        if((S & mask) > 0)
        {
            printf("%d ", x);
        }
        
        mask <<= 1;
    }

    printf("\n");
}

void populateA(SET *A)
{
    int arr[] = {1, 2, 3};
    int arrCount = sizeof(arr)/sizeof(arr[0]);
    int x;
    for(x=0; x<arrCount; x++)
    {
        insert(A, arr[x]);
    }
}

void populateB(SET *A)
{
    int arr[] = {1, 2, 3, 5, 6};
    int arrCount = sizeof(arr)/sizeof(arr[0]);
    int x;
    for(x=0; x<arrCount; x++)
    {
        insert(A, arr[x]);
    }
}

int isMember(SET A, int n)
{
    unsigned int mask = 1;
    return ((A & mask << n) > 0) ? 1 : 0;
}
int main()
{
    SET A, B;
    initSet(&A);
    initSet(&B);

    populateA(&A);
    populateB(&B);

    display(A);
    display(B);
}