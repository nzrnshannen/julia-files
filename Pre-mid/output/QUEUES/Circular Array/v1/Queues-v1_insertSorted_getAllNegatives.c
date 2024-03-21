
#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    int data[MAX];
    int front;
    int rear;
}Queue;

void InitQueue(Queue *Q);
void Populate(Queue *Q);
void Display(Queue Q);
void insertSorted(Queue *Q, int data); //insert unique
void Enqueue(Queue *Q, int data);
void Dequeue(Queue *Q);
int Front(Queue Q);
Queue getAllNegatives(Queue Q);

bool isEmpty(Queue Q);
bool isFull(Queue Q);

void InitQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear = -1;
}

void Populate(Queue *Q)
{
    insertSorted(Q, -11);
    insertSorted(Q, -9);
    insertSorted(Q, -7);
    insertSorted(Q, -10);
    insertSorted(Q, -18);

    Display(*Q);
    insertSorted(Q, 20); //this should not be included
}

void Display(Queue Q)
{
    if(!isEmpty(Q))
    {
        Queue tempQueue;
        InitQueue(&tempQueue);

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
            Enqueue(&Q, Front(tempQueue));
            Dequeue(&tempQueue);
        }

        printf("\n\n");
    }
    else
    {
        printf("\n\t>> Empty queue! <<\n");
    }
}

void insertSorted(Queue *Q, int data)
{
    Queue tempQueue;
    InitQueue(&tempQueue);

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
        int elem;
        elem = Front(tempQueue);
        Enqueue(Q, elem);
        Dequeue(&tempQueue);
    }
}

void Enqueue(Queue *Q, int data)
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
        Q->data[Q->rear] = data;

    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        if(Q->front==Q->rear)
        {
            Q->front = -1;
            Q->rear = -1;
        }
        else
        {
            Q->front = (Q->front+1)%MAX;
        }
    }
}

int Front(Queue Q)
{
    return Q.data[Q.front];
}

bool isEmpty(Queue Q)
{
    return (Q.front==-1) ? true : false;
}

bool isFull(Queue Q)
{
    return ((Q.rear+1)%MAX == Q.front) ? true : false;
}

Queue getAllNegatives(Queue Q)
{
    int count=0;
    Queue tempQueue, negaQueue, returnQueue;
    InitQueue(&tempQueue);
    InitQueue(&negaQueue);
    InitQueue(&returnQueue);

    while(!isEmpty(Q))
    {
        int data;
        data = Front(Q);

        if(data < 0)
        {
            count++;
            Enqueue(&negaQueue, data);
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

        if(isFull(returnQueue))
        {
            printf("\n\t>> Temporary queue is full! Last negative element is: %d <<\n", data);
        }
        
        Enqueue(&returnQueue, data);
        Dequeue(&negaQueue);
    }

    return returnQueue;
}

int main()
{
    Queue myQueue;
    InitQueue(&myQueue);
    Populate(&myQueue);
    Display(myQueue);

    Queue negaQueue = getAllNegatives(myQueue);
    Display(negaQueue);
    return 0;
}