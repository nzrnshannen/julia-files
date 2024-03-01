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

void initCStack(CStack *C);
void initVHeap(VirtualHeap *VH);
void Push(CStack *C, VirtualHeap *VH, int data);
void Pop(CStack *C, VirtualHeap *VH);
void DeleteFirstOccur(CStack *C, VirtualHeap *VH, int data);
void DeleteAllOccur(CStack *C, VirtualHeap *VH, int data);
bool isFull(VirtualHeap VH);
bool isEmpty(CStack C);
void Print(CStack C, VirtualHeap VH);
void Populate(CStack *C, VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int ndx);
int Top(CStack C, VirtualHeap VH);

bool isFull(VirtualHeap VH)
{
    return (VH.Avail==-1) ? true : false;
}

bool isEmpty(CStack C)
{
    return (C==-1) ? true : false;
}

void initCStack(CStack *C)
{
    *C =-1;
}

void initVHeap(VirtualHeap *VH)
{
    VH->Avail = MAX-1;  
    int x;
    for(x=VH->Avail; x>=0; x--)
    {
        VH->Node[x].link = x-1;
    }
}

int Top(CStack C, VirtualHeap VH)
{
    return VH.Node[C].data;
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

void Push(CStack *C, VirtualHeap *VH, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Node[ndx].data = data;
        VH->Node[ndx].link = *C;
        *C = ndx;
    }
}

void Pop(CStack *C, VirtualHeap *VH)
{
    if(!isEmpty(*C))
    {
        int ndx;
        ndx = *C;
        *C =VH->Node[ndx].link;
        deallocSpace(VH, ndx);
    }
}

void DeleteFirstOccur(CStack *C, VirtualHeap *VH, int data)
{
    if(!isEmpty(*C))
    {
        CStack tempStack;
        VirtualHeap tempHeap;

        initCStack(&tempStack);
        initVHeap(&tempHeap);

        while(!isEmpty(*C))
        {
            Push(&tempStack, &tempHeap, Top(*C, *VH));
            Pop(C, VH);   
        }

        while(!isEmpty(tempStack) && Top(tempStack, tempHeap)!=data)
        {
            Push(C, VH, Top(tempStack, tempHeap));
            Pop(&tempStack, &tempHeap);
        }

        if(Top(tempStack, tempHeap)==data)
        {
            Pop(&tempStack, &tempHeap);
        }

        while(!isEmpty(tempStack))
        {
            Push(C, VH, Top(tempStack, tempHeap));
            Pop(&tempStack, &tempHeap);
        }
    }
}

void DeleteAllOccur(CStack *C, VirtualHeap *VH, int data)
{
    if(!isEmpty(*C))
    {
        CStack tempStack;
        VirtualHeap tempHeap;
        initCStack(&tempStack);
        initVHeap(&tempHeap);

        while(!isEmpty(*C))
        {
            if(Top(*C, *VH)!=data)
            {
                Push(&tempStack, &tempHeap, Top(*C, *VH));
            }
            Pop(C, VH);
        }

        while(!isEmpty(tempStack))
        {
            Push(C, VH, Top(tempStack, tempHeap));
            Pop(&tempStack, &tempHeap);
        }
    }
}

void Print(CStack C, VirtualHeap VH)
{
    if(!isEmpty(C))
    {
        CStack tempStack;
        VirtualHeap tempHeap;
        initCStack(&tempStack);
        initVHeap(&tempHeap);
        
        printf("\n===\nStack: ");
        while(!isEmpty(C))
        {
            Push(&tempStack, &tempHeap, Top(C, VH));
            Pop(&C, &VH);
        }

        while(!isEmpty(tempStack))
        {
            printf("%d ", Top(tempStack, tempHeap));
            Push(&C, &VH, Top(tempStack, tempHeap));
            Pop(&tempStack, &tempHeap);
        }

        printf("\n\n");
    }
}

void Populate(CStack *C, VirtualHeap *VH)
{
    Push(C, VH, 1);
    Push(C, VH, 1);
    Push(C, VH, 3);
    Push(C, VH, 4);
    Push(C, VH, 1);
}

int main()
{
    CStack myStack;
    VirtualHeap myHeap;
    initCStack(&myStack);
    initVHeap(&myHeap);

    Populate(&myStack, &myHeap);
    Print(myStack, myHeap);

    DeleteAllOccur(&myStack, &myHeap, 1);
    Print(myStack, myHeap);
    return 0;
}