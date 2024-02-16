#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef int CLIST;

typedef struct{
    int data;
    int next;
}nodeType;

typedef struct{
    nodeType Node[SIZE];
    int avail;
}VirtualHeap;

int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int ndx);

void insertAtEnd(VirtualHeap *VH, CLIST *C, int data);
void insertAtBeginning(VirtualHeap *VH, CLIST *C, int data);
void insertAtPos(VirtualHeap *VH, CLIST *C, int pos, int data);

void deleteAtEnd(VirtualHeap *VH, CLIST *C);
void deleteAtBeginning(VirtualHeap *VH, CLIST *C);
void deleteAtPos(VirtualHeap *VH, CLIST *C, int pos);

void deleteFirstOccur(VirtualHeap *VH, CLIST *C, int data);
void deleteAllOccur(VirtualHeap *VH, CLIST *C, int data);

void initVHeap(VirtualHeap *VH); //version 2
void initList(CLIST *C);
void displayList(CLIST C, VirtualHeap VH);
void populateList(CLIST *C, VirtualHeap *VH);

int countElem(CLIST C, VirtualHeap VH);


void initList(CLIST *C)
{
    *C = -1;
}

void initVHeap(VirtualHeap *VH)
{
    int x;
    VH->avail = SIZE-1;
    for(x=VH->avail; x>=0; x--)
    {
        VH->Node[x].next = x-1;
    }
}

int allocSpace(VirtualHeap *VH)
{
    int retval = VH->avail;
    if(retval!=-1)
    {
        VH->avail = VH->Node[retval].next;
    }
    return retval;
}

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<SIZE)
    {
        VH->Node[ndx].next = VH->avail;
        VH->avail = ndx;
    }
}

void insertAtEnd(VirtualHeap *VH, CLIST *C, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Node[ndx].data = data;
        VH->Node[ndx].next = -1;

        if(*C==-1)
        {
            *C = ndx;
        }
        else
        {
            CLIST *trav;
            for(trav=C; *trav!=-1; trav=&(VH->Node[*trav].next)){}
            
            *trav = ndx;
        }
    }
}

void insertAtBeginning(VirtualHeap *VH, CLIST *C, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Node[ndx].data = data;
        VH->Node[ndx].next = *C;
        *C = ndx;
    }
}

void insertAtPos(VirtualHeap *VH, CLIST *C, int pos, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Node[ndx].data = data;

        if(pos==1)
        {
            VH->Node[ndx].next = *C;
            *C = ndx;
        }
        else
        {
            CLIST *trav;
            int x = pos-1, ctr;

            for(ctr=0, trav = C; *trav!=-1 && ctr<x; ctr++, trav = &(VH->Node[*trav].next)){}

            VH->Node[ndx].next = *trav;
            *trav = ndx;
        }
    }
}

void deleteAtEnd(VirtualHeap *VH, CLIST *C)
{
    int ndx;
    CLIST *trav;
    for(trav=C; *trav!=-1 && VH->Node[*trav].next!=-1; trav=&(VH->Node[*trav].next)){}

    ndx = *trav;
    *trav = -1;

    deallocSpace(VH, ndx);
}

void deleteAtBeginning(VirtualHeap *VH, CLIST *C)
{
    int ndx;
    ndx = *C;
    *C = VH->Node[ndx].next;
    
    deallocSpace(VH, ndx);
}


void deleteAtPos(VirtualHeap *VH, CLIST *C, int pos)
{
    if(pos>0 && pos<=countElem(*C, *VH))
    {
        int ctr, ndx, x = pos-1;
        CLIST *trav;

        for(trav=C, ctr = 0; *trav!=-1 && ctr < x; ctr++, trav=&(VH->Node[*trav].next)){}

        ndx = *trav;
        *trav = VH->Node[ndx].next;

        deallocSpace(VH, ndx);
    }
}

void displayList(CLIST C, VirtualHeap VH)
{
    printf("\n===\n");
    printf("List: ");

    int x;
    for(x=C; x!=-1; x=VH.Node[x].next)
    {
        printf("%d ", VH.Node[x].data);
    }

    printf("\n\n");
}

int countElem(CLIST C, VirtualHeap VH)
{
    int count=1, x;
    for(x=C; x!=-1; count++, x=VH.Node[x].next){}

    return count;
}

void populateList(CLIST *C, VirtualHeap *VH)
{
    insertAtEnd(VH, C, 1);
    insertAtEnd(VH, C, 2);
    insertAtEnd(VH, C, 3);
    insertAtBeginning(VH, C, 3);
    insertAtPos(VH, C, 1, 3);

}

void deleteFirstOccur(VirtualHeap *VH, CLIST *C, int data)
{
    CLIST *trav;
    int ndx;

    for(trav=C; *trav!=-1 && VH->Node[*trav].data!=data; trav=&(VH->Node[*trav].next)){}

    if(*trav!=-1)
    {
        ndx = *trav;
        *trav = VH->Node[ndx].next;

        deallocSpace(VH, ndx);
    }
}

void deleteAllOccur(VirtualHeap *VH, CLIST *C, int data)
{
    CLIST *trav;
    for(trav=C; *trav!=-1; )
    {
        if(VH->Node[*trav].data==data)
        {
            int ndx;
            ndx = *trav;
            *trav = VH->Node[ndx].next;
            trav=C;
            deallocSpace(VH, ndx);
        }
        else
        {
            trav=&(VH->Node[*trav].next);
        }
    }
}


int main()
{
    CLIST myList;
    VirtualHeap myHeap;
    initList(&myList);
    initVHeap(&myHeap);
    populateList(&myList, &myHeap);
    displayList(myList, myHeap);

    // deleteAtBeginning(&myHeap, &myList);
    // deleteAtEnd(&myHeap, &myList);
    // deleteAtPos(&myHeap, &myList, 3);

    deleteFirstOccur(&myHeap, &myList, 4);
    deleteAllOccur(&myHeap, &myList, 3);
    displayList(myList, myHeap);
    return 0;
}