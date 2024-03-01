#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    int data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int avail;
}VirtualHeap;

typedef int CLIST;

void deallocSpace(VirtualHeap *VH, int ndx);
int allocSpace(VirtualHeap *VH);

void insertAtBeginning(CLIST *C, VirtualHeap *VH, int data);
void insertAtEnd(CLIST *C, VirtualHeap *VH, int data);
void insertAtPos(CLIST *C, VirtualHeap *VH, int data, int pos);

void deleteAtBeginning(CLIST *C, VirtualHeap *VH);
void deleteAtEnd(CLIST *C, VirtualHeap *VH);
void deleteAtPos(CLIST *C, VirtualHeap *VH, int pos);

void deleteFirstOccur(CLIST *C, VirtualHeap *VH, int data);
void deleteAllOccur(CLIST *C, VirtualHeap *VH, int data);

void initClist(CLIST *C);
void initVHeap(VirtualHeap *VH);

void Populate(CLIST *C, VirtualHeap *VH);
void displayList(CLIST C, VirtualHeap VH);

bool isEmpty(CLIST C);
bool isFull(VirtualHeap VH);

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<MAX)
    {
        VH->Nodes[ndx].link = VH->avail;
        VH->avail = ndx;
    }
}

int allocSpace(VirtualHeap *VH)
{
    int retval = VH->avail;
    if(retval!=-1)
    {
        VH->avail = VH->Nodes[retval].link;
    }

    return retval;
}

void initClist(CLIST *C)
{
    *C = -1;
}

void initVHeap(VirtualHeap *VH)
{
    int x;
    VH->avail = MAX-1;
    for(x=VH->avail; x>0; x--)
    {
        VH->Nodes[x].link = x-1;
    }
}

void displayList(CLIST C, VirtualHeap VH)
{
    if(!isEmpty(C))
    {
        printf("\n===\nList: ");
        CLIST trav;
        for(trav=C; trav!=-1; trav=VH.Nodes[trav].link)
        {
            printf("%d ", VH.Nodes[trav].data);
        }

        printf("\n\n");
    }
}

void insertAtBeginning(CLIST *C, VirtualHeap *VH, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Nodes[ndx].data = data;
        VH->Nodes[ndx].link = *C;
        *C = ndx;
    }
}

void insertAtEnd(CLIST *C, VirtualHeap *VH, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        CLIST *trav;
        for(trav=C; *trav!=-1; trav=&(VH->Nodes[*trav].link)){}

        VH->Nodes[ndx].link = *trav; //or -1
        VH->Nodes[ndx].data = data;
        *trav = ndx;
    }
}

void insertAtPos(CLIST *C, VirtualHeap *VH, int data, int pos)
{
    if(pos>=1 && pos<=MAX)
    {
        int ndx = allocSpace(VH);
        
        if(ndx!=-1)
        {
            int ctr;
            CLIST *trav;
            for(trav=C; *trav!=-1 && ctr<pos; ctr++, trav=&(VH->Nodes[*trav].link)){}

            if(ctr==pos)
            {
                VH->Nodes[ndx].data = data;
                VH->Nodes[ndx].link = *trav;    
                *trav = ndx;
            }
        }
        
    }
}

void deleteAtBeginning(CLIST *C, VirtualHeap *VH)
{
    int ndx;
    ndx = *C;
    *C = VH->Nodes[ndx].link;
    deallocSpace(VH, ndx);
}

void deleteAtEnd(CLIST *C, VirtualHeap *VH)
{
    int ndx;
    CLIST *trav;
    for(trav=C; VH->Nodes[*trav].link!=-1; trav=&(VH->Nodes[*trav].link)){}

    ndx = *trav;
    *trav = -1;
    deallocSpace(VH, ndx);
}

void deleteAtPos(CLIST *C, VirtualHeap *VH, int pos)
{
    int ndx, ctr;
    CLIST *trav;
    for(trav=C, ctr=1; ctr<pos; trav=&(VH->Nodes[*trav].link), ctr++){}

    ndx = *trav;
    *trav = VH->Nodes[*trav].link;
    deallocSpace(VH, ndx);
}

void deleteFirstOccur(CLIST *C, VirtualHeap *VH, int data)
{
    int ndx;
    CLIST *trav;
    for(trav=C; *trav!=-1 && VH->Nodes[*trav].data!=data; trav=&(VH->Nodes[*trav].link)){}

    if(VH->Nodes[*trav].data==data)
    {
        ndx = *trav;
        *trav = VH->Nodes[ndx].link;
        deallocSpace(VH, ndx);
    }
}

void deleteAllOccur(CLIST *C, VirtualHeap *VH, int data)
{
    CLIST *trav;
    for(trav=C; *trav!=-1; )
    {
        if(VH->Nodes[*trav].data==data)
        {
            int ndx;
            ndx = *trav;
            *trav = VH->Nodes[ndx].link;
            deallocSpace(VH, ndx);
            trav=C;
        }
        else
        {
            trav=&(VH->Nodes[*trav].link);
        }
    }
}

bool isEmpty(CLIST C)
{
    return (C==-1)? true:false;
}

bool isFull(VirtualHeap VH)
{
    return (VH.avail==-1) ? true:false;
}
void Populate(CLIST *C, VirtualHeap *VH)
{
    insertAtBeginning(C, VH, 1);
    insertAtBeginning(C, VH, 1);
    insertAtBeginning(C, VH, 3);
    insertAtBeginning(C, VH, 1);
    insertAtPos(C, VH, 1, 4);
}

int main()
{
    CLIST myList;
    initClist(&myList);

    VirtualHeap myHeap;
    initVHeap(&myHeap);

    Populate(&myList, &myHeap);
    displayList(myList, myHeap);

    deleteAllOccur(&myList, &myHeap, 1);
    displayList(myList, myHeap);

    return 0;
}