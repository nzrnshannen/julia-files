#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int arr[SIZE];
    int top;
}arrStack, *STACK;

void InitStack(STACK *S);
void Push(STACK *S, int data);
void Pop(STACK *S);
bool isEmpty(STACK S);
bool isFull(STACK S);
void Print(STACK S);
void Populate(STACK *S);
void PopFirstOccur(STACK *S, int data);
void PopAllOccur(STACK *S, int data);
int Top(STACK S);

void InitStack(STACK *S)
{
    (*S)->top = -1;
}

int Top(STACK S)
{
    return S->arr[S->top];
}

void Push(STACK *S, int data)
{
    if(!isFull(*S))
    {
        (*S)->top++;
        (*S)->arr[(*S)->top] = data;
    }
}

void Pop(STACK *S)
{
    if(!isEmpty(*S))
    {
        (*S)->top--;
    }
}

bool isEmpty(STACK S)
{
    return (S->top==-1) ? true : false;
}

bool isFull(STACK S)
{
    return (S->top==SIZE-1) ? true : false;
}

void Print(STACK S)
{
    if(!isEmpty(S))
    {
        arrStack tempStack;
        STACK ptrTemp = &tempStack;
        InitStack(&ptrTemp);

        printf("\n===\nStack: ");
        while(!isEmpty(S))
        {
            Push(&ptrTemp, Top(S));
            Pop(&S);
        }

        while(!isEmpty(ptrTemp))
        {
            printf("%d ", Top(ptrTemp));
            Push(&S, Top(ptrTemp));
            Pop(&ptrTemp);
        }
        printf("\n\n");
    }
}

void PopFirstOccur(STACK *S, int data)
{
    if(!isEmpty(*S))
    {
        arrStack tempStack;
        STACK ptrTemp = &tempStack;
        InitStack(&ptrTemp);

        // while(!isEmpty(*S) && Top(*S)!=data)
        // {
        //     Push(&ptrTemp, data);
        // }

        // if(Top(*S)==data)
        // {
        //     Pop(S);
        // }

        // while(!isEmpty(ptrTemp))
        // {
        //     Push(S, Top(ptrTemp));
        //     Pop(&ptrTemp);
        // }

        while(!isEmpty(*S))
        {
            Push(&ptrTemp, Top(*S));
            Pop(S);
        }

        while(!isEmpty(ptrTemp) && Top(ptrTemp)!=data)
        {
            Push(S, Top(ptrTemp));
        }

        if(Top(ptrTemp)==data)
        {
            Pop(&ptrTemp);
        }

        while(!isEmpty(ptrTemp))
        {
            Push(S, Top(ptrTemp));
            Pop(&ptrTemp);
        }
    }
}

void PopAllOccur(STACK *S, int data)
{
    if(!isEmpty(*S))
    {
        arrStack tempStack;
        STACK ptrTemp = &tempStack;
        InitStack(&ptrTemp);

        while(!isEmpty(*S))
        {
            if(Top(*S)!=data)
            {
                Push(&ptrTemp, Top(*S));
            }
            Pop(S);
        }

        while(!isEmpty(ptrTemp))
        {
            Push(S, Top(ptrTemp));
            Pop(&ptrTemp);
        }
    }
}

void Populate(STACK *S)
{
    Push(S, 1);
    Push(S, 1);
    Push(S, 3);
    Push(S, 4);
    Push(S, 1);
    Push(S, 6);
}

int main()
{
    arrStack myStack;
    STACK ptrStack = &myStack;
    InitStack(&ptrStack);
    Populate(&ptrStack);
    Print(ptrStack);
    PopFirstOccur(&ptrStack, 1);
    Print(ptrStack);
    return 0;
}