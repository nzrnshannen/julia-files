#include<stdio.h>
#include<stdbool.h>

#define SIZE 5

typedef struct{
    char elem;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[SIZE];
    int avail;
}VirtualHeap;

typedef int CLIST;

int allocSpace(VirtualHeap *VH)
{
    int retval = VH->avail;
    if(retval!=-1)
    {
        VH->avail = VH->Nodes[retval].link;
    }

    return retval;
}

void initVirtualHeap(VirtualHeap *VH)
{
    VH->avail = SIZE-1;
    int x;
    for(x=VH->avail; x>=0; x--)
    {
        VH->Nodes[x].link = x-1;
    }
}

void initCList(CLIST *C)
{
    *C = -1;
}

void addElem(CLIST *C, VirtualHeap *VH, char elem)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Nodes[ndx].elem = elem;
        VH->Nodes[ndx].link= -1;

        if(*C==-1)
        {
            *C = ndx;
        }
        else
        {
            int x;
            for(x=*C; VH->Nodes[x].link!=-1; x=VH->Nodes[x].link){}

            VH->Nodes[x].link = ndx;
        }
    }
}

void displayList(CLIST C, VirtualHeap VH)
{
    printf("\n====\nList: ");
    int x;
    for(x=C; x!=-1; x=VH.Nodes[x].link)
    {
        printf("%c ", VH.Nodes[x].elem);
    }
    printf("\n");
}

int main()
{
    VirtualHeap Vheap;
    CLIST C;

    initCList(&C);
    initVirtualHeap(&Vheap);
    addElem(&C, &Vheap, 'A');
    addElem(&C, &Vheap, 'B');
    addElem(&C, &Vheap, 'C');
    addElem(&C, &Vheap, 'A');
    addElem(&C, &Vheap, 'A');

    addElem(&C, &Vheap, 'F');
    displayList(C, Vheap);
    return 0;
}