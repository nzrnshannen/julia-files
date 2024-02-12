#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int data[SIZE];
    int top;
}STACK;

void initStack(STACK *S);
void push(STACK *S, int data);
void pop(STACK *S);
int top(STACK S);
bool isFull(STACK S);
bool isEmpty(STACK S);
void printStack(STACK S);
void populate(STACK *S);

void initStack(STACK *S)
{
    S->top=-1;
}

void push(STACK *S, int data)
{
    if(S->top<SIZE-1)
    {
        S->top++;
        S->data[S->top] = data;
    }
}

void pop(STACK *S)
{
    if(S->top!=-1)
    {
        S->top--;
    }
}

int top(STACK S)
{
    return S.data[S.top];
}

bool isFull(STACK S)
{
    return (S.top==SIZE-1) ? true : false;
}

bool isEmpty(STACK S)
{
    return (S.top==-1) ? true: false;
}

void printStack(STACK S)
{
    STACK tempStack;
    initStack(&tempStack);

    printf("\n=====\nSTACK: ");
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

void populate(STACK *S)
{
    push(S, 1);
    push(S, 2);
    push(S, 3);
    push(S, 4);
    push(S, 5);
    push(S, 6);
}
int main()
{
    STACK myStack;
    initStack(&myStack);

    populate(&myStack);

    printStack(myStack);
    return 0;
}