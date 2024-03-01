#include<stdio.h>
#define MAX 5

typedef struct{
    int data[MAX];
    int front;
    int rear;
}Queue;

void initQueue(Queue *Q);
void enqueue(Queue *Q, int data);
void dequeue(Queue *Q);
void display(Queue Q);
void populate(Queue *Q);
int front(Queue Q);

void initQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear = -1;
}

int front(Queue Q)
{
    return Q.data[Q.front];
}

void enqueue(Queue *Q, int data)
{
    if(Q->rear<MAX) //remember, we are not implementing circular array yet
    {   
        if(Q->front==-1 && Q->rear==-1)
        {
            Q->front++;
            Q->rear++;
        }
        else
        {
            Q->rear++;
        }
        Q->data[Q->rear] = data;
    }
}

void dequeue(Queue *Q)
{
    if(Q->front!=-1)
    {
        if(Q->front==Q->rear)
        {
            Q->front = -1;
            Q->rear = -1;
        }
        else
        {
            Q->front++;
        }
    }
}

void display(Queue Q)
{
    if(Q.front!=-1)
    {
        Queue tempQueue;
        initQueue(&tempQueue);

        printf("\n===\nQueue: ");

        while(Q.front!=-1)
        {
            int data;
            data = front(Q);
            enqueue(&tempQueue, data);
            dequeue(&Q);
        }

        while(tempQueue.front!=-1)
        {
            int data;
            data = front(tempQueue);
            printf("%d ", data);
            enqueue(&Q, data);
            dequeue(&tempQueue);
        }

        printf("\n\n");
    }
}

void populate(Queue *Q)
{
    enqueue(Q, 2);
    enqueue(Q, 3);
    enqueue(Q, 5);
    enqueue(Q, 1);
    enqueue(Q, 18);
}

int main()
{
    Queue myQueue;
    initQueue(&myQueue);
    populate(&myQueue);
    display(myQueue);
    return 0;
}