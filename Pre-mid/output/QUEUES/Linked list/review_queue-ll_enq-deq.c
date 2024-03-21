#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

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

        if(isEmpty(*Q))
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
        Q->Front = Q->Front->link; //delete at beginning

        if(Q->Front==NULL) //if front is null, make rear null too
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

void Populate(Queue *Q)
{
    Enqueue(Q, 'A');
    Enqueue(Q, 'B');
    Enqueue(Q, 'C');
    Enqueue(Q, 'D');
    Enqueue(Q, 'E');
    Enqueue(Q, 'F');
}

int main()
{
    Queue myQueue;
    InitQueue(&myQueue);
    Populate(&myQueue);
    Display(&myQueue);
    return 0;
}