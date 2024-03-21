#include<stdio.h>
#include<stdlib.h>
#define MAX 20

typedef int SET[MAX];

void displaySet(SET A);
SET* unionSet(SET A, SET B);
SET* intersectionSet(SET A, SET B);
SET *differenceSet(SET A, SET B);

//index 0 will contain the number of elements in a SET

void displaySet(SET A)
{
    int x;
    printf("\n===\nSet: {");

    for(x=1; x<=A[0]; x++)
    {
        printf(" %d ", A[x]);
    }
    printf("}\n");
}

SET *unionSet(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        int x, y;
        
        int sizeA, sizeB, sizeC;
        sizeA = A[0];
        sizeB = B[0];
        sizeC = 0;

        for(x=1, y=1; x<=sizeA && y<=sizeB; )
        {
            if(A[x] < B[y])
            {
                sizeC++;
                (*C)[sizeC] = A[x];
                x++;
            }
            else if(B[y] < A[x])
            {
                sizeC++;
                (*C)[sizeC] = B[y];
                y++;
            }
            else
            {
                sizeC++;
                (*C)[sizeC] = A[x];
                x++, y++;
            }
        }

        if(x<=sizeA)
        {
            for(; x<=sizeA; x++)
            {
                sizeC++;
                (*C)[sizeC] = A[x];
            }
        }

        if(y<=sizeB)
        {
            for(; y<=sizeB; y++)
            {
                sizeC++;
                (*C)[sizeC] = B[y];
            }
        }

        (*C)[0] = sizeC;
    }

    return C;
}

SET* intersectionSet(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        int x, y;
        
        int sizeA, sizeB, sizeC;
        sizeA = A[0];
        sizeB = B[0];
        sizeC = 0;

        for(x=1, y=1; x<=sizeA && y<=sizeB; )
        {
            if(A[x] < B[y])
            {
                x++;
            }
            else if(B[y] < A[x])
            {
                y++;
            }
            else
            {
                sizeC++;
                (*C)[sizeC] = A[x];
                x++, y++;
            }
        }

        (*C)[0] = sizeC;
    }

    return C;
}

SET* differenceSet(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        int x, y;

        int sizeA, sizeB, sizeC;

        sizeA = A[0];
        sizeB = B[0];
        sizeC = 0;

        for(x=1, y=1; x<=sizeA && y<=sizeB; )
        {
            if(A[x] < B[y])
            {
                sizeC++;
                (*C)[sizeC] = A[x];
                x++;
            }
            else if(B[y] < A[x])
            {
                y++;
            }
            else
            {
                x++, y++;
            }
        }

        if(x<=sizeA)
        {
            for(; x<=sizeA; x++)
            {
                sizeC++;
                (*C)[sizeC] = A[x];
            }
        }

        (*C)[0] = sizeC;
    }
    
    return C;
}

int main()
{
    SET A = {3, 1, 5, 6};
    SET B = {4, 5, 6, 7, 9};

    displaySet(A);
    displaySet(B);

    SET *U = unionSet(A, B);
    SET *I = intersectionSet(A, B);
    SET *D = differenceSet(A, B);
    displaySet(*U);
    displaySet(*I);
    displaySet(*D);
    
    free(U);
    free(I);
    free(D);

    return 0;
}