#include<stdio.h>
#define MAX 5

typedef struct{
    int data[MAX];
    int avail;
}*List;

List returnSomeData()
{
    List L;
    L = NULL;

    L->avail = -1;
    return L;
}

int main()
{
    List example = returnSomeData();

    printf("%d", example->avail);

    return 0;
}