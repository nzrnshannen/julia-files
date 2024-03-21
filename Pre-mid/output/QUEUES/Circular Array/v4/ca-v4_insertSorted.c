#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#define MAX 5

typedef struct{
    char *elemPtr;
    int front;
    int rear;
}Qnode, *QUEUE;

void InitQueue(QUEUE *Q);
bool isEmpty(QUEUE Q);
bool isFull(QUEUE Q);
void Display(QUEUE *Q);
char Front(QUEUE Q);
void Enqueue(QUEUE *Q, char data);
void Dequeue(QUEUE *Q);
void InsertSorted(QUEUE *Q, char data);
void Populate(QUEUE *Q);

void InitQueue(QUEUE *Q)
{
    (*Q)->front = -1;
    (*Q)->rear = -1;
    (*Q)->elemPtr = (char*)malloc(sizeof(char) * MAX);
    if((*Q)->elemPtr==NULL)
    {
        perror("Memory allocation failure");
        exit(1);
    }
}

bool isEmpty(QUEUE Q)
{
    return (Q->front==-1) ? true : false;
}

bool isFull(QUEUE Q)
{
    return (Q->front == (Q->rear+1)%MAX)? true : false;
}

void Display(QUEUE *Q)
{
    if(!isEmpty(*Q))
    {
        Qnode tempq;
        QUEUE temp = &tempq;
        InitQueue(&temp);

        char ch;

        printf("\n==\nQueue: ");
        while(!isEmpty(*Q))
        {
            ch = Front(*Q);
            printf("%c ", ch);
            Dequeue(Q);
            Enqueue(&temp, ch);
        }

        while(!isEmpty(temp))
        {
            ch = Front(temp);
            Dequeue(&temp);
            Enqueue(Q, ch);
        }

        printf("\n");
    }
}

char Front(QUEUE Q)
{
    return Q->elemPtr[Q->front];
}

void Enqueue(QUEUE *Q, char data)
{
    if(!isFull(*Q))
    {
        if((*Q)->front==-1)
        {
            (*Q)->front++;
            (*Q)->rear++;
        }
        else
        {
            (*Q)->rear = ((*Q)->rear+1)%MAX;
        }
        (*Q)->elemPtr[(*Q)->rear] = data;
    }
}

void InsertSorted(QUEUE *Q, char data)
{
    if(!isFull(*Q))
    {
        Qnode tempq;
        QUEUE temp = &tempq;
        InitQueue(&temp);

        char ch;

        while(!isEmpty(*Q) && Front(*Q) < data)
        {
            ch = Front(*Q);
            Dequeue(Q);
            Enqueue(&temp, ch);
        }

        Enqueue(&temp, data);

        while(!isEmpty(*Q))
        {
            ch = Front(*Q);
            Dequeue(Q);
            Enqueue(&temp, ch);
        }

        while(!isEmpty(temp))
        {
            ch = Front(temp);
            Dequeue(&temp);
            Enqueue(Q, ch);
        }

        printf("\n");
    }
}

void Dequeue(QUEUE *Q)
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

void Populate(QUEUE *Q)
{
    InsertSorted(Q, 'B');
    InsertSorted(Q, 'C');
    InsertSorted(Q, 'F');
    InsertSorted(Q, 'E');
    InsertSorted(Q, 'G');

    // Enqueue(Q, 'B');
    // Enqueue(Q, 'C');
    // Enqueue(Q, 'A');
    // Enqueue(Q, 'D');
    // Enqueue(Q, 'F');
    // Enqueue(Q, 'Z');
}

int main()
{
    Qnode tmpq;
    QUEUE myQueue = &tmpq;
    InitQueue(&myQueue);
    Populate(&myQueue);
    Display(&myQueue);

    free(myQueue->elemPtr);
    return 0;
}
