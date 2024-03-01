#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int *elemPtr;
    int top;
}STACK;

void initStack(STACK *S);
void Populate(STACK *S);
void Print(STACK S);
void Push(STACK *S, int data);
void Pop(STACK *S);
int Top(STACK S);
bool isEmpty(STACK S);
bool isFull(STACK S);
void insertSorted(STACK *S, int data);
STACK getAllNegatives(STACK S);

void initStack(STACK *S)
{
    S->top=-1;
    S->elemPtr = (int*)malloc(sizeof(int) * SIZE);
    if(S->elemPtr==NULL)
    {
        exit(1);
    }
}

bool isEmpty(STACK S)
{
    return (S.top==-1) ? true : false;
}

bool isFull(STACK S)
{
    return (S.top>=SIZE-1) ? true : false;
}

int Top(STACK S)
{
    return S.elemPtr[S.top];
}

void Push(STACK *S, int data)
{
    if(isFull(*S))
    {
        int INIT_CAP = S->top+1;
        S->elemPtr = (int*)realloc(S->elemPtr, sizeof(int) * (INIT_CAP + 1));
        if(S->elemPtr==NULL)
        {
            exit(1);
        }
    }

    S->top++;
    S->elemPtr[S->top] = data;
}

void Pop(STACK *S)
{
    if(!isEmpty(*S))
    {
        S->top--;
    }
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

        free(tempStack.elemPtr);
    }    
}

void Populate(STACK *S)
{
    insertSorted(S, 1);
    insertSorted(S, -1);
    insertSorted(S, 90);
    insertSorted(S, 23);
    insertSorted(S, -7);
}

void insertSorted(STACK *S, int data)
{

    STACK tempStack;
    initStack(&tempStack);

    while(!isEmpty(*S) && Top(*S) > data)
    {
        Push(&tempStack, Top(*S));
        Pop(S);
    }

    Push(S, data);

    while(!isEmpty(tempStack))
    {
        Push(S, Top(tempStack));
        Pop(&tempStack);
    }
}

STACK getAllNegatives(STACK S)
{
    STACK tempStack, negaStack, returnStack;
    int count=0;
    initStack(&tempStack);
    initStack(&negaStack);
    initStack(&returnStack);
    if(!isEmpty(S))
    {
        while(!isEmpty(S))
        {
            Push(&tempStack, Top(S));
            Pop(&S);
        }
        
        printf("\nwhile loop 1 \n");
        while(!isEmpty(tempStack))
        {
            if(Top(tempStack) < 0)
            {
                Push(&negaStack, Top(tempStack));
                count++;
            }
            Push(&S, Top(tempStack));
            Pop(&tempStack);
        }

        Push(&negaStack, count);
        while(!isEmpty(negaStack))
        {
            Push(&returnStack, Top(negaStack));
            Pop(&negaStack);
        }
    }
    free(tempStack.elemPtr);
    free(negaStack.elemPtr);

    return returnStack;
}

int main()
{
    STACK myStack;
    STACK negaStack;
    initStack(&myStack);
    Populate(&myStack);
    Print(myStack);

    negaStack = getAllNegatives(myStack);
    Print(negaStack);

    return 0;
}