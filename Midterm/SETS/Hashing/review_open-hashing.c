#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX 10

typedef struct node{
    int data;
    struct node *link;
}nodeType, *LIST;

typedef LIST Dictionary[MAX];

void initDict(Dictionary D);
void insert(Dictionary D, int elem);
void delete(Dictionary D, int elem);
int hash(int elem);
void display(Dictionary D);
bool isMember(Dictionary D, int elem);

void initDict(Dictionary D)
{
    int x;
    for(x=0; x<MAX; x++)
    {
        D[x] = NULL;
    }
}

void insert(Dictionary D, int elem)
{
    int key = hash(elem); //determines the location of your element
    LIST *trav;

    for(trav=&D[key]; *trav!=NULL && (*trav)->data<elem; trav=&(*trav)->link){}

    if(*trav==NULL || (*trav)->data!=elem)
    {
        LIST newNode;
        newNode = (LIST)malloc(sizeof(nodeType));
        if(newNode!=NULL)
        {
            newNode->data = elem;
            newNode->link = *trav;
            *trav = newNode;
        }
    }
}

void delete(Dictionary D, int elem)
{
    int key = hash(elem);
    LIST *trav;

    for(trav = &D[key]; *trav!=NULL && (*trav)->data < elem; trav=&(*trav)->link){}

    if(*trav!=NULL && (*trav)->data == elem)
    {
        LIST temp;
        temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}

int hash(int elem)
{
    return elem%MAX;
}

void display(Dictionary D)
{
    int x;
    printf("\n===\nOPEN HASHING\n");
    for(x=0; x<MAX; x++)
    {
        LIST trav;
        printf("Group %d: ", x);
        for(trav=D[x]; trav!=NULL; trav=trav->link)
        {
            printf("--> %d ", trav->data);
        }
        printf("\n");
    }
}

void populate(Dictionary D)
{
    insert(D, 1);
    insert(D, 0);
    insert(D, 20);
    insert(D, 21);
    insert(D, 9);
    insert(D, 10);
    insert(D, 95);
    insert(D, 50);
}

int main()
{
    Dictionary myDict;
    initDict(myDict);
    populate(myDict);
    display(myDict);
    return 0;
}