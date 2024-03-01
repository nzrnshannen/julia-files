#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int *elemPtr;
    int top;
}STACK;

void initStack(STACK *S);
void Print(STACK S);
void Push(STACK *S, int data);
void Pop(STACK *S);
void Populate(STACK *S);
bool isEmpty(STACK S);
bool isFull(STACK S);
void DeleteFirstOccur(STACK *S, int data);
void DeleteAllOccur(STACK *S, int data);
int Top(STACK S);

void initStack(STACK *S)
{
    S->top = -1;
    S->elemPtr = (int*)malloc(sizeof(int) * SIZE);
    if(S->elemPtr==NULL)
    {
        exit(1);
    }
}

void Push(STACK *S, int data)
{
    if(isFull(*S))
    {
        int INIT_CAP = S->top+1;
        S->elemPtr = (int*)realloc(S->elemPtr, sizeof(int) * INIT_CAP + 1);
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

bool isEmpty(STACK S)
{
    return (S.top==-1) ? true : false;
}

bool isFull(STACK S)
{
    return (S.top>=SIZE-1) ? true : false;
}

void DeleteFirstOccur(STACK *S, int data)
{
    if(!isEmpty(*S))
    {
        STACK tempStack;
        initStack(&tempStack);

        // while(!isEmpty(*S) && Top(*S) != data)
        // {
        //     Push(&tempStack, Top(*S));
        //     Pop(S);
        // }

        // Pop(S);

        // while(!isEmpty(tempStack))
        // {
        //     Push(S, Top(tempStack));
        //     Pop(S);
        // }

        // free(tempStack.elemPtr);


        while(!isEmpty(*S))
        {
            Push(&tempStack, Top(*S));
            Pop(S);
        }

        while(!isEmpty(tempStack) && Top(tempStack) != data)
        {
            Push(S, Top(tempStack));
            Pop(&tempStack);
        }

        Pop(&tempStack);

        while(!isEmpty(tempStack))
        {
            Push(S, Top(tempStack));
            Pop(&tempStack);
        }

        free(tempStack.elemPtr);
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

int Top(STACK S)
{
    return S.elemPtr[S.top];
}

void Print(STACK S)
{
    if(!isEmpty(S))
    {
        printf("\n===\nStack: ");
        STACK tempStack;
        initStack(&tempStack);

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
    Push(S, 1);
    Push(S, 4);
    Push(S, 6);
    Push(S, 1);
    Push(S, 1);
    Push(S, 65);
    Push(S, 1);
}

int main()
{
    STACK myStack;
    initStack(&myStack);
    Populate(&myStack);
    Print(myStack);

    DeleteAllOccur(&myStack, 1);
    Print(myStack);
    free(myStack.elemPtr);
    return 0;
}