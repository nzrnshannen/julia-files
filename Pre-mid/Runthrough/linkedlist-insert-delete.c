#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    int data;
    struct node *next;
}nodeType, *LIST;

void initList(LIST *L);
void populate(LIST *L);
void insertAtBeginning(LIST *L, int data);
void insertAtEnd(LIST *L, int data);
void insertAtPos(LIST *L, int data, int pos);
void deleteAtEnd(LIST *L);
void deleteAtBeginning(LIST *L);
void deleteAtPos(LIST *L, int pos);
void deleteFirstOccur(LIST *L, int data);
void deleteAllOccur(LIST *L, int data);
void clearList(LIST *L);
int countNodes(LIST L);
bool isEmpty(LIST L);

void displayList(LIST L);

void initList(LIST *L)
{
    *L = NULL;
}

//insert functions
void insertAtBeginning(LIST *L, int data)
{
    LIST newnode = (LIST)malloc(sizeof(nodeType));
    if(newnode!=NULL)
    {
        newnode->data = data;
        newnode->next = *L;
        *L = newnode;
    }
}

void insertAtEnd(LIST *L, int data)
{
    LIST newnode = (LIST)malloc(sizeof(nodeType));
    if(newnode!=NULL)
    {
        newnode->data = data;
        if(isEmpty(*L))
        {
            *L = newnode;
            (*L)->next = NULL;
        }
        else
        {
            LIST *trav;
            for(trav=L;(*trav)!=NULL; trav=&(*trav)->next){}
            *trav = newnode;
            (*trav)->next = NULL;
        }

    }
}

int countNodes(LIST L)
{
    int count=0;
    if(!isEmpty(L))
    {
        LIST trav;
        for(trav=L, count=1; trav!=NULL; trav=trav->next, count++){}

    }

    return count;
}

void insertAtPos(LIST *L, int data, int pos)
{
    if(!isEmpty(*L) && pos>=1 && pos<=countNodes(*L)+1)
    {
        int ctr;
        LIST *trav;
        for(trav=L, ctr=1; *trav!=NULL && ctr<pos; ctr++, trav=&(*trav)->next){}

        LIST newnode = (LIST)malloc(sizeof(nodeType));
        if(newnode!=NULL)
        {
            newnode->data = data;
            newnode->next = *trav;
            *trav = newnode;
        }

        printf("\ntest\n");
    }
}

void deleteAtBeginning(LIST *L)
{
    if(!isEmpty(*L))
    {
        LIST temp;
        temp = *L;
        *L = temp->next;
        free(temp);
    }
}

void deleteAtEnd(LIST *L)
{
    if(!isEmpty(*L))
    {
        LIST temp;
        LIST *trav;
        for(trav=L; (*trav)->next!=NULL; trav=&(*trav)->next){}

        temp = *trav;
        *trav = NULL;
        free(temp);
    }
}

void deleteAtPos(LIST *L, int pos)
{
    if(!isEmpty(*L) && pos<=countNodes(*L) && pos>=1)
    {
        int ctr;
        LIST *trav;
        for(trav=L, ctr=1; *trav!=NULL && ctr<pos; ctr++, trav=&(*trav)->next){}

        if(*trav!=NULL)
        {
            LIST temp;
            temp = *trav;
            *trav = temp->next;
            free(temp);
        }
    }
}

void deleteFirstOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        LIST *trav;
        for(trav=L; *trav!=NULL && (*trav)->data!=data; trav=&(*trav)->next){}

        if(*trav!=NULL)
        {
            LIST temp;
            temp = *trav;
            *trav = temp->next;
            free(temp);
        }
    }
}

void deleteAllOccur(LIST *L, int data)
{
    if(!isEmpty(*L))
    {
        LIST *trav;
        for(trav = L; *trav!=NULL; )
        {
            if((*trav)->data==data)
            {
                LIST temp;
                temp = *trav;
                *trav = temp->next;
                free(temp);

                trav = L;
            }
            else
            {
                trav=&(*trav)->next;
            }
        }
    }
}

bool isEmpty(LIST L)
{
    return (L==NULL) ? true: false;
}

void displayList(LIST L)
{
    if(!isEmpty(L))
    {
        printf("\n===\nList: ");
        LIST trav;
        for(trav=L; trav!=NULL; trav=trav->next)
        {
            printf("%d ", trav->data);
        }

        printf("\n\n");
    }
}

void populate(LIST *L)
{
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 2);
    insertAtEnd(L, 11);
    insertAtPos(L, 2000, 3);
    insertAtBeginning(L, 1);
    insertAtBeginning(L, 1);
}

int main()
{
    LIST myList;
    initList(&myList);

    populate(&myList);
    displayList(myList);

    deleteAllOccur(&myList, 1);
    displayList(myList);
    
    return 0;
}