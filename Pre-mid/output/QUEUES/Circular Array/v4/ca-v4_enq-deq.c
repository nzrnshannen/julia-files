#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX 5

typedef struct{
    char *elemPtr;
    int rear;
    int front;
}Qnode, *QUEUE;

void initQueue(QUEUE *Q);
void Enqueue(QUEUE *Q, char elem);
void Dequeue(QUEUE *Q);
bool isFull(QUEUE Q);
bool isEmpty(QUEUE Q);
void Display(QUEUE *Q);
void Populate(QUEUE *Q);
char Front(QUEUE Q);

void initQueue(QUEUE *Q)
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

void Enqueue(QUEUE *Q, char elem)
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

        (*Q)->elemPtr[(*Q)->rear] = elem;
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
            (*Q)->front =((*Q)->front + 1)%MAX;
        }
    }
}

bool isFull(QUEUE Q)
{
    return (Q->front == (Q->rear+1)%MAX)? true : false;
}

bool isEmpty(QUEUE Q)
{
    return (Q->front==-1) ? true : false;
}

void Display(QUEUE *Q)
{
    if(!isEmpty(*Q))
    {
        Qnode temp;
        QUEUE tempQueue;
        tempQueue = &temp;
        initQueue(&tempQueue);

        printf("\n===\nQueue: ");
        char ch;
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
        printf("\n");
    }
    else
    {
        printf("\n\t>> Empty queue <<\n");
    }
}

char Front(QUEUE Q)
{
    return Q->elemPtr[Q->front];
}

void Populate(QUEUE *Q)
{
    Enqueue(Q, 'A');
    Enqueue(Q, 'B');
    Enqueue(Q, 'C');
    Enqueue(Q, 'D');
    Enqueue(Q, 'E');
    Enqueue(Q, 'F'); //should not be included
}

//insert sorted
void InsertSorted(QUEUE *Q, char data)
{
    if(!isFull(*Q))
    {
        Qnode tempq;
        QUEUE temp = &tempq;
        initQueue(&temp);
        char ch;

        while(!isEmpty(*Q) && Front(*Q) < data)
        {
            ch = Front(*Q);
            Dequeue(Q);
            Enqueue(&temp, ch);
        }

        Enqueue(&temp, data);


        while(!isEmpty(temp))
        {
            ch = Front(temp);
            Dequeue(&temp);
            Enqueue(Q, ch);
        }

        printf("\n");
    }
}

int main()
{
    Qnode qn;
    QUEUE myQueue = &qn;
    initQueue(&myQueue);
    Populate(&myQueue);
    Display(&myQueue);
    Display(&myQueue);
    Dequeue(&myQueue);
    Dequeue(&myQueue);
    Dequeue(&myQueue);
    Dequeue(&myQueue);
    Dequeue(&myQueue);
    Dequeue(&myQueue);
    Display(&myQueue);
    free(myQueue->elemPtr);
    return 0;
}