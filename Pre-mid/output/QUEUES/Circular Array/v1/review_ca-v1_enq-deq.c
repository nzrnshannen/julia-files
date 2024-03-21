#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    char data[MAX];
    int Front;
    int Rear;
}Queue;

void InitQueue(Queue *Q);
bool isFull(Queue Q);
bool isEmpty(Queue Q);
void Enqueue(Queue *Q, char data);
void Dequeue(Queue *Q);
char Front(Queue Q);
void Display(Queue Q);
void InsertSorted(Queue *Q, char data);
void Populate(Queue *Q);

void InitQueue(Queue *Q)
{
    Q->Front = -1;
    Q->Rear = -1;
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
        if(isEmpty(*Q))
        {
            Q->Front++;
            Q->Rear++;
        }
        else
        {
            Q->Rear = (Q->Rear+1)%MAX;
        }
        Q->data[Q->Rear] = data;
    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        if(Q->Front==Q->Rear)
        {
            Q->Front = -1;
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
    return Q.data[Q.Front];
}

void Display(Queue Q)
{
    if(!isEmpty(Q))
    {
        printf("\ndisplay test\n");
        Queue temp;
        InitQueue(&temp);

        char ch;

        printf("\n===\nQueue: ");
        
        while(!isEmpty(Q))
        {
            ch = Front(Q);
            printf("%c ", ch);
            Dequeue(&Q);
            Enqueue(&temp, ch);
        }

        while(!isEmpty(temp))
        {
            ch = Front(temp);
            Dequeue(&temp);
            Enqueue(&Q, ch);
        }

        printf("\n\n");
    }
    else
        printf("\noutside\n");
}

void InsertSorted(Queue *Q, char data)
{
    if(!isFull(*Q))
    {
        char ch;
        Queue temp;
        InitQueue(&temp);

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
    }
}

void Populate(Queue *Q)
{
    InsertSorted(Q, 'B');
    InsertSorted(Q, 'C');
    InsertSorted(Q, 'A');
    InsertSorted(Q, 'L');
    InsertSorted(Q, 'Z');
    InsertSorted(Q, 'D'); //this shouldn't be included in the queue
}

int main()
{
    Queue myQueue;
    InitQueue(&myQueue);
    Populate(&myQueue);
    Display(myQueue);
    return 0;
}