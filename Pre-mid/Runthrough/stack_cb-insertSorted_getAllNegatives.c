#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    int data;
    int link;
}nodeType;

typedef struct{
    nodeType Node[MAX];
    int Avail;
}VirtualHeap;

typedef int CStack;

void initCStack(CStack *S);
void initVHeap(VirtualHeap *VH);
void Push(CStack *S, VirtualHeap *VH, int data);
void Pop(CStack *S, VirtualHeap *VH);
void InsertSorted(CStack *S, VirtualHeap *VH, int data);
void getAllNegatives(CStack S, VirtualHeap VH);
bool isFull(VirtualHeap VH);
bool isEmpty(CStack S);
void Print(CStack S, VirtualHeap VH);
void Populate(CStack *S, VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int ndx);
int Top(CStack S, VirtualHeap VH);

void initCStack(CStack *S)
{
    *S = -1;
}

void initVHeap(VirtualHeap *VH)
{
    int x;
    VH->Avail = MAX-1;
    for(x=VH->Avail; x>=0; x--)
    {
        VH->Node[x].link = x-1;
    }
}

void Push(CStack *S, VirtualHeap *VH, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Node[ndx].data = data;
        VH->Node[ndx].link = *S;
        *S = ndx;
    }
}

void Pop(CStack *C, VirtualHeap *VH)
{
    int ndx;
    ndx = *C;
    *C = VH->Node[ndx].link;
    deallocSpace(VH, ndx);
}

bool isEmpty(CStack S)
{
    return (S==-1)? true : false;
}

bool isFull(VirtualHeap VH)
{
    return (VH.Avail==-1) ? true : false;
}

int allocSpace(VirtualHeap *VH)
{
    int retval = VH->Avail;
    if(retval!=-1)
    {
        VH->Avail = VH->Node[retval].link;
    }
    return retval;
}

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<MAX)
    {
        VH->Node[ndx].link = VH->Avail;
        VH->Avail = ndx;
    }
}

int Top(CStack S, VirtualHeap VH)
{
    return VH.Node[S].data;
}

void Print(CStack S, VirtualHeap VH)
{
    if(!isEmpty(S))
    {
        CStack tempStack;
        VirtualHeap tempHeap;
        initCStack(&tempStack);
        initVHeap(&tempHeap);

        printf("\n===\nStack: ");
        while(!isEmpty(S))
        {
            Push(&tempStack, &tempHeap, Top(S, VH));
            Pop(&S, &VH);
        }

        while(!isEmpty(tempStack))
        {
            printf("%d ", Top(tempStack, tempHeap));
            Push(&S, &VH, Top(tempStack, tempHeap));
            Pop(&tempStack, &tempHeap);
        }

        printf("\n\n");
    }
}

void InsertSorted(CStack *S, VirtualHeap *VH, int data)
{
    CStack tempStack;
    VirtualHeap tempHeap;

    initCStack(&tempStack);
    initVHeap(&tempHeap);

    while(!isEmpty(*S) && Top(*S, *VH) > data)
    {
        Push(&tempStack, &tempHeap, Top(*S, *VH));
        Pop(S, VH);
    }

    Push(S, VH, data);

    while(!isEmpty(tempStack))
    {
        Push(S, VH, Top(tempStack, tempHeap));
        Pop(&tempStack, &tempHeap);
    }
}

void Populate(CStack *S, VirtualHeap *VH)
{
    InsertSorted(S, VH, -11);
    InsertSorted(S, VH, -5);
    InsertSorted(S, VH, -10);
    InsertSorted(S, VH, -21);
    InsertSorted(S, VH, -7);
}

void getAllNegatives(CStack S, VirtualHeap VH)
{
    if(!isEmpty(S))
    {
        CStack tempStack, tempNega;
        VirtualHeap tempHeap, tempNegaHeap;

        int count = 0;
        initCStack(&tempStack);
        initCStack(&tempNega);
        initVHeap(&tempHeap);
        initVHeap(&tempNegaHeap);

        while(!isEmpty(S))
        {
            if(Top(S, VH) < 0)
            {
                if(count==MAX-1)
                {
                    printf("\n\n\t>> Temporary stack is full. Last negative element is: %d \n", Top(S, VH));
                }
                else
                {
                    Push(&tempNega, &tempNegaHeap, Top(S, VH));
                }
                count++;
            }
            Push(&tempStack, &tempHeap, Top(S, VH));
            Pop(&S, &VH);
        }


        while(!isEmpty(tempStack))
        {
            Push(&S, &VH, Top(tempStack, tempHeap));
            Pop(&tempStack, &tempHeap);
        }
        
        Push(&tempNega, &tempNegaHeap, count);

        // Print(tempNega, tempNegaHeap);

        CStack printStack;
        VirtualHeap printHeap;
        initCStack(&printStack);
        initVHeap(&printHeap);

        while(!isEmpty(tempNega))
        {
            Push(&printStack, &printHeap, Top(tempNega, tempNegaHeap));
            Pop(&tempNega, &tempNegaHeap);
        }

        Print(printStack, printHeap);
    }
}

int main()
{
    CStack myStack;
    VirtualHeap myHeap;

    initCStack(&myStack);
    initVHeap(&myHeap);

    Populate(&myStack, &myHeap);
    Print(myStack, myHeap);
    getAllNegatives(myStack, myHeap);
    return 0;
}
