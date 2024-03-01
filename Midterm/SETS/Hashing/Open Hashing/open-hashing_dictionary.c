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
void insert(Dictionary D, int data);
void delete(Dictionary D, int data);
int hash(int data);
void populate(Dictionary D);
void display(Dictionary D);
void delete(Dictionary D, int data);
bool isMember(Dictionary D, int data);
void clearDict(Dictionary D);

void initDict(Dictionary D)
{
    int x;
    for(x=0; x<MAX; x++)
        D[x] = NULL;
}

int hash(int data)
{
    return data%MAX;
}

void insert(Dictionary D, int data)
{
    int key;
    key = hash(data);
    
    LIST* trav;
    for(trav=&D[key]; *trav!=NULL && (*trav)->data<data; trav=&(*trav)->link){}

    if(*trav==NULL || data != (*trav)->data)
    {
        LIST newNode = (LIST)malloc(sizeof(nodeType));
        if(newNode!=NULL)
        {
            newNode->data = data;
            newNode->link = *trav;
            *trav = newNode;
        }
    }
}

void display(Dictionary D)
{
    int x;
    LIST trav;
    
    for(x=0; x<MAX; x++)
    {
        printf("Group %d ---> ", x);
        for(trav=D[x]; trav!=NULL; trav=trav->link)
        {
            printf("%d ", trav->data);
        }
        printf("\n");
    }
}

void populate(Dictionary D)
{
    insert(D, 0);
    insert(D, 13);
    insert(D, 5);
    insert(D, 19);
    insert(D, 4);
    insert(D, 29);
    insert(D, 59);
    insert(D, 39);
}

void delete(Dictionary D, int data)
{
    int key;
    key = hash(data);

    LIST *trav;
    for(trav=&D[key]; *trav!=NULL && (*trav)->data!=data; trav=&(*trav)->link){}

    if(*trav!=NULL && (*trav)->data == data)
    {
        LIST temp;
        temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}

bool isMember(Dictionary D, int data)
{
    int key;
    LIST trav;
    key = hash(data);

    for(trav=D[key]; trav!=NULL && trav->data!=data; trav=trav->link){}

    return (trav!=NULL && trav->data==data) ? true : false;
}

// void clearDict(Dictionary D)
// {
//     int x;
//     for(x=0; x<MAX; x++)
//     {
//         LIST *trav;
//         trav = D[x];
//         while(*trav!=NULL)
//         {
//             LIST temp;
//             temp = D[x];

//         }
//     }
// }
int main()
{
    Dictionary myDictionary;
    initDict(myDictionary);
    populate(myDictionary);
    display(myDictionary);
    return 0;
}