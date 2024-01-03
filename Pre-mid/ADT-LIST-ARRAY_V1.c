#include<stdio.h>
#include<stdbool.h>
#define SIZE 10

typedef enum {FALSE, TRUE} Boolean;
typedef struct{
    char elements[SIZE];
    int count;
}List;

void initList(List *L)
{
    L->count=0;
}

List initList2(List L)
{
    L.count = 0;
    return L;
}

int findElem(List L, int elem)
{
    int ndx = -1;
    int x;
    for(x=0; x<L.count && L.elements[x]!=elem; x++){}

    if(L.elements[x]==elem)
    {
        ndx = x;
    }

    return ndx;
}

void insertFirst(List *L, int elem)
{
    if(L->count!=SIZE)
    {
        int x;
        for(x=L->count; x>0; x--)
        {
            L->elements[x] = L->elements[x-1];
        }
        L->elements[x] = elem;
        L->count++;
    }
}

Boolean deleteElem(List *L, int elem)
{
    Boolean retval = FALSE;
    int x, y;
    
    for(x=0; x<L->count;)
    {
        if(L->elements[x]==elem)
        {
            for(y=x; y<L->count-1; y++)
            {
                L->elements[y] = L->elements[y+1];
            }
            L->count--;
            retval = TRUE;
        }
        else
        {
            x++;
        }
    }

    return retval;
}

void printList(List L)
{
    int x;
    printf("\n===\nList: ");
    for(x=0; x<L.count; x++)
    {
        printf("%d ", L.elements[x]);
    }
    printf("\n\n");
}

int main()
{
    List listA;
    initList(&listA);
    insertFirst(&listA, 3);
    insertFirst(&listA, 3);
    insertFirst(&listA, 3);
    printList(listA);
    // printf("\nDelete %d", deleteElem(&listA, 5));
    // printf("\nSearch: %d", findElem(listA, 1));
    printf("\ntest: %d", deleteElem(&listA, 3));
    printList(listA);
    return 0;
}