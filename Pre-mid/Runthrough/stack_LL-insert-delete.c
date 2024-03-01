#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    int data;
    struct node *next;
}nodeType, *STACK;

void initStack(STACK *S);
void Push(STACK *S, int data);
void Pop(STACK *S);
void DeleteFirstOccurrence(STACK *S, int data);
void DeleteAllOccurrence(STACK *S, int data);
void Display(STACK S);
void Populate(STACK *S);
bool isEmpty(STACK S);
void Clear(STACK *S);
int Top(STACK S);

void initStack(STACK *S)
{
    *S = NULL;
}

bool isEmpty(STACK S)
{
    return (S==NULL) ? true : false;
}

void Push(STACK *S, int data)
{
    STACK newNode = (STACK)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->data = data;
        newNode->next = *S;
        *S = newNode;
    }
}

void Pop(STACK *S)
{
    if(!isEmpty(*S))
    {
        STACK temp;
        temp = *S;
        *S = temp->next;
        free(temp);
    }
}

int Top(STACK S)
{
    return S->data;
}

void DeleteFirstOccurrence(STACK *S, int data)
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

        if(!isEmpty(tempStack) && Top(tempStack)==data)
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

void DeleteAllOccurrence(STACK *S, int data)
{
    if(!isEmpty(*S))
    {
        STACK tempStack;
        initStack(&tempStack);

        while(!isEmpty(*S))
        {
            if(Top(*S) != data)
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

void Display(STACK S)
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

        printf("\n\n");
    }
}

void Clear(STACK *S)
{
    while(!isEmpty(*S))
    {
        Pop(S);
    }
}

void Populate(STACK *S)
{
    Push(S, 1);
    Push(S, 8);
    Push(S, 5);
    Push(S, 3);
    Push(S, 2);
    Push(S, 5);
    Push(S, 4);
}

int main()
{
    STACK myStack;
    initStack(&myStack);

    Populate(&myStack);
    Display(myStack);

    DeleteFirstOccurrence(&myStack, 5);
    Display(myStack);

    Clear(&myStack);
    return 0;
}