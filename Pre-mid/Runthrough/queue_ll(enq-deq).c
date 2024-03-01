#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}nodeType, *LIST;

typedef struct{
    LIST Front;
    LIST Rear;
}QUEUE;

void initQueue(QUEUE *Q);
void Enqueue(QUEUE *Q, int data);
void Dequeue(QUEUE *Q);
void Print(QUEUE Q);
void Clear(QUEUE *Q);
void Populate(QUEUE *Q);
bool isEmpty(QUEUE Q);
int Front(QUEUE Q);

int Front(QUEUE Q)
{
    return Q.Front->data;
}
void initQueue(QUEUE *Q)
{
    Q->Front = NULL;
    Q->Rear = NULL;
}

bool isEmpty(QUEUE Q)
{
    return (Q.Front==NULL) ? true : false;
}

void Populate(QUEUE *Q)
{
    Enqueue(Q, 1);
    Enqueue(Q, 2);
    Enqueue(Q, 3);
    Enqueue(Q, 4);
}

void Enqueue(QUEUE *Q, int data)
{
    LIST newNode = (LIST)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->data = data;
        newNode->next = NULL;
        if(Q->Front==NULL)
        {
            Q->Front = newNode;
            Q->Rear = newNode;
        }
        else
        {
            Q->Rear = newNode;
            Q->Rear->next = newNode;
        }
    }
}

void Dequeue(QUEUE *Q)
{
    if(Q->Front!=NULL)
    {
        LIST temp;
        temp = Q->Front;
        Q->Front = temp->next;
        free(temp);

        if(Q->Front == NULL)
        {
            Q->Rear = NULL;
        }
    }
}

void Print(QUEUE Q)
{
    QUEUE temp;
    int data;

    initQueue(&temp);
    while(!isEmpty(Q))
    {
        data = Front(Q);
        printf("%d ", data);
        Dequeue(&Q);
        Enqueue(&temp, data);
    }

    while(!isEmpty(temp))
    {
        data = Front(temp);
        Dequeue(&temp);
        Enqueue(&Q, data);
    }
}


int main()
{
    QUEUE marbsEffect;
    initQueue(&marbsEffect);
    Populate(&marbsEffect);
    Print(marbsEffect);
    return 0;   
}