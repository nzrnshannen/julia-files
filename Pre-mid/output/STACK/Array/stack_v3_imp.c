#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int *elemPtr;
    int top;
}STACK;

void initStack(STACK *S);
void push(STACK *S, int data);
void pop(STACK *S);
bool isFull(STACK S);
bool isEmpty(STACK S);
void populate(STACK *S);
void display(STACK S);
int top(STACK S);
void makeNull(STACK *S);

void initStack(STACK *S)
{
    S->top = -1;
    S->elemPtr = (int*)malloc(sizeof(int) * SIZE);
    if(S->elemPtr==NULL)
    {
        exit(1);
    }
}

void push(STACK *S, int data)
{
    if(S->top>=SIZE-1)
    {
        int INIT_CAPACITY = S->top+1;
        S->elemPtr = (int*)realloc(S->elemPtr, sizeof(int) * INIT_CAPACITY + 1);
        if(S->elemPtr==NULL)
        {
            exit(1);
        }
    }

    S->top++;
    S->elemPtr[S->top] = data;
}


void pop(STACK *S)
{
    if(S->top!=-1)
    {
        S->top--;
    }
}

void display(STACK S)
{
    if(S.top!=-1)
    {
        STACK tempStack;
        initStack(&tempStack);

        printf("\n===\nStack: ");

        while(!isEmpty(S))
        {
            push(&tempStack, top(S));
            pop(&S);
        }

        while(!isEmpty(tempStack))
        {
            printf("%d ", top(tempStack));
            push(&S, top(tempStack));
            pop(&tempStack);
        }

        printf("\n\n");
    }
}

int top(STACK S)
{
    return S.elemPtr[S.top];
}

void populate(STACK *S)
{
    push(S, 1);
    push(S, 2);
    push(S, 3);
    push(S, 4);
    push(S, 5);
    push(S, 6);
    push(S, 7);
}

void makeNull(STACK *S)
{
    free(S->elemPtr);
    S->elemPtr=NULL;
}

bool isEmpty(STACK S)
{
    return (S.top==-1) ? true : false;
}

bool isFull(STACK S)
{
    return (S.top==SIZE-1) ? true : false;
}

int main()
{
    STACK myStack;
    initStack(&myStack);
    populate(&myStack);

    display(myStack);
    makeNull(&myStack);
    return 0;
}