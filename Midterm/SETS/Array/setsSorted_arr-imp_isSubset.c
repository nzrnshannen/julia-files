#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100

typedef int SET[MAX];

void display(SET A);
SET *unionSet(SET A, SET B);
SET *intersectionSet(SET A, SET B);
SET *differenceSet(SET A, SET B);
bool isSubset(SET A, SET B);


void display(SET A)
{
    int x;
    printf("\n===\nSET: { ");
    for(x=1; x<=A[0]; x++)
    {
        printf("%d ", A[x]);
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
            sizeC++;
            if(A[x] < B[y])
            {
                (*C)[sizeC] = A[x];
                x++;
            }
            else if(B[y] < A[x])
            {
                (*C)[sizeC] = B[y];
                y++;
            }
            else
            {
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

        if(y<=sizeC)
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

SET *intersectionSet(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        int x, y;

        int sizeA, sizeB, sizeC;
        sizeA = A[0];
        sizeB = B[0];
        sizeC = 0;

        for(x=1, y=1; x<sizeA && y<sizeB; )
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

SET *differenceSet(SET A, SET B)
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

bool isSubset(SET A, SET B)
{
    bool isSub;
    int x, y;
    isSub = (A[0] <= B[0]) ? true : false;

    for(x=1; isSub==true && x<=A[0]; x++)
    {
        for(y=1; y<=B[0] && A[x]!=B[y]; y++){}

        isSub = (y <= B[0]) ? true : false; 
    }

    return isSub;
}

int main()
{
    SET A = {4, 1, 4, 5, 9};  
    SET B = {5, 1, 4, 5, 10, 11};

    display(A);
    display(B);

    SET *U = unionSet(A, B);
    // SET *I = intersectionSet(A, B);
    // SET *D = differenceSet(A, B);

    printf("Test = %d\n", isSubset(A, B));

    display(*U);
    // display(*I);
    // display(*D);

    free(U);
    // free(I);
    // free(D);

    return 0;
}