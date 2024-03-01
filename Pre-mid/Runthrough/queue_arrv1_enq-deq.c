#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    int elem[MAX];
    int front;
    int rear;
}Queue;

void initQueue(Queue *Q);
bool isFull(Queue Q);
bool isEmpty(Queue Q);
void enqueue(Queue *Q, int data);
void dequeue(Queue *Q);
int front(Queue Q);

void displayQueue(Queue Q);

void initQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear = -1;
}

bool isEmpty(Queue Q)
{
    return (Q.front=-1) ? true : false;
}

bool isFull(Queue Q)
{
    return (Q.rear == -1) ? true : false;
}


void enqueue(Queue *Q, int data)
{
    
}


int main()
{

    return 0;
}