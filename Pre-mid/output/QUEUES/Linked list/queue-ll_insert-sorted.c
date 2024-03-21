#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    char data;
    struct node *link;
}nodeType, *qNode;

typedef struct{
    qNode Front;
    qNode Rear;
}Queue;

void InitQueue(Queue *Q);
bool isEmpty(Queue Q);
void Enqueue(Queue *Q, char data);
void Dequeue(Queue *Q);
char Front(Queue Q);
void Display(Queue *Q);
void InsertSorted(Queue *Q, char data);
void Populate(Queue *Q);

void InitQueue(Queue *Q)
{
    Q->Front = NULL;
    Q->Rear = NULL;
}

bool isEmpty(Queue Q)
{
    return (Q.Front == NULL) ? true : false;
}

void Enqueue(Queue *Q, char data)
{
    qNode newNode = (qNode)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->data = data;
        newNode->link = NULL;

        if(Q->Front==NULL)
        {
            Q->Front = newNode;
        }
        else
        {
            Q->Rear->link = newNode;
        }
        Q->Rear = newNode;
    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        qNode temp;
        temp = Q->Front;

        Q->Front = Q->Front->link;
        
        if(Q->Front==NULL)
        {
            Q->Rear = NULL;
        }

        free(temp);
    }
}

char Front(Queue Q)
{
    return Q.Front->data;
}

void Display(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        Queue tempQueue;
        InitQueue(&tempQueue);

        char ch; 

        printf("\n===\nQueue: ");
        
        while(!isEmpty(*Q))
        {
            ch = Front(*Q);
            printf("%c ", ch);
            Dequeue(Q);
            Enqueue(&tempQueue, ch);
        }

        while(!isEmpty(tempQueue))
        {
            ch = Front(tempQueue);
            Dequeue(&tempQueue);
            Enqueue(Q, ch);
        }
        printf("\n\n");
    }
}

void InsertSorted(Queue *Q, char data)
{
    Queue tempQueue;
    InitQueue(&tempQueue);

    char ch;

    while(!isEmpty(*Q) && Front(*Q) < data)
    {
        ch = Front(*Q);
        Dequeue(Q);
        Enqueue(&tempQueue, ch);
    }

    Enqueue(&tempQueue, data);

    while(!isEmpty(*Q))
    {
        ch = Front(*Q);
        Dequeue(Q);
        Enqueue(&tempQueue, ch);
    }

    while(!isEmpty(tempQueue))
    {
        ch = Front(tempQueue);
        Dequeue(&tempQueue);
        Enqueue(Q, ch);
    }
}

void Populate(Queue *Q)
{
    InsertSorted(Q, 'B');
    InsertSorted(Q, 'Z');
    InsertSorted(Q, 'L');
    InsertSorted(Q, 'A');
    InsertSorted(Q, 'F');
    InsertSorted(Q, 'H');
}

int main()
{
    Queue myQueue;
    InitQueue(&myQueue);
    Populate(&myQueue);
    Display(&myQueue);
    return 0;
}