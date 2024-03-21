#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    int data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int avail;
}VirtualHeap;

typedef struct{
    VirtualHeap *vptr;
    int front;
    int rear;
}Queue;

VirtualHeap VH;

void InitQueue(Queue *Q);
void Enqueue(Queue *Q, int data);
void Dequeue(Queue *Q);
int Front(Queue Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);
void Display(Queue *Q);
void Populate(Queue *Q);

void InitQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear = -1;
    Q->vptr = &VH;
}

bool isFull(Queue Q)
{
    return (Q.vptr->avail==-1) ? true : false;
}

bool isEmpty(Queue Q)
{
    return(Q.front == -1) ? true : false;
}

void Enqueue(Queue *Q, int data)
{
    if(Q->vptr->avail!=-1)
    {
        int ndx = Q->vptr->avail;
        Q->vptr->avail = Q->vptr->Nodes[ndx].link; //update avail

        Q->vptr->Nodes[ndx].data = data; 
        Q->vptr->Nodes[ndx].link = -1;

        if(Q->front==-1)
        {
            Q->front = ndx;
            Q->rear = ndx;
        }
        else
        {
            Q->vptr->Nodes[Q->rear].link = ndx; //update the link part of the current rear before moving it
            Q->rear = ndx; //change rear
        }
    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        int nextFront;
        nextFront = Q->vptr->Nodes[Q->front].link;

        if(Q->front!=-1)
        {
            Q->vptr->Nodes[Q->front].link = Q->vptr->avail;
            Q->vptr->avail = Q->front;

            Q->front = nextFront;

            if(Q->front == -1)
            {
                Q->rear= -1;
            }
        }
    }
}

int Front(Queue Q)
{
    return Q.vptr->Nodes[Q.front].data;
}

void Display(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        printf("\n===\nQueue: ");
        Queue tempQueue;
        int data;

        InitQueue(&tempQueue);
        while(!isEmpty(*Q))
        {
            data = Front(*Q);
            printf("%d ", data);
            Dequeue(Q);
            Enqueue(&tempQueue, data);
        }

        while(!isEmpty(tempQueue))
        {
            data = Front(tempQueue);
            Dequeue(&tempQueue);
            Enqueue(Q, data);
        }

        printf("\n\n");
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
    VH.avail = MAX-1;
    int x;
    for(x=VH.avail; x>=0; x--)
    {
        VH.Nodes[x].link = x-1;
    }

    Queue myQueue;
    InitQueue(&myQueue);
    Populate(&myQueue);
    Display(&myQueue);

    Dequeue(&myQueue);
    Display(&myQueue);
    Display(&myQueue);
    return 0;
}