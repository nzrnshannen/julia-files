#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    int data[MAX];
    int front;
    int rear;
}Queue;

void InitQueue(Queue *Q);
void Enqueue(Queue *Q, int data);
void Dequeue(Queue *Q);
int Front(Queue Q);
void Populate(Queue *Q);
void Display(Queue Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);

void InitQueue(Queue *Q)
{
    //set queue to be empty
    Q->front = -1;
    Q->rear = -1;
}

bool isEmpty(Queue Q)
{
    return (Q.front==-1)? true : false;
}

bool isFull(Queue Q)
{
    return ((Q.rear+1)%MAX == Q.front) ? true : false;
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
            Q->rear  = -1;
        }
        else
        {
            Q->front = (Q->front + 1)%MAX;
        }
    }
}

int Front(Queue Q)
{
    return Q.data[Q.front]; 
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
        printf("\n\tEmpty queue!\n\n");
    }
}

void Populate(Queue *Q)
{
    Enqueue(Q, 10);
    Enqueue(Q, 20);
    Enqueue(Q, 30);
    Enqueue(Q, 40);
    Enqueue(Q, 50);
    Enqueue(Q, 60);
}

int main()
{
    Queue myQueue;

    InitQueue(&myQueue);

    Populate(&myQueue);

    Display(myQueue);


    Dequeue(&myQueue);
    Display(myQueue);

    Dequeue(&myQueue);
    Dequeue(&myQueue);
    Dequeue(&myQueue);
    Dequeue(&myQueue);

    Display(myQueue);

    return 0;
}