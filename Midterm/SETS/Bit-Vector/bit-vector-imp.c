    #include<stdio.h>
#include<stdlib.h>
#define MAX 5
typedef int SET[MAX]; //fixed

SET* Union(SET A, SET B);
SET *Intersection(SET A, SET B);
SET *Difference(SET A, SET B);
void Insert(SET *A, int ndx);
void Display(SET A);
void Delete(SET *A, int ndx);
void PopulateA(SET *A);
void PopulateB(SET *B);
void initSet(SET *A);
int member(SET A, int ndx);

void initSet(SET *A)
{
    int x;
    for(x=0; x<MAX; x++)
    {
        (*A)[x] = 0;
    }
}

SET* Union(SET A, SET B)
{
    int x;
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        for(x=0; x<MAX; x++)
        {
            (*C)[x] = A[x] | B[x];
        }
    }

    return C;
}

SET* Intersection(SET A, SET B)
{
    int x;
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        for(x=0; x<MAX; x++)
        {
            (*C)[x] = A[x] & B[x];
        }
    }
    return C;
}

SET* Difference(SET A, SET B)
{
    int x;
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        for(x=0; x<MAX; x++)
        {
            (*C)[x] = A[x] &~ B[x]; 
        }
    }
    return C;
}

void Insert(SET *A, int ndx)
{
    if(ndx>=0 && ndx<MAX)
    {
        (*A)[ndx] = 1;
    }
}

void Delete(SET *A, int ndx)
{
    if(ndx>=0 && ndx<MAX)
    {
        (*A)[ndx] = 0;
    }
}

void PopulateA(SET *A)
{
    Insert(A, 3);
    Insert(A, 0);
}

void PopulateB(SET *B)
{
    Insert(B, 1);
    Insert(B, 4);
    Insert(B, 3);
    Insert(B, 2);
}

int member(SET A, int ndx)
{
    return A[ndx] == 1 ? 1 : 0;
}

void Display(SET A)
{
    int x;
    printf("\n===\nSet: ");
    for(x=0; x<MAX; x++)
    {
        printf("%d ", A[x]);
    }
    printf("\n");
}

int main()
{
    SET A;
    initSet(&A);
    PopulateA(&A);

    SET B;
    initSet(&B);
    PopulateB(&B);

    Display(A);
    Display(B);

    SET *C = Difference(A, B);
    Display(*C);

    free(C);
    return 0;
}

