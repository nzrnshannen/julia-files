#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[SIZE];
    int avail;
}myHeap, *VirtualHeap;

typedef int CLIST;

void initCLIST(CLIST *C);
void initVHeap(VirtualHeap *VH); //version 2
void insertSorted(CLIST *C, VirtualHeap *VH, int data);
myHeap getAllNegatives(CLIST C, VirtualHeap VH);
int allocSpace(VirtualHeap *VH);
// void deallocSpace(VirtualHeap* VH, int ndx);
void display(CLIST C, VirtualHeap VH);
bool isEmpty(CLIST C);
bool isFull(VirtualHeap VH);
void populate(CLIST *C, VirtualHeap *VH);

void initCLIST(CLIST *C)
{
    *C = -1;
}

void initVHeap(VirtualHeap *VH)
{
    (*VH)->avail = SIZE-1;
    int x;
    for(x=(*VH)->avail; x>=0; x--)
    {
        (*VH)->Nodes[x].link = x-1;
    }
}

void insertSorted(CLIST *C, VirtualHeap *VH, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        (*VH)->Nodes[ndx].data = data;
        (*VH)->Nodes[ndx].link = -1;
        if(isEmpty(*C))
        {
            (*VH)->Nodes[ndx].link = *C;
            *C = ndx;
        }
        else
        {
            int x;
            for(x=*C; (*VH)->Nodes[x].link!=-1 && (*VH)->Nodes[x].data < data; x=(*VH)->Nodes[x].link){}
        
            //should have used ppn style for this lmao
            if(x==*C && (*VH)->Nodes[x].data > data)
            {
                (*VH)->Nodes[x].link = ndx;
                *C = ndx;
            }

            int y;
            for(y=*C; (*VH)->Nodes[y].link!=x; y=(*VH)->Nodes[y].link){}

            (*VH)->Nodes[ndx].link = (*VH)->Nodes[y].link;
            (*VH)->Nodes[y].link = ndx;
            
        }

    }
}

void display(CLIST C, VirtualHeap VH)
{
    if(!isEmpty(C))
    {
        printf("\n===\nList: ");
        int x;
        for(x=C; x!=-1; x=VH->Nodes[x].link)
        {
            printf("%d ", VH->Nodes[x].data);
        }

        printf("\n\n");
    }
}

bool isFull(VirtualHeap VH)
{
    return (VH->avail==-1) ? true : false;
}

bool isEmpty(CLIST C)
{
    return (C==-1) ? true : false;
}

myHeap getAllNegatives(CLIST C, VirtualHeap VH)
{
    myHeap tempHeap;
    VirtualHeap ptempHeap = &tempHeap;
    initVHeap(&ptempHeap);

    CLIST tempH;
    initCLIST(&tempH);

    int x, y=1;
    for(x=C; x!=-1; x=VH->Nodes[x].link)
    {
        if(VH->Nodes[x].data < 0)
        {
            if(y==SIZE-1 && x!=-1)
            {
                printf("\n\t>> Temp stack is full. Last negative number is: %d<<\n\n", VH->Nodes[x].data);
            }

            insertSorted(&tempH, &ptempHeap, VH->Nodes[x].data);
            y++;
        }
    }

    if(y>1)
    {
        int ndx = allocSpace(&ptempHeap);
        if(ndx!=-1)
        {
            ptempHeap->Nodes[ndx].data = y-1;
            ptempHeap->Nodes[ndx].link = tempH;
            tempH = ndx;
        }
    }

    return tempHeap;
}

int allocSpace(VirtualHeap *VH)
{
    int retval = (*VH)->avail;
    if(retval!=-1)
    {
        (*VH)->avail = (*VH)->Nodes[retval].link;
    }

    return retval;
}

void populate(CLIST *C, VirtualHeap *VH)
{
    insertSorted(C, VH, 3);
    insertSorted(C, VH, 2);
    insertSorted(C, VH, 1);
    insertSorted(C, VH, -5);
    insertSorted(C, VH, -12);
}
int main()
{
    CLIST head1, head2;
    myHeap heap1, heap2;
    
    VirtualHeap vheap1, vheap2;
    vheap1 = &heap1;
    vheap2 = &heap2;

    initCLIST(&head1);
    initCLIST(&head2);

    initVHeap(&vheap1);
    initVHeap(&vheap2);

    populate(&head1, &vheap1);

    display(head1, vheap1);
    return 0;
}

