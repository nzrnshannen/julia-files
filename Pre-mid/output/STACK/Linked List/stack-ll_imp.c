//beginning node will be the top
//head will be at the top


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    int data;
    struct node *next;
}nodetype, *STACK;

void initStack(STACK *S);
void push(STACK *S, int data); //insertAtBeginning
void pop(STACK *S); //deleteAtBeginning
int top(STACK S);
void printStack(STACK S);
void populate(STACK *S);
void deleteFirstOccur(STACK *S);
void deleteAllOccur(STACK *S);
bool isEmpty(STACK S);
void populate(STACK *S);

void initStack(STACK *S)
{
    *S = NULL;
}

void push(STACK *S, int data)
{
    STACK newnode = (STACK)malloc(sizeof(nodetype));
    if(newnode!=NULL)
    {
        newnode->data = data;
        newnode->next = *S;
        *S = newnode;
    }
}

void pop(STACK *S)
{
    STACK temp;
    temp = *S;
    *S = (*S)->next;
    free(temp);
}

int top(STACK S)
{
    return S->data;
}

void printStack(STACK S)
{
    if(S!=NULL)
    {
        printf("\n===\nStack: ");
        STACK tempStack;
        initStack(&tempStack);

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


int main()
{
    return 0;
}