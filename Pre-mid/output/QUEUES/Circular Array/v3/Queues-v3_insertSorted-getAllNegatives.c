#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX 5

typedef struct{
    int *elemPtr;
    int front;
    int rear;
}Queue;

void initQueue(Queue *Q);
void Enqueue(Queue *Q, int data);
void Dequeue(Queue *Q);
int Front(Queue Q);

bool isEmpty(Queue Q);
bool isFull(Queue Q);

void Display(Queue Q);
void Populate(Queue *Q);

void InsertSorted(Queue *Q, int data);
Queue getAllNegatives(Queue Q);

void initQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear = -1;
    Q->elemPtr = (int*)malloc(sizeof(int) * MAX);
    if(Q->elemPtr==NULL)
    {
        printf("\nMemory allocation failure\n");
        exit(1);
    }
}

void Enqueue(Queue* Q, int data)
{
    if(!isFull(*Q))
    {
        if(isEmpty(*Q))
        {
            Q->front++;
            Q->rear++;
        }
        else
        {
            Q->rear = (Q->rear+1)%MAX;
        }
        Q->elemPtr[Q->rear] = data;
    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        if(Q->front==Q->rear)
        {
            Q->front=-1;
            Q->rear=-1;
        }
        else
        {
            Q->front = (Q->front+1)%MAX; 
        }
    }
}

int Front(Queue Q)
{
    return Q.elemPtr[Q.front];
}

bool isEmpty(Queue Q)
{
    return (Q.front==-1) ? true : false;
}

bool isFull(Queue Q)
{
    return ((Q.rear+1)%MAX == Q.front) ? true : false;
}

void Display(Queue Q)
{
    if(!isEmpty(Q))
    {
        Queue tempQueue;
        initQueue(&tempQueue);

        printf("\n===\nQueue: ");
        while(!isEmpty(Q))
        {
            int data;
            data = Front(Q);
            printf("%d ", data);
            Enqueue(&tempQueue, data);
            Dequeue(&Q);
        }

        while(!isEmpty(tempQueue))
        {
            int data;
            data = Front(tempQueue);
            Enqueue(&Q, data);
            Dequeue(&tempQueue);
        }
    }
}

void Populate(Queue *Q)
{
    InsertSorted(Q, -10);
    InsertSorted(Q, -20);
    InsertSorted(Q, -30);
    InsertSorted(Q, -40);
    InsertSorted(Q, -50);
    InsertSorted(Q, -60); //this should not be in the queue
}

void InsertSorted(Queue *Q, int data)
{
    Queue tempQueue;
    initQueue(&tempQueue);

    while(!isEmpty(*Q) && data > Front(*Q))
    {
        Enqueue(&tempQueue, Front(*Q));
        Dequeue(Q);
    }

    Enqueue(&tempQueue, data);

    while(!isEmpty(*Q))
    {
        Enqueue(&tempQueue, Front(*Q));
        Dequeue(Q);
    }

    while(!isEmpty(tempQueue))
    {
        Enqueue(Q, Front(tempQueue));
        Dequeue(&tempQueue);
    }
}

Queue getAllNegatives(Queue Q)
{
    Queue tempQueue, negaQueue, returnQueue;
    initQueue(&tempQueue);
    initQueue(&negaQueue);
    initQueue(&returnQueue);

    int count = 0;

    while(!isEmpty(Q))
    {
        int data;
        data = Front(Q);

        if(data < 0)
        {
            Enqueue(&negaQueue, data);
            count++;
        }

        Enqueue(&tempQueue, data);
        Dequeue(&Q);
    }

    while(!isEmpty(tempQueue))
    {
        int data;
        data = Front(tempQueue);
        Enqueue(&Q, data);
        Dequeue(&tempQueue);
    }

    Enqueue(&returnQueue, count);

    while(!isEmpty(negaQueue))
    {
        int data;
        data = Front(negaQueue);
        if(negaQueue.front==negaQueue.rear)
        {
            printf("\n\n\t>> Temporary stack is full! Last negative element is: %d <<\n\n", Front(negaQueue));
        }
        Enqueue(&returnQueue, data);
        Dequeue(&negaQueue);
    }

    return returnQueue;
}

int main()
{
    Queue myQueue, negaQueue;
    initQueue(&myQueue);
    Populate(&myQueue);

    Display(myQueue);

    negaQueue = getAllNegatives(myQueue);
    Display(negaQueue);
    return 0;
}