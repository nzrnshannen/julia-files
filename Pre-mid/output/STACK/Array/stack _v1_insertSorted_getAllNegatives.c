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
void InsertSorted(STACK *S, int data);
STACK getAllNegatives(STACK S);     
void Pop(STACK *S);
void Display(STACK S);
int Top(STACK S);
bool isEmpty(STACK S);
bool isFull(STACK S);

void initStack(STACK *S)
{
    S->top = -1;
}

void Populate(STACK *S)
{
    InsertSorted(S, -1);
    InsertSorted(S, -2);
    InsertSorted(S, -3);
    InsertSorted(S, -4);
    InsertSorted(S, -5);
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

void Display(STACK S)
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
            int data = Top(tempStack);
            printf("%d ", data);
            Push(&S, data);
            Pop(&tempStack);
        }

        printf("\n\n");
    }
}

int Top(STACK S)
{
    return S.data[S.top];
}

bool isEmpty(STACK S)
{
    return (S.top==-1) ? true : false;
}

bool isFull(STACK S)
{
    return (S.top==MAX) ? true : false;
}

void InsertSorted(STACK *S, int data)
{
    if(!isFull(*S))
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
}

STACK getAllNegatives(STACK S)
{
    printf("\nfirst test\n");
    STACK tempStack, negaStack;
    initStack(&tempStack);
    initStack(&negaStack);
    int count=0;

    while(!isEmpty(S))
    {
        if(Top(S) < 0)
        {
            Push(&negaStack, Top(S));
            count++;
        }

        Push(&tempStack, Top(S));
        Pop(&S);
    }

    printf("\ntest 1 done\n");

    while(!isEmpty(tempStack))
    {
        Push(&S, Top(tempStack));
        Pop(&tempStack);
    }

    printf("\ntest 2 done\n");
    STACK returnStack;
    initStack(&returnStack);

    Push(&returnStack, count);

    while(!isEmpty(negaStack))
    {
        if()
        {
            printf("\n\n\t >> Temporary stack is full. Last negative number is: %d <<\n", Top(negaStack));
        }

        Push(&returnStack, Top(negaStack));
        Pop(&negaStack);
    }

    return returnStack;
    
}

int main()
{
    STACK marbsEffect, getNega;
    initStack(&marbsEffect);

    Populate(&marbsEffect);

    Display(marbsEffect);

    getNega = getAllNegatives(marbsEffect);
    Display(getNega);

    return 0;
}