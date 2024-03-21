#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX 10

typedef int SET[MAX];

void Display(SET A);
SET* UnionSet(SET A, SET B); 
SET *IntersectionSet(SET A, SET B);
SET *DifferenceSet(SET A, SET B);
bool isSuperset(SET A, SET B); //I tend to make this in a different C file because why not hehe

//index 0 will contain the number of elements in a set, first element will be on index 1 

void Display(SET A)
{
    if(A[0] == 0)
    {
        printf("\n\t>> Empty set <<\n\n");
    }
    else
    {
        int x;
        printf("\n===\nSet: ");
        for(x=1; x<=A[0]; x++)
        {
            printf(" %d ", A[x]);
        }

        printf("\n");
    }
}

SET* UnionSet(SET A, SET B)
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

SET* IntersectionSet(SET A, SET B)
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

SET* DifferenceSet(SET A, SET B)
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

bool isSuperset(SET B, SET A)
{
    bool isSuper;

    int x, y;

    isSuper = (B[0] >= A[0]) ? true : false;

    for(x=1; isSuper==true && x<=A[0]; x++)
    {
        for(y=1; y<=B[0] && A[x] != B[y]; y++){}

        isSuper = (y<=B[0]) ? true : false;
    }
    

    return isSuper;
}

int main()
{
    SET A = {4, 1, 4, 5, 9};
    SET B = {6, 1, 3, 4, 5, 6, 9};
    
    SET *U = UnionSet(A, B);
    SET *I = IntersectionSet(A, B);
    SET *D = DifferenceSet(A, B);

    Display(*U);
    Display(*I);
    Display(*D);

    printf("Test = %d\n", isSuperset(B, A)); //check if B is superset of A
    free(U);
    free(I);
    free(D);

    return 0;
}

