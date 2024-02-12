#include<stdio.h>
#define SIZE 3

typedef struct{
    int data;
    int link;
}nodeType;

typedef struct{
    nodeType Node[SIZE];
    nodeType Node[SIZE+1];
    int avail;
}VirtualHeap;



typedef int CLIST;

void initCList(CLIST *C);
void initVHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int ndx);
void insertElem(CLIST *C, VirtualHeap *VH, int data); //acts as insertAtEnd
void populate(CLIST *C, VirtualHeap *VH);


void initCList(CLIST *C)
{
    *C = -1;
}


void initVHeap(VirtualHeap *VH) //version 2
{
    VH->avail = SIZE-1; // 0 1 2 
    int x;
    for(x=VH->avail; x>=0; x--) 
    {
        VH->Node[x].link = x-1;
    }
}



void insertElem(CLIST *C, VirtualHeap *VH, int data) //insert at end
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Node[ndx].data = data;

        if(*C==-1)
        {
            *C = ndx;
        }
        else
        {
            int x;
            for(x=*C; VH->Node[x].link!=-1; x=VH->Node[x].link){} //x = -1

            VH->Node[x].link = ndx;
        }

        VH->Node[ndx].link = -1;
    }
}

void displayList(CLIST C, VirtualHeap VH)
{
    int x;
    printf("\n===\nList: ");
    for(x=C; x!=-1; x=VH.Node[x].link)
    {
        printf("%d ", VH.Node[x].data);
    }

    printf("\n\n");
}


int allocSpace(VirtualHeap *VH)
{
    int retval = VH->avail;
    if(retval!=-1)
    {
        VH->avail = VH->Node[retval].link;
    }

    return retval;
}
void populate(CLIST *C, VirtualHeap *VH)
{
    insertElem(C, VH, -3);
    insertElem(C, VH, -2);
    insertElem(C, VH, 1);
}   

void getAllNegatives(CLIST C, VirtualHeap VHeap)
{
    CLIST tempC;
    VirtualHeap tempVH;
    initCList(&tempC);
    initVHeap(&tempVH);


    int x;
    // int tempCount = 0;
    //x = 2
    for(x=C; x!=-1; x=VHeap.Node[x].link)
    {
        if(VHeap.Node[x].data < 0)
        {
            insertElem(&tempC, &tempVH, VHeap.Node[x].data);
        }
    }

    displayList(tempC, tempVH);
    
}

int main()
{
    CLIST C;
    VirtualHeap VHeap;

    initCList(&C);
    initVHeap(&VHeap);

    populate(&C, &VHeap);

    displayList(C, VHeap);
    getAllNegatives(C, VHeap);
    return 0;
}
