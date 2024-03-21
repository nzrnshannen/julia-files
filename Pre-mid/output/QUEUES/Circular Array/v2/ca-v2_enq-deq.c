#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    char data[MAX];
    int front;
    int rear;
}Qnode, *Queue;

void InitQueue(Queue *Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);
void Enqueue(Queue *Q, char data);
void Dequeue(Queue *Q);
void Print(Queue Q);
char Front(Queue Q);
void Populate(Queue *Q);

void InitQueue(Queue *Q)
{
    (*Q)->front = -1;
    (*Q)->rear = -1;
}

bool isEmpty(Queue Q)
{
    return (Q->front==-1) ? true : false;
}

bool isFull(Queue Q)
{
    return (Q->front == (Q->rear+1)%MAX) ? true : false;
}

void Enqueue(Queue *Q, char data)
{
    if(!isFull(*Q))
    {
        if(isEmpty(*Q))
        {
            (*Q)->front++;
            (*Q)->rear++;
        }
        else
        {
            (*Q)->rear = ((*Q)->rear+1)%MAX;
        }

        (*Q)->data[(*Q)->rear]= data;
    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        if((*Q)->front==(*Q)->rear)
        {
            (*Q)->front = -1;
            (*Q)->rear = -1;
        }
        else
        {
            (*Q)->front = ((*Q)->front+1)%MAX;
        }
    }
}

void Print(Queue Q)
{
    if(!isEmpty(Q))
    {
        Qnode tempq;
        Queue tempQueue = &tempq;
        InitQueue(&tempQueue);

        char ch;

        printf("\n===\nQueue: ");
        while(!isEmpty(Q))  
        {
            ch = Front(Q);
            printf("%c ", ch);
            Dequeue(&Q);
            Enqueue(&tempQueue, ch);
        }

        while(!isEmpty(tempQueue))
        {
            ch = Front(tempQueue);
            Dequeue(&tempQueue);
            Enqueue(&Q, ch);
        }
        printf("\n\n");
    }
}

char Front(Queue Q)
{
    return Q->data[Q->front];
}

void Populate(Queue *Q)
{
    Enqueue(Q, 'A');
    Enqueue(Q, 'C');
    Enqueue(Q, 'B');
    Enqueue(Q, 'D');
    Enqueue(Q, 'R');
    Enqueue(Q, 'L'); //this shouldn't be included in the queue
}

int main()
{
    Qnode example;
    Queue myQueue = &example;

    InitQueue(&myQueue);

    Populate(&myQueue);
    Print(myQueue);

    return 0;
}