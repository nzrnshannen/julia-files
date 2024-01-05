#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 5 //for testing purposes

typedef struct{
    char *elemPtr;
    int count;
}listType, *List;

void initializeList(List *A);
bool isEmpty(List A);
bool isFull(List A);
bool isPresent(List A, char elem);
int searchElem(List A, char elem); //returns index
void addElem(List *A, char elem);
void addElemAtPos(List *A, char elem, int pos);
void deleteFirstOccur(List *A, char elem);
void deleteAllOccur(List *A, char elem);
void deleteAtPos(List *A, int pos);
void shrinkList(List *A, int init_cap);
void printList(List A);
void populate(List *A);
void clearList(List *A);

void initializeList(List *A)
{
    (*A)->count = 0;
    (*A)->elemPtr = (char*)malloc(sizeof(char) * SIZE);
    if((*A)->elemPtr==NULL)
    {
        printf("\nMemory allocation failure");
        exit(1);
    }
}

bool isEmpty(List A)
{
    return (A->count==0) ? true : false;
}

bool isFull(List A)
{
    return (A->count==SIZE) ? true : false;
}

bool isPresent(List A, char elem)
{
    int x;
    for(x=0; x<A->count && A->elemPtr[x]!=elem; x++){}

    return (A->elemPtr[x]==elem) ? true : false;
}

int searchElem(List A, char elem)
{
    int x;
    for(x=0; x<A->count && A->elemPtr[x]!=elem; x++){}

    return (A->elemPtr[x]==elem) ? x : -1;
}

void addElem(List *A, char elem)
{
    if((*A)->count==SIZE)
    {
        printf("\n\tList already full! Reallocating...\n\n");
        int init_cap = (*A)->count;
        (*A)->elemPtr = (char*)realloc((*A)->elemPtr, sizeof(char) * (init_cap + 1));
        if((*A)->elemPtr==NULL)
        {
            printf("\nMemory allocation failure");
            exit(1);
        }
    }

    (*A)->elemPtr[(*A)->count++] = elem;
    printf("\n\t>> Successfully inserted character %c. <<\n\n", elem);
}

void addElemAtPos(List *A, char elem, int pos)
{
    if(pos<=0 || pos > (*A)->count+1)
    {
        printf("\nInvalid position! Position starts at 1 and ends with %d.\n", (*A)->count);
    }
    else if(pos==(*A)->count+1)
    {
        addElem(A, elem);
    }
    else
    {
        if((*A)->count==SIZE)
        {
            int init_cap = (*A)->count;
            (*A)->elemPtr = (char*)realloc((*A)->elemPtr, sizeof(char) * (init_cap + 1));
            if((*A)->elemPtr==NULL)
            {
                printf("\nMemory allocation failure\n");
                exit(1);
            }
        }

        int x, y;
        for(x=0; x<pos-1; x++){}

        for(y=(*A)->count; y>x; y--)
        {
            (*A)->elemPtr[y] = (*A)->elemPtr[y-1];
        }
        (*A)->elemPtr[y] = elem;
        (*A)->count++;
        printf("\n\t>> Successfully inserted character %c. <<\n\n", elem);
    }
}

void deleteFirstOccur(List *A, char elem)
{
    int retval = searchElem(*A, elem);
    if(retval!=-1)
    {
        int x, init_cap;
        init_cap = (*A)->count;
        for(x=retval; x<(*A)->count-1; x++)
        {
            (*A)->elemPtr[x] = (*A)->elemPtr[x+1];
        }
        (*A)->count--;
        printf("\n\tSuccessfully removed character %c at index %d.\n\n", elem, retval);
        shrinkList(A, init_cap);
    }
}

void deleteAllOccur(List *A, char elem)
{
    if(!isPresent(*A, elem))
    {
        printf("\n\tCharacter %c not present!\n\n", elem);
    }
    else
    {
        int x, init_cap;
        init_cap = (*A)->count;
        for(x=0; x<(*A)->count; )
        {
            if((*A)->elemPtr[x]==elem)
            {   
                int y;
                for(y=x; y<(*A)->count-1; y++)
                {
                    (*A)->elemPtr[y] = (*A)->elemPtr[y+1];
                }
                (*A)->count--;
            }
            else
            {
                x++;
            }
        }
        printf("\n\tSuccessfully deleted all occurrences of character %c.\n\n", elem);
        shrinkList(A, init_cap);
    }
}

void deleteAtPos(List *A, int pos)
{
    if(pos<=0 || pos > (*A)->count)
    {
        printf("\nInvalid position! Position starts at 1 and ends with %d.\n", (*A)->count);
    }
    else
    {
        int x, init_cap;
        init_cap = (*A)->count;
        x = pos-1;
        int retval = (*A)->elemPtr[x];
        for(; x<(*A)->count-1; x++)
        {
            (*A)->elemPtr[x] = (*A)->elemPtr[x+1];
        }
        (*A)->count--;
        shrinkList(A, init_cap);


        printf("\n\tSuccessfully removed character %c at position %d.\n\n", retval, pos);
    }
}

void shrinkList(List *A, int init_cap)
{
    if(init_cap > SIZE && (*A)->count<init_cap)
    {
        printf("\n******\nShrinking the size...\n******\n\n");
        (*A)->elemPtr = (char*)realloc((*A)->elemPtr, sizeof(listType) * (*A)->count);
        if((*A)->elemPtr==NULL)
        {
            printf("\nMemory allocation failure.\n");
            exit(1);
        }
    }
}

void printList(List A)
{
    if(isEmpty(A))
    {
        printf("\n\tEmpty list!\n\n");
    }
    else
    {
        int x;
        printf("\n=========\nList: ");
        for(x=0; x<A->count; x++)
        {
            printf("%c ", A->elemPtr[x]);
        }
        printf("\n\n");
    }
}

void clearList(List *A)
{
    free((*A)->elemPtr);
    (*A)->elemPtr=NULL;
}

void populate(List *A)
{
    addElem(A, 'A');
    addElem(A, 'A');
    addElem(A, 'A');
    addElem(A, 'D');
    addElem(A, 'A');
    addElem(A, 'F');
    printf("\nCharacter count = %d\n\n", (*A)->count);
}
int main()
{
    listType listOne;
    List L = &listOne;
    initializeList(&L);
    populate(&L);
    deleteAtPos(&L, 6);
    printList(L);
    printf("\nCharacter count = %d\n\n", L->count);
    clearList(&L);
    return 0;
}