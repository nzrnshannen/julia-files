#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    char data;
    int link;
}nodeType;

typedef struct{
    nodeType Node[MAX];
    int avail;
}VirtualHeap;

typedef struct{
    int Front;
    int Rear;
    VirtualHeap *vptr;
}Queue;

VirtualHeap VH;

void InitQueue(Queue *Q);
void Enqueue(Queue *Q, char data);
void Dequeue(Queue *Q);
void Print(Queue Q);
char Front(Queue Q);
void InsertSorted(Queue *Q, char data);
void Populate(Queue *Q);
bool isFull(Queue Q);
bool isEmpty(Queue Q);

void InitQueue(Queue *Q)
{
    Q->Front = -1;
    Q->Rear = -1;
    Q->vptr = &VH;
}

void Enqueue(Queue *Q, char data)
{
    int ndx = Q->vptr->avail;
    if(ndx!=-1)
    {
        //doing allocspace
        Q->vptr->avail = Q->vptr->Node[ndx].link;

        //inserting element
        Q->vptr->Node[ndx].data = data;
        Q->vptr->Node[ndx].link = -1;

        //front and rear update
        if(Q->Front==-1)
        {
            Q->Front = ndx;
        }
        else
        {
            Q->vptr->Node[Q->Rear].link = ndx;
        }
        Q->Rear = ndx;
    }
}

void Dequeue(Queue *Q)
{
    if(!isEmpty(*Q))
    {
        int temp;
        temp = Q->Front;

        //move front first before doing dealloc as temp and q->front has the same value atm
        //meaning, when we do deallocspace before the line below,
        //we cannot move front to the next node, but instead move front to the avail node (which is outside of the queue already)
        Q->Front = Q->vptr->Node[Q->Front].link;

        //doing deallocSpace
        Q->vptr->Node[temp].link = Q->vptr->avail;
        Q->vptr->avail = temp;


        if(Q->Front==-1)
        {   
            Q->Rear = -1;
        }
    }
}

void Print(Queue Q)
{
    if(!isEmpty(Q))
    {
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
}

char Front(Queue Q)
{
    return Q.vptr->Node[Q.Front].data;
}

void InsertSorted(Queue *Q, char data)
{
    if(Q->vptr->avail!=-1)
    {
        Queue temp;
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
    }
}

bool isFull(Queue Q)
{
    return (Q.vptr->avail==-1) ? true : false;
}

bool isEmpty(Queue Q)
{
    return (Q.Front == -1) ? true : false;
}

void Populate(Queue *Q)
{
    InsertSorted(Q, 'B');
    InsertSorted(Q, 'A');
    InsertSorted(Q, 'L');
    InsertSorted(Q, 'E');
    InsertSorted(Q, 'H');
    InsertSorted(Q, 'Z'); //should not be included in the queue
}

int main()
{
    Queue myQueue;
    InitQueue(&myQueue);

    int x;

    //initializing virtual heap using version 2
    VH.avail = MAX-1;
    for(x=VH.avail; x>=0; x--)
    {
        VH.Node[x].link = x-1;
    }

    Populate(&myQueue);
    
    Print(myQueue);

    return 0;
}