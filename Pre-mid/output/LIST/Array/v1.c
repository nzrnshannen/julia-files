#include<stdio.h>
#include<stdbool.h>

#define SIZE 5

typedef struct{
    char elem[SIZE];
    int count;
}LIST;

void initializeList(LIST *L);
void insertUnique(LIST *L, char elem);

void deleteElem(LIST *L, char elem);
// void deleteAllOccur(LIST *L, char elem);

bool isEmpty(LIST L);
bool isFull(LIST L);
bool isPresent(LIST L, char elem);

void emptyListMsg();
void fullListMsg();
void notPresentMsg(char elem);

int searchElem(LIST L, char elem);

void displayList(LIST L);

void initializeList(LIST *L)
{
    L->count = 0;
}

void insertUnique(LIST *L, char elem)
{
    if(isFull(*L))
    {
        fullListMsg();
    }
    else
    {
        if(isPresent(*L, elem))
        {
            printf("\nElement [%c] already exists!\n", elem);
        }
        else
        {
            int x, y;
            
            for(x=0; x<L->count && L->elem[x] < elem; x++){}

            for(y=L->count; y>x; y--)
            {
                L->elem[y] = L->elem[y-1];
            }

            L->elem[y] = elem;

            L->count++;
        }
    }
}

void deleteElem(LIST *L, char elem)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        int retval = searchElem(*L, elem);

        if(retval!=-1)
        {
            int x;
            for(x=retval; x<L->count; x++)
            {
                L->elem[x] = L->elem[x+1];
            }
            
            L->count--;
        }
        else
        {
            notPresentMsg(elem);
        }
    }
}


bool isEmpty(LIST L)
{
    return (L.count==0);
}

bool isFull(LIST L)
{
    return (L.count==SIZE);
}

void emptyListMsg()
{
    printf("\n\n\tList is empty!\n\n");
}

void fullListMsg()
{
    printf("\n\n\tList is full!\n\n");
}

void notPresentMsg(char elem)
{
    printf("\n\n\tElement [%c] does not exist!\n\n", elem);
}

void displayList(LIST L)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n=====\nList: ");
        int x;
        for(x=0; x<L.count; x++)
        {
            printf("%c ", L.elem[x]);
        }

        printf("\n");

    }
}

bool isPresent(LIST L, char elem)
{
    int x;
    
    for(x=0; x<L.count && L.elem[x]!=elem; x++){}

    return (L.elem[x]==elem) ? true : false;
}

int searchElem(LIST L, char elem)
{
    int x;
    for(x=0; x<L.count && L.elem[x]!=elem; x++){}

    return (L.elem[x]==elem) ? x : -1;
}

//CODE BELOW NOT APPLICABLE as we're doing insertUnique
// void deleteAllOccur(LIST *L, char elem)
// {
//     if(isEmpty(*L))
//     {
//         emptyListMsg();
//     }
//     else
//     {
//         if(isPresent(*L, elem))
//         {
//             notPresentMsg(elem);
//         }
//         else
//         {
//             int x;
//             for(x=0; x<L->count; )
//             {
//                 if(L->elem[x]==elem)
//                 {
//                     int y;
//                     for(y=x; y<L->count-1; y++)
//                     {
//                         L->elem[y] = L->elem[y+1];
//                     }
//                     L->count--;
//                 }
//             }
//         }
//     }
// }

int main()
{
    LIST list_one;
    initializeList(&list_one);
    insertUnique(&list_one, 'A');
    insertUnique(&list_one, 'A');
    insertUnique(&list_one, 'C');
    insertUnique(&list_one, 'D');
    insertUnique(&list_one, 'E');
    insertUnique(&list_one, 'B');
    displayList(list_one);
    deleteElem(&list_one, 'A');
    insertUnique(&list_one, 'Z');
    insertUnique(&list_one, 'J');
    displayList(list_one);

    return 0;
}