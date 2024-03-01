#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef int CLIST;

typedef struct{
    int data;
    int link;
}nodetype;

typedef struct{
    nodetype Node[MAX];
    int avail;
}VirtualHeap;

typedef int CLIST;

int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int ndx);

void insertSorted(CLIST *C, VirtualHeap *VH, int data);
void getAllNegatives(CLIST C, VirtualHeap VH);

void Populate(CLIST *C, VirtualHeap *VH);
void displayList(CLIST C, VirtualHeap VH);

bool isEmpty(CLIST C);
bool isFull(VirtualHeap VH);

void initCList(CLIST *C);
void initVHeap(VirtualHeap *VH);

bool isEmpty(CLIST C)
{
    return (C==-1)? true: false;
}

bool isFull(VirtualHeap VH)
{
    return (VH.avail==-1) ? true: false;
}

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<MAX)
    {
        VH->Node[ndx].link = VH->avail;
        VH->avail = ndx;
    }
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

void initCList(CLIST *C)
{
    *C = -1;
}

void initVHeap(VirtualHeap *VH)
{
    VH->avail = MAX-1;
    int x;
    for(x=VH->avail; x>=0; x--)
    {
        VH->Node[x].link = x-1;
    }
}

void displayList(CLIST C, VirtualHeap VH)
{
    if(!isEmpty(C))
    {
        printf("\n===\nList: ");
        CLIST trav;
        for(trav=C; trav!=-1; trav=VH.Node[trav].link)
        {
            printf("%d ", VH.Node[trav].data);
        }

        printf("\n\n");
    }
}

void insertSorted(CLIST *C, VirtualHeap *VH, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        CLIST *trav;
        VH->Node[ndx].data = data;
        for(trav=C; *trav!=-1 && VH->Node[*trav].data < data; trav=&(VH->Node[*trav].link)){}

        VH->Node[ndx].link = *trav;
        *trav = ndx;
    }
}

void getAllNegatives(CLIST C, VirtualHeap VH)
{
    CLIST tempList;
    VirtualHeap tempHeap;
    initCList(&tempList);
    initVHeap(&tempHeap);

    int count = 0;

    CLIST trav;
    for(trav=C; trav!=-1; trav=VH.Node[trav].link)
    {
        if(VH.Node[trav].data<0)
        {
            if(count==MAX-1)
            {
                printf("\n\n\t >> Temporary stack full. Last negative number is: %d <<\n", VH.Node[trav].data);
            }
            else
            {
                insertSorted(&tempList, &tempHeap, VH.Node[trav].data);
            }
            count++;
        }
    }

    int ndx = allocSpace(&tempHeap);
    if(ndx!=-1)
    {
        tempHeap.Node[ndx].data = count;

        tempHeap.Node[ndx].link = tempList;
        tempList = ndx;
    }

    displayList(tempList, tempHeap);
}
void Populate(CLIST *C, VirtualHeap *VH)
{
    insertSorted(C, VH, -9);
    insertSorted(C, VH, -6);
    insertSorted(C, VH, -10);
    insertSorted(C, VH, -1);
    insertSorted(C, VH, -5);
}

int main()
{
    CLIST myList;
    VirtualHeap myHeap;
    initCList(&myList);
    initVHeap(&myHeap);

    

    Populate(&myList, &myHeap);
    displayList(myList, myHeap);

    getAllNegatives(myList, myHeap);
    return 0;
}