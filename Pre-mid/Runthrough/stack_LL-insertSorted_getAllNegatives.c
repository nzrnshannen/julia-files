#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}nodeType, *STACK;

void Push(STACK *S, int data);
void Pop(STACK *S);
void InsertSorted(STACK *S, int data);
void Display(STACK S);
void InitStack(STACK *S);
bool isEmpty(STACK S);
STACK getAllNegatives(STACK S); 
void Clear(STACK *S);
void Populate(STACK *S);
int Top(STACK S);

void InitStack(STACK *S)
{
    *S = NULL;
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

void Display(STACK S)
{
    STACK tempStack;
    InitStack(&tempStack);

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

int Top(STACK S)
{
    return S->data;
}

void Clear(STACK *S)
{
    while(!isEmpty(*S))
    {
        Pop(S);
    }
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

STACK getAllNegatives(STACK S)
{
    STACK tempStack, stackNegative;
    InitStack(&tempStack);
    InitStack(&stackNegative);

    int count = 0;
    while(!isEmpty(S))
    {
        if(Top(S) < 0)
        {
            Push(&stackNegative, Top(S));
            count++;
        }

        Push(&tempStack, Top(S));
        Pop(&S);
    }

    while(!isEmpty(tempStack))
    {
        Push(&S, Top(tempStack));
        Pop(&tempStack);
    }

    STACK returnStack;
    InitStack(&returnStack);
    STACK countNode = (STACK)malloc(sizeof(nodeType));
    if(countNode!=NULL)
    {
        countNode->next = returnStack;
        returnStack = countNode;
    }

    while(!isEmpty(stackNegative))
    {
        Push(&returnStack, Top(stackNegative));
        Pop(&stackNegative);
    }

    countNode->data = count;
    return returnStack;
}

bool isEmpty(STACK S)
{
    return (S==NULL) ? true : false;
}

void InsertSorted(STACK *S, int data)
{
    STACK tempStack;
    InitStack(&tempStack);

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

void Populate(STACK *S)
{
    InsertSorted(S, -1);
    InsertSorted(S, -6);
    InsertSorted(S, -2);
    InsertSorted(S, 18);
    InsertSorted(S, -5);
}


int main()
{
    STACK myStack;
    InitStack(&myStack);

    Populate(&myStack);
    Display(myStack);

    STACK negaStack;
    negaStack = getAllNegatives(myStack);
    Display(negaStack);

    // Clear(&myStack);
    // Clear(&negaStack);
    return 0;
}