#include<stdlib.h>
#include<stdio.h>
#define MAX 5
typedef int SET[MAX];

SET* Union(SET A, SET B);
SET* Intersection(SET A, SET B);
SET* Difference(SET A, SET B);
void PopulateA(SET *A);
void PopulateB(SET *B);
void initSet(SET *A);
void Insert(SET *A, int ndx);
void Delete(SET *A, int ndx);
int member(SET A, int ndx);
void Display(SET A);

SET* Union(SET A, SET B)
{
    SET* C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        initSet(C);
        int x;
        for(x=0; x<MAX; x++)
        {
            if(A[x] || B[x])
            {
                (*C)[x] = 1;
            }
        }
    }

    return C;
}

SET * Intersection(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        // initSet(C);
        int x;
        for(x=0; x<MAX; x++)
        {
            if(A[x] && B[x])
            {
                (*C)[x] = 1;
            }
        }
    }
    
    return C;
}

SET* Difference(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        initSet(C);
        int x;
        for(x=0; x<MAX; x++)
        {
            if(A[x] == 1 && A[x] != B[x])
            {
                (*C)[x] = 1;
            }
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

void initSet(SET *A)
{
    int x;
    for(x=0; x<MAX; x++)
    {
        (*A)[x] = 0;
    }
}

int member(SET A, int ndx)
{
    return A[ndx] == 1 ? 1 : 0;
}

void PopulateA(SET *A)
{
    Insert(A, 1);
    Insert(A, 0);
    Insert(A, 3);
    Insert(A, 4);
}

void PopulateB(SET *B)
{
    Insert(B, 2);
    Insert(B, 1);
    Insert(B, 4);
}

void Display(SET A)
{
    int x;
    printf("\n===\nSet: ");
    for(x=0; x<MAX; x++)    
        printf("%d ", A[x]);

    printf("\n\n");
}


int main()
{
    SET A, B;
    initSet(&A);
    initSet(&B);
    PopulateA(&A);
    PopulateB(&B);

    Display(A);
    Display(B);

    SET *C = Intersection(A, B);
    Display(*C);

    free(C);
    return 0;
}