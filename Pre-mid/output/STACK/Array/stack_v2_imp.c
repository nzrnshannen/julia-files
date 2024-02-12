#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int data[SIZE];
    int top;
}nodeType, *STACK;

void initStack(STACK *S);
void Push(STACK *S, int data);
void Pop(STACK *S);
void Display(STACK S);
int Top(STACK S);
bool isEmpty(STACK S);
bool isFull(STACK S);
void Populate(STACK *S);

void initStack(STACK *S)
{
    (*S)->top=-1;
}

void Push(STACK *S, int data)
{
    if((*S)->top<SIZE-1)
    {
        (*S)->top++;
        (*S)->data[(*S)->top] = data;
    }
}

void Pop(STACK *S)
{
    if((*S)->top!=-1)
    {
        (*S)->top--;
    }
}

int Top(STACK S)
{
    return S->data[S->top];
}

void Populate(STACK *S)
{
    Push(S, 1);
    Push(S, 2);
    Push(S, 3);
    Push(S, 4);
    Push(S, 5);
    Push(S, 6);
}

bool isFull(STACK S)
{
    return (S->top==SIZE-1) ? true : false;
}

bool isEmpty(STACK S)
{
    return (S->top==-1) ? true : false;
}

void Display(STACK S)
{
    nodeType tempStack;
    STACK pTemp = &tempStack;
    initStack(&pTemp);

    printf("\n===\nStack: ");
    while(!isEmpty(S))
    {
        Push(&pTemp, Top(S));
        Pop(&S);
    }

    while(!isEmpty(&tempStack))
    {
        printf("%d ", Top(&tempStack));
        Push(&S, Top(&tempStack));
        Pop(&pTemp);
    }

    printf("\n\n");
}

int main()
{
    nodeType myStack;
    STACK pStack = &myStack;
    initStack(&pStack);
    Populate(&pStack);
    Display(pStack);

    return 0;
}