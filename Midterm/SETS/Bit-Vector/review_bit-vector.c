#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 10

typedef int SET[MAX];

void initSet(SET *A);
void displaySet(SET A);
void insert(SET *A, int ndx);
void delete(SET *A, int ndx);

SET *Union(SET A, SET B);
SET *Intersection(SET A, SET B);
SET *Difference(SET A, SET B);

bool isSubset(SET A, SET B);
bool isSuperset(SET B, SET A);

void populateA(SET *A);
void populateB(SET *B);

void initSet(SET *A)
{
    int x;
    for(x=0; x<MAX; x++)
    {
        (*A)[x] = 0;
    }
}

void displaySet(SET A)
{
    printf("\n===\nSet: ");
    int x;
    for(x=0; x<MAX; x++)
    {
        printf("%d ", A[x]);
    }
    printf("\n\n");
}

void insert(SET *A, int ndx)
{
    if(ndx>=0 && ndx<MAX)
    {
        (*A)[ndx] = 1;
    }
}

void delete(SET *A, int ndx)
{
    if(ndx>=0 && ndx<MAX)
    {
        (*A)[ndx] = 0;
    }
}

SET *Union(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(*C!=NULL)
    {
        int x;
        for(x=0; x<MAX; x++)
        {
            (*C)[x] = A[x] | B[x];
        }
    }

    return C;
}

SET *Intersection(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(*C!=NULL)
    {
        int x;
        for(x=0; x<MAX; x++)
        {
            (*C)[x] = A[x] & B[x];
        }
    }

    return C;
}

SET * Difference(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(*C!=NULL)
    {
        int x;
        for(x=0; x<MAX; x++)
        {
            (*C)[x] = A[x] &~ B[x];
        }
    }

    return C;
}

bool isSubset(SET A, SET B)
{
    int x;

    for(x=0; x<MAX && (A[x] & ~B[x]) == 0; x++){}

    return (x==MAX) ? true : false;
}

bool isSuperset(SET B, SET A)
{
    int x;
    for(x=0; x<MAX && (~B[x] & A[x])==0; x++){}

    return (x==MAX) ? true : false;
}

void populateA(SET *A)
{
    insert(A, 0);
    insert(A, 1);
    insert(A, 2);
    insert(A, 6);
}

void populateB(SET *B)
{
    insert(B, 0);
    insert(B, 1);
    insert(B, 2);
    insert(B, 5);
    insert(B, 6);
}

int main()
{
    SET A, B;

    initSet(&A);
    initSet(&B);

    populateA(&A);
    populateB(&B);

    displaySet(A);
    displaySet(B);


    SET *U, *I, *D;
    U = Union(A, B);
    I = Intersection(A, B);
    D = Difference(A, B);

    printf("\n\t>> U I D <<\n");
    displaySet(*U);
    displaySet(*I);
    displaySet(*D);

    printf("\n==\nTest if A is a subset of B: %d\n", isSubset(A, B));
    printf("==\nTest if B is a superset of A: %d\n", isSuperset(B, A));
    return 0;
}