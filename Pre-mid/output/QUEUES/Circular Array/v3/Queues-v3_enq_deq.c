#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

void initQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear = -1;

    Q->elemPtr = (int*)malloc(sizeof(int) * MAX);
    if(Q->elemPtr==NULL)
    {
        printf("\nMemory allocation failure!\n");
        exit(1);
    }
}

bool isEmpty(Queue Q)
{
    return (Q.front==-1) ? true : false;
}

bool isFull(Queue Q)
{
    return ((Q.rear+1)%MAX == Q.front) ? true: false; 
}

int Front(Queue Q)
{
    return Q.elemPtr[Q.front];
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        if(Q->front==Q->rear)
        {
            Q->front=-1;
            Q->rear= -1;
        }
        else
        {
            Q->front = (Q->front+1)%MAX;
        }
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
        Q->elemPtr[Q->rear] = data;
    }
}

void Display(Queue Q)
{
    if(!isEmpty(Q))
    {
        printf("\n===\nQueue: ");

        Queue tempQueue;
        initQueue(&tempQueue);

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
        free(tempQueue.elemPtr);
        printf("\n\n");
    }
    else
    {
        printf("\n\tEmpty queue!\n\n");
    }
}

void Populate(Queue *Q)
{
    Enqueue(Q, 1);
    Enqueue(Q, 2);
    Enqueue(Q, 3);
    Enqueue(Q, 4);
    Enqueue(Q, 5);
    Enqueue(Q, 6);
}

int main()
{
    Queue myQueue;
    initQueue(&myQueue);
    Populate(&myQueue);
    Display(myQueue);

    free(myQueue.elemPtr);
    return 0;
}