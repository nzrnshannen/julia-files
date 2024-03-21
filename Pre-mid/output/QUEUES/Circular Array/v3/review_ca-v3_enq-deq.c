#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX 5

typedef struct{
    char *dataPtr;
    int Front;
    int Rear;
}Queue;

void InitQueue(Queue *Q);
bool isFull(Queue Q);
bool isEmpty(Queue Q);
void Enqueue(Queue *Q, char data);
void Dequeue(Queue *Q);
void Display(Queue Q);
char Front(Queue Q);
void Populate(Queue *Q);

void InitQueue(Queue *Q)
{
    Q->Front = -1;
    Q->Rear = -1;
    Q->dataPtr = (char*)malloc(sizeof(char) * MAX);
    if(Q->dataPtr==NULL)
    {
        perror("Memory allocation failure");
        exit(1);
    }
}

bool isFull(Queue Q)
{
    return (Q.Front == (Q.Rear+1)%MAX) ? true : false;
}

bool isEmpty(Queue Q)
{
    return (Q.Front==-1) ? true : false;
}

void Enqueue(Queue *Q, char data)
{
    if(!isFull(*Q))
    {
        if(Q->Front==-1)
        {
            Q->Front++;
            Q->Rear++;
        }
        else
        {
            Q->Rear = (Q->Rear+1)%MAX;
        }
        Q->dataPtr[Q->Rear] = data;
    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        if(Q->Front==Q->Rear)
        {
            Q->Front =-1;
            Q->Rear = -1;
        }
        else
        {
            Q->Front = (Q->Front+1)%MAX;
        }
    }
}

char Front(Queue Q)
{
    return Q.dataPtr[Q.Front];
}

void Display(Queue Q)
{
    if(!isEmpty(Q))
    {
        Queue tempQueue;
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

void Populate(Queue *Q)
{
    Enqueue(Q, 'A');
    Enqueue(Q, 'B');
    Enqueue(Q, 'C');
    Enqueue(Q, 'D');
    Enqueue(Q, 'E');
    Enqueue(Q, 'F'); // this shouldn't be included in the queue
}

int main()
{
    Queue myQueue;
    InitQueue(&myQueue);
    Populate(&myQueue);
    Display(myQueue);

    free(myQueue.dataPtr);
    return 0;
}