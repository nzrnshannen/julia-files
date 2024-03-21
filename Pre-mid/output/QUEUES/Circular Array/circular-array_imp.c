#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    int data[MAX];
    int front;
    int rear;
}Queue;

void enqueue(Queue *Q, int data);
void dequeue(Queue *Q);
int front(Queue Q);
void initQueue(Queue *Q);
void populate(Queue *Q);
void display(Queue Q);

void initQueue(Queue *Q)
{
    Q->front = -1; //initialize front to be empty
    Q->rear = -1; //initialize rear to be empty
}

int front(Queue Q)
{
    return Q.data[Q.front]; //return front of the queue but it doesn't remove the element
}

void enqueue(Queue *Q, int data)
{
    if((Q->rear+1)%MAX!=Q->front) //it's like looking ahead if there's an available index (space)
    {
        if(Q->front==-1 && Q->rear==-1) //no element yet on the list
        {
            Q->front ++;
            Q->rear++;
        }
        else
        {
            Q->rear = (Q->rear + 1)%MAX;
            //if MAX is 5,
            //when Q->rear is 3, then Q->rear + 1 is 4 ==> 4 % 5 = 4 
            //when Q->rear is 4, then Q->rear + 1 is 5 ==> 5 % 5 = 0 (it goes back to 0 as index 0 is available)
        }

        Q->data[Q->rear] = data; //always insert data in the rear of the queue 
    }
}

void dequeue(Queue *Q)
{
    if(Q->front!=-1)
    {
        if(Q->front==Q->rear) //if Q->front and Q->rear is at the same index (meaning, there's only 1 element left to be dequeued)
        {
            //these two lines of code set the queue to be empty
            Q->front=-1; 
            Q->rear=-1;
        }
        else
        {
            Q->front = (Q->front+1)%MAX; 
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
            printf("%d ", front(Q));
            enqueue(&tempQueue, front(Q));
            dequeue(&Q);
        }

        while(tempQueue.front!=-1)
        {
            enqueue(&Q, front(tempQueue));
            dequeue(&tempQueue);
        }

        printf("\n\n");
    }
}

void populate(Queue *Q)
{
    enqueue(Q, 10);
    enqueue(Q, 20);
    enqueue(Q, 30);
    enqueue(Q, 40);
    enqueue(Q, 50);
    enqueue(Q, 60);
}

int main()
{
    Queue myQueue;
    initQueue(&myQueue);
    populate(&myQueue);
    display(myQueue);
    dequeue(&myQueue);
    display(myQueue);
    return 0;
}