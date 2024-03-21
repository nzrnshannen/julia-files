#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    char data[MAX];
    int Front;
    int Rear;
}qNode, *Queue;

void InitQueue(Queue *Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);
void Enqueue(Queue *Q, char data);
void Dequeue(Queue *Q);
char Front(Queue Q);
void Display(Queue Q);
void InsertSorted(Queue *Q, char data);
void Populate(Queue *Q);

void InitQueue(Queue *Q)
{
    (*Q)->Front = -1;
    (*Q)->Rear = -1;
}

bool isEmpty(Queue Q)
{
    return (Q->Front==-1) ? true : false;
}

bool isFull(Queue Q)
{
    return (Q->Front == (Q->Rear+1)%MAX) ? true : false;
}

void Enqueue(Queue *Q, char data)
{
    if(!isFull(*Q))
    {
        if((*Q)->Front==-1)
        {
            (*Q)->Front++;
            (*Q)->Rear++;
        }
        else
        {
            (*Q)->Rear = ((*Q)->Rear+1)%MAX;
        }
        (*Q)->data[(*Q)->Rear] = data;
    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        if((*Q)->Front==(*Q)->Rear)
        {
            (*Q)->Front = -1;
            (*Q)->Rear =- 1;
        }
        else
        {
            (*Q)->Front = ((*Q)->Front+1)%MAX;
        }
    }
}

char Front(Queue Q)
{
    return Q->data[Q->Front];
}

void Display(Queue Q)
{
    if(!isEmpty(Q))
    {
        qNode temp;
        Queue tempQueue = &temp;
        InitQueue(&tempQueue);

        printf("\n===\nQueue: ");
        char ch;
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
void InsertSorted(Queue *Q, char data)
{
    if(!isFull(*Q))
    {
        qNode temp;
        Queue tempQueue = &temp;
        InitQueue(&tempQueue);
        char ch;

        while(!isEmpty(*Q) && Front(*Q) < data)
        {
            ch = Front(*Q);
            Dequeue(Q);
            Enqueue(&tempQueue, ch);
        }   

        Enqueue(&tempQueue, data);

        while(!isEmpty(*Q))
        {
            ch = Front(*Q);
            Dequeue(Q);
            Enqueue(&tempQueue, ch);
        }


        while(!isEmpty(tempQueue))
        {
            ch = Front(tempQueue);
            Dequeue(&tempQueue);
            Enqueue(Q, ch);
        }
        
    }
}

void Populate(Queue *Q)
{
    InsertSorted(Q, 'C');
    InsertSorted(Q, 'D');
    InsertSorted(Q, 'L');
    InsertSorted(Q, 'A');
    InsertSorted(Q, 'G');
    InsertSorted(Q, 'B'); //this shouldn't be included in the queue
}

int main()
{
    qNode exampleQueue;
    Queue myQueue = &exampleQueue;
    InitQueue(&myQueue);
    Populate(&myQueue);
    Display(myQueue);
    return 0;
}