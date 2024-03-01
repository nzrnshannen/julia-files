#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node{
    int elem;
    struct node *next;
}nodeType, *Qnode;

typedef struct{
    Qnode front;
    Qnode rear;
}Queue;

void initQueue(Queue *Q);
void Enqueue(Queue *Q, int elem);
void Dequeue(Queue *Q);
int Front(Queue Q);
void Display(Queue Q);
void Populate(Queue *Q);

void initQueue(Queue *Q)
{
    Q->front = NULL;
    Q->rear = NULL;
}

void Enqueue(Queue *Q, int elem)
{
    Qnode newNode = (Qnode)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->elem = elem;
        newNode->next = NULL;

        //insert the first elem
        if(Q->front == NULL)
        {
            Q->front = newNode;
            //Q->rear = newNode;
        }
        else
        {
            Q->rear->next = newNode;
            //Q->rear = newNode;
        }

        Q->rear = newNode;
    }
}

void Dequeue(Queue *Q)
{
    if(Q->front!=NULL)
    {
        Qnode temp; //will hold the node to be deleted
        temp = Q->front; //temp will point to the node to be deleted
        if(Q->front==Q->rear)
        {
            //since front and rear are pointing to the same node, meaning there's only one node in the queue
            Q->front = NULL;
            Q->rear = NULL;
        }
        else
        {
            Q->front = temp->next; //moving front to point to the next node
        }

        free(temp);
    }
}

int Front(Queue Q)
{
    return (Q.front!=NULL) ? Q.front->elem : -9999999;
}

void Display(Queue Q)
{
    if(Q.front!=NULL)
    {
        Queue tempQueue;
        initQueue(&tempQueue);

        printf("\n===\nQueue: ");
        while(Q.front!=NULL)
        {
            int data = Front(Q);
            Enqueue(&tempQueue, data);
            Dequeue(&Q);
        }

        while(tempQueue.front!=NULL)
        {
            int data = Front(tempQueue);
            printf("%d ", data);
            Enqueue(&Q, data);
            Dequeue(&tempQueue);
        }

        printf("\n\n");
    }
}

void Populate(Queue *Q)
{
    Enqueue(Q, 1);
    Enqueue(Q, 5);
    Enqueue(Q, 6);
    Enqueue(Q, 2);
    Enqueue(Q, 8);    
}

int main()
{
    Queue myQueue;
    initQueue(&myQueue);
    Populate(&myQueue);
    Display(myQueue);
    return 0;
}