#include<stdio.h>
#include<stdbool.h>

#define MAX 5

typedef struct{
    int data[MAX];
    int top;
}STACK;

void initStack(STACK *S);
void Populate(STACK *S);
void Push(STACK *S, int data);
void Pop(STACK *S);
int Top(STACK S);
void Print(STACK S);
void DeleteFirstOccur(STACK *S, int data);
void DeleteAllOccur(STACK *S, int data);
bool isEmpty(STACK S);
bool isFull(STACK S);

void initStack(STACK *S)
{
    S->top = -1;
}

void Populate(STACK *S)
{
    Push(S, 1);
    Push(S, 2);
    Push(S, 3);
    Push(S, 1);
    Push(S, 1);
}

void Push(STACK *S, int data)
{
    if(!isFull(*S))
    {
        S->top++;
        S->data[S->top] = data;
    }
}

void Pop(STACK *S)
{
    if(!isEmpty(*S))
    {
        S->top--;
    }
}

int Top(STACK S)
{
    return S.data[S.top];
}

void Print(STACK S)
{
    if(!isEmpty(S))
    {
        STACK tempStack;
        initStack(&tempStack);

        printf("\n===\nStack: ");
        while(!isEmpty(S))
        {
            Push(&tempStack, Top(S));
            Pop(&S);
        }

        while(!isEmpty(tempStack))
        {
            printf("%d ", Top(tempStack));
            Push(&S, Top(tempStack));
            Pop(&tempStack);
        }

        printf("\n\n");
    }
}

void DeleteFirstOccur(STACK *S, int data)
{
    if(!isEmpty(*S))
    {
        STACK tempStack;
        initStack(&tempStack);

        while(!isEmpty(*S))
        {
            Push(&tempStack, Top(*S));
            Pop(S);
        }

        while(!isEmpty(tempStack) && Top(tempStack)!=data)
        {
            Push(S, Top(tempStack));
            Pop(&tempStack);
        }

        if(Top(tempStack)==data)
        {
            Pop(&tempStack);
        }

        while(!isEmpty(tempStack))
        {
            Push(S, Top(tempStack));
            Pop(&tempStack);
        }

    }
}

void DeleteAllOccur(STACK *S, int data)
{
    if(!isEmpty(*S))
    {
        STACK tempStack;
        initStack(&tempStack);

        while(!isEmpty(*S))
        {
            if(Top(*S)!=data)
            {
                Push(&tempStack, Top(*S));
            }
            Pop(S);
        }

        while(!isEmpty(tempStack))
        {
            Push(S, Top(tempStack));
            Pop(&tempStack);
        }
    }
}
bool isEmpty(STACK S)
{
    return (S.top==-1) ? true : false;
}

bool isFull(STACK S)
{
    return (S.top==MAX) ? true : false;
}

int main()
{
    STACK myStack;
    initStack(&myStack);

    Populate(&myStack);
    Print(myStack);

    DeleteFirstOccur(&myStack, 1);
    Print(myStack);
    return 0;   
}