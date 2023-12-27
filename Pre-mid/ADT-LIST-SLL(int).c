/*===============================================
Created by: Shannen T. Nazareno
Date: 12/27/2023
================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define NULL_NO -9999

typedef struct node{
    int elem;
    struct node *link;
}ctype, *LIST;

void initList(LIST *L);
void displayList(LIST L);

void insertAtBeginning(LIST *L, int x);
void insertAtEnd(LIST *L, int x);
void insertAtPos(LIST *L, int x, int pos);
void populate(LIST *L);
int countNodes(LIST L);

void deleteAtBeginning(LIST *L);
void deleteAtEnd(LIST *L);
void deleteAtPos(LIST *L, int pos);
void deleteFirstOccur(LIST *L, int elem);
void deleteAllOccur(LIST *L, int elem);
void clearList(LIST *L);

bool isEmpty(LIST L);
bool isPresent(LIST L, int elem);

void emptyListMsg();
void invalidPosMsg();
void noElemPresent(int elem);

int getFirst(LIST L);
int getLast(LIST L);
int getElemAtPos(LIST L, int pos);

void concatenate(LIST *A, LIST *B);

bool isEmpty(LIST L)
{
    return (L==NULL);
}

bool isPresent(LIST L, int searchElem)
{
    LIST trav;
    for(trav=L; trav!=NULL && trav->elem!=searchElem; trav=trav->link){}

    return (trav!=NULL && trav->elem==searchElem);
}

void initList(LIST *L)
{
    *L = NULL;
}

int countNodes(LIST L)
{
    LIST trav;
    int c;
    for(trav=L, c=0; trav!=NULL; trav=trav->link, c++){}

    return c;
}

void displayList(LIST L)
{
    if(L!=NULL)
    {
        LIST temp;

        printf("\n=====\nList: ");
        for(temp=L; temp!=NULL; temp=temp->link)
        {
            printf("%d ", temp->elem);
        }
        printf("\n\n");
    }
    else
    {
        printf("\n\n\tList is empty!\n\n");
    }
}

void insertAtBeginning(LIST *L, int x)
{
    LIST newNode = (LIST)malloc(sizeof(ctype));
    if(newNode==NULL)
    {
        printf("Memory allocation failure");
        exit(1);
    }
    else
    {
        newNode->elem = x;
        newNode->link = *L;
        *L = newNode;
    }
}

void insertAtEnd(LIST *L, int x)
{
    LIST newNode = (LIST)malloc(sizeof(ctype));
    if(newNode==NULL)
    {
        printf("Memory allocation failure");
        exit(1);
    }
    else
    {
        newNode->elem = x;
        newNode->link = NULL;

        LIST temp;

        for(temp=*L; temp->link!=NULL; temp=temp->link){}

        temp->link = newNode;
    }
}

void insertAtPos(LIST *L, int x, int pos)
{
    LIST trav;
    int n;
    for(trav=*L, n=0; trav!=NULL; trav=trav->link, n++){}
    if(pos==1)
    {
        insertAtBeginning(L, x);
    }
    else if(pos==n+1)
    {
        insertAtEnd(L, x);
    }
    else if(pos>1)
    {
        int i=1;
        LIST* trav;
        for(trav=L; i<pos && *trav!=NULL; trav=&(*trav)->link, i++){}  

        LIST newNode = (LIST)malloc(sizeof(ctype));
        if(newNode==NULL)
        {
            printf("Memory allocation failure");
            exit(1);
        }
        else
        {
            newNode->elem = x;
            newNode->link = *trav;
            *trav = newNode;
        }
    }
    else
    {
        printf("\n\n\tInvalid position!\n\n");
    }
}

void populate(LIST *L)
{
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 2);
    insertAtEnd(L, 5);
    insertAtEnd(L, 9);
    insertAtBeginning(L, 3);
    insertAtPos(L, 3, 2);
    insertAtPos(L, 3, 2);
    insertAtPos(L, 666, 7);
    insertAtPos(L, 3, 9);
}

void emptyListMsg()
{
    printf("\n\tList is empty!\n\n");
}

void invalidPosMsg()
{
    printf("\n\tInvalid position!\n\n");
}

void deleteAtBeginning(LIST *L)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        LIST temp;
        temp =  *L;
        *L = (*L)->link;
        free(temp);
    }
}

void deleteAtEnd(LIST *L)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        LIST *trav, temp;
        for(trav=L; (*trav)->link!=NULL; trav=&(*trav)->link){}

        temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}

void deleteAtPos(LIST *L, int pos)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else if(countNodes(*L) < pos || pos < 0)
    {
        invalidPosMsg();
    }
    else
    {
        int n = countNodes(*L);
        if(pos==1)
        {
            deleteAtBeginning(L);
        }
        else if(pos==n)
        {
            deleteAtEnd(L);
        }
        else
        {
            int ctr;
            LIST *trav, temp;
            for(trav=L, ctr=1; (*trav)!=NULL && ctr < pos; trav=&(*trav)->link, ctr++){}

            temp = *trav;
            *trav = temp->link;
            free(temp);
        }
    }
}

int getFirst(LIST L)
{
    return (L!=NULL) ? L->elem : NULL_NO;
}

int getLast(LIST L)
{
    LIST trav;
    for(trav=L; trav!=NULL && trav->link!=NULL; trav=trav->link){}

    return (trav!=NULL) ? trav->elem : NULL_NO; 
}

int getElemAtPos(LIST L, int pos)
{
    LIST trav = L;
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else if(!(countNodes(L)>=pos && pos > 0))
    {
        invalidPosMsg();
    }
    else
    {
        int ctr;
        for(trav=L, ctr=1; trav!=NULL && ctr<pos; ctr++, trav=trav->link){}
    }

    return (trav!=NULL && (countNodes(L) >= pos && pos > 0)) ? trav->elem : NULL_NO;
}

void deleteFirstOccur(LIST *L, int elem)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        LIST *trav;
        for(trav=L; (*trav)->link!=NULL && elem!=(*trav)->elem; trav=&(*trav)->link){}

        if((*trav)->link==NULL && elem!=(*trav)->elem)
        {
            noElemPresent(elem);
        }
        else
        {
            if(trav==L)
            {
                deleteAtBeginning(L);
            }
            else
            {
                LIST temp;
                temp = *trav;
                *trav = temp->link;
                free(temp);
            }

            printf("\n\n\tSuccessfully deleted element %d.\n\n", elem);
        }
    }
}

void deleteAllOccur(LIST *L, int elem)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        if(!(isPresent(*L, elem)))
        {
            noElemPresent(elem);
        }
        else
        {
            LIST *trav;
            for(trav=L; (*trav)!=NULL;)
            {
                if((*trav)->elem==elem)
                {
                    if(trav==L)
                    {
                        deleteAtBeginning(L);
                    }
                    else
                    {
                        LIST temp;
                        temp = *trav;
                        *trav = temp->link;
                        free(temp);
                    }
                    trav=L;
                }
                else
                {
                    trav=&(*trav)->link;
                }
            }

            printf("\n\n\tSuccessfully deleted all occurrences of element %d.\n\n", elem);

        }
    }
}

void noElemPresent(int elem)
{
    printf("\n\n\t*************************\n\tElement %d cannot be found!\n\n", elem);
}

void clearList(LIST *L)
{
    while(*L!=NULL)
    {
        LIST temp;
        temp = *L;
        *L = (*L)->link;
        free(temp);
    }

    printf("\n\n\tList cleared.\n\n");

}

void concatenate(LIST *A, LIST *B)
{
    if(isEmpty(*A) || isEmpty(*B))
    {
        emptyListMsg();
    }
    else
    {
        LIST *trav;
        for(trav=A; (*trav)->link!=NULL; trav = &(*trav)->link){}
       (*trav)->link = *B; 

        printf("\n\t********************************\n\tSuccessfully concatenated lists!\n\n");

        *B = NULL;
    }
}

int main()
{
    LIST A;
    LIST B;
    initList(&A);
    initList(&B);
    populate(&A);
    insertAtBeginning(&B, 1);
    insertAtBeginning(&B, 2);
    insertAtBeginning(&B, 3);
    printf("\nNumber of nodes: %d\n", countNodes(A));

    // deleteAtBeginning(&A);
    // deleteAtEnd(&A);
    // deleteAtEnd(&A);
    // deleteAtPos(&A, 5);
    // deleteFirstOccur(&A, 666);

    deleteAllOccur(&A, 3);

    displayList(A);
    displayList(B);

    concatenate(&A, &B);
    displayList(A);

    clearList(&A);
    return 0;
}