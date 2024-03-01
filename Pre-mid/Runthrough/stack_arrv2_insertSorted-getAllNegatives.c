#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int data[SIZE];
    int top;
}arrStack, *STACK;

void InitStack(STACK *S);
void Push(STACK *S, int data);
void InsertSorted(STACK *S, int data);
arrStack getAllNegatives(STACK S);
void Pop(STACK *S);
int Top(STACK S);
void Populate(STACK *S);
bool isEmpty(STACK S);
bool isFull(STACK S);
void Print(STACK S);

void InitStack(STACK *S)
{
    (*S)->top=-1;
}

void Push(STACK *S, int data)
{
    if(!isFull(*S))
    {
        (*S)->top++;
        (*S)->data[(*S)->top] = data;
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
        STACK pTemp = &tempStack;
        InitStack(&pTemp);

        printf("\n===\nStack: ");
        while(!isEmpty(S))
        {
            Push(&pTemp, Top(S));
            Pop(&S);
        }

        while(!isEmpty(pTemp))
        {
            printf("%d ", Top(pTemp));
            Push(&S, Top(pTemp));
            Pop(&pTemp);
        }

        printf("\n\n");
    }
}

arrStack getAllNegatives(STACK S)
{
    arrStack tempStack, stackNegative;
    int count=0;
    
    STACK ptrTemp = &tempStack;
    STACK ptrNega = &stackNegative;

    InitStack(&ptrTemp);
    InitStack(&ptrNega);

    while(!isEmpty(S))
    {
        if(Top(S) < 0)
        {
            if(count==SIZE-1)
            {
                printf("\n\n\t>> Temporary stack is full. Last negative number: %d <<\n", Top(S));
            }
            else
            {
                Push(&ptrNega, Top(S));
            }
            count++;
        }

        Push(&ptrTemp, Top(S));
        Pop(&S);
    }

    while(!isEmpty(ptrTemp))
    {
        Push(&S, Top(ptrTemp));
        Pop(&ptrTemp);
    }

    arrStack returnStack;
    STACK ptrReturn = &returnStack;
    InitStack(&ptrReturn);

    Push(&ptrReturn, count);
    while(!isEmpty(ptrNega))
    {
        Push(&ptrReturn, Top(ptrNega));
        Pop(&ptrNega);
    }

    return returnStack;

}

void InsertSorted(STACK *S, int data)
{
    arrStack tempStack;
    STACK pTemp = &tempStack;
    InitStack(&pTemp);

    while(!isEmpty(*S) && Top(*S) > data)
    {
        Push(&pTemp, Top(*S));
        Pop(S);
    }

    Push(S, data);

    while(!isEmpty(pTemp))
    {
        Push(S, Top(pTemp));
        Pop(&pTemp);
    }
}

int Top(STACK S)
{
    return S->data[S->top];
}

void Populate(STACK *S)
{
    InsertSorted(S, -1);
    InsertSorted(S, -3);
    InsertSorted(S, -2);
    InsertSorted(S, -10);
    InsertSorted(S, -17); 
}

int main()
{
    arrStack myStack;
    STACK ptrArrStack = &myStack;
    InitStack(&ptrArrStack);
    Populate(&ptrArrStack);
    Print(ptrArrStack);

    arrStack negativeStack;
    negativeStack = getAllNegatives(ptrArrStack);

    STACK ptrNegatives = &negativeStack;
    Print(ptrNegatives);

    return 0;
}