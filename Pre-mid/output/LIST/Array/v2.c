#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    char elem[SIZE];
    int count;
}listType, *List;

void initializeList(List L);
void insertElem(List L, char elem);
void deleteAtPos(List L, int pos);
void deleteAllOccur(List L, char elem);
void deleteFirstOccur(List L, char elem);
void populateList(List L);
bool isEmpty(List L);
bool isFull(List L);
bool search(List L, char elem);

char elemAtPos(List L, int pos);

void fullListMsg();
void emptyListMsg();
void displayList(List L);

void insertElem(List L, char elem)
{
    if(isFull(L))
    {
        fullListMsg();
    }
    else
    {
        L->elem[L->count++] = elem;
    }
}

bool isFull(List L)
{
    return (L->count==SIZE) ? true : false;
}

bool isEmpty(List L)
{
    return (L->count==0) ? true : false;
}

bool search(List L, char elem)
{
    int x;
    for(x=0; x<L->count && L->elem[x]!=elem; x++){}

    return (L->elem[x]==elem) ? true : false;
}

void deleteFirstOccur(List L, char elem)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        if(search(L, elem))
        {
            int x;
            for(x=0; x<L->count && L->elem[x]!=elem; x++){}

            if(L->elem[x]==elem)
            {
                int y;
                for(y=x; y<L->count-1; y++)
                {
                    L->elem[y] = L->elem[y+1];
                }
                L->count--;
            }

            printf("\n\n\tSuccessfully deleted element.\n\n");
        }
        else
        {
            printf("\n\n\tElement %c not found!\n\n", elem);
        }
    }
}

void deleteAllOccur(List L, char elem)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else if (!search(L, elem))
    {
        printf("\n\n\tElement does not exists!\n\n");
    }
    else
    {
        int x;
        for(x=0; x<L->count; )
        {
            if(L->elem[x]==elem)
            {
                int y;
                for(y=x; y<L->count-1; y++)
                {
                    L->elem[y] = L->elem[y+1];
                }
                L->count--;
            }
            else
            {
                x++;
            }
        }

        printf("\n\n\tSuccessfully deleted all occurrences of element %c.\n\n", elem);
    }
}

void deleteAtPos(List L, int pos)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else if(pos > L->count || pos <= 0)
    {
        printf("\n >> Invalid position! Position begins at 1 and ends at %d. <<\n\n", L->count);
    }
    else
    {
        int x;
        int retval = L->elem[pos-1];
        for(x=pos-1; x<L->count-1; x++)
        {
            L->elem[x] = L->elem[x+1];
        }
        L->count--;

        printf("\n\n\tSuccessfully deleted %c at position %d.\n\n", retval, pos);
    }
}

void fullListMsg()
{
    printf("\n\n\tList is full!\n\n");
}

void emptyListMsg()
{
    printf("\n\n\tList is empty!\n\n");
}

void initializeList(List L)
{
    L->count=0;
}

void displayList(List L)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n==================\nList: ");
        int x;
        for(x=0; x<L->count; x++)
        {
            printf("%c ", L->elem[x]);
        }
        printf("\n\n");
    }
}

void populateList(List L)
{
    insertElem(L, 'A');
    insertElem(L, 'B');
    insertElem(L, 'A');
    insertElem(L, 'C');
    insertElem(L, 'A');
}

char elemAtPos(List L, int pos)
{
    char retval = '\0';
    if(pos > 0 && pos <= L->count)
    {
        retval = L->elem[pos-1];
    }

    return retval;
}

int main()
{
    listType listOne;
    initializeList(&listOne);
    populateList(&listOne);
    displayList(&listOne);
    // deleteAtPos(&listOne, 5);
    deleteAllOccur(&listOne, 'A');
    displayList(&listOne);

    printf("Element = %c", elemAtPos(&listOne, 0));
    return 0;
}