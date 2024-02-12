#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int* getAllNegative(int size, int Arr[])
{
    int x, y = 1;
    int temp[size+1];

    for(x=0; x<size; x++)
    {
        if(Arr[x] < 0)
        {
            temp[y] = Arr[x];
            y++;
        }

    }

    temp[0] = y-1;

    int *new = (int*)malloc(sizeof(int) * y);
    if(new!=NULL)
    {
        memcpy(new, temp, y * sizeof(int));
    }

    return new;
}

void display(int Arr[], int size)
{
    int x;
    printf("\n====\n");
    for(x=0; x<size; x++)
        printf("%d ", Arr[x]);
    
    printf("\n\n");
}

int main()
{
    int A[] = {2, 1, 3, 4};
    int size = sizeof(A)/sizeof(A[0]);
    int *B = getAllNegative(size, A);
    display(B, B[0]+1);

}