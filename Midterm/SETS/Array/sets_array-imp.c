#include<stdio.h>
#define MAX 5

typedef int SET[MAX];

// SET* Union(SET A, SET B)
// {

// }

void initSet(SET *A);
void PopulateA(SET *A);
void PopulateB(SET *B);
int isMember(SET A, int elem);
void Display(SET A);
SET* Union (SET A, SET B);
SET *Intersection(SET A, SET B);
SET *Difference(SET A, SET B);
void Insert(SET *A, int elem);
void Delete(SET *A, int elem);

SET *Difference(SET A, SET B)
{
    SET *C = (SET*)malloc(sizeof(SET))
    {
        if(C!=NULL)
        {
            int x, y, z = 0;
            for(x=0, y=0; x<MAX && y<MAX; )
            {
                if(A[x] < B[x])
                {
                    x++;
                }
                else if(B[y] < A[x])
                {
                    C[z] = A[x];
                    x++;
                    z++;
                }
                else
                {
                    y++;
                }
            }
        }
    }
}

SET* Intersection(SET A, SET B)
{
    int x, y, z = 0;
    SET *C = (SET*)malloc(sizeof(SET));
    if(C!=NULL)
    {
        for(x=0; x<MAX; )
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
                C[z] = A[x];
                z++;
                x++;
                y++;
            }
        }
    }
    return C;
}

void Display(SET A)
{
    printf("\nSet: ");
    int x;
    for(x=0; x<MAX; x++)
        printf("%d ", A[x]);

    printf("\n\n");
}

int isMember(SET A, int elem)
{
    int x;
    for(x=0; x<MAX && A[x]!=elem; x++){}

    return (A[x]==elem) ? elem : -1;
}

void Insert

int main()
{
    return 0;
}