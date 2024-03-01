#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    int data;
    int link;
}nodeType;

typedef struct{
    nodeType Node[SIZE];
    int avail;
}myHeap, *VirtualHeap;

typedef int CLIST;

void initCList(CLIST *C);
void initVHeap(VirtualHeap *VH); //version 2
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int ndx);

void insertAtBeginning(CLIST *C, VirtualHeap *VH, int data);
void insertAtEnd(CLIST *C, VirtualHeap *VH, int data);
void insertAtPos(CLIST *C, VirtualHeap *VH, int data, int pos);

void deleteAtBeginning(CLIST *C, VirtualHeap *VH);
void deleteAtEnd(CLIST *C, VirtualHeap *VH);
void deleteAtPos(CLIST *C, VirtualHeap *VH, int pos);

void deleteFirstOccurrence(CLIST *C, VirtualHeap *VH, int data);
void deleteAllOccurrence(CLIST *C, VirtualHeap *VH, int data);

bool isEmpty(CLIST C);
bool isFull(CLIST C);
void populate(CLIST *C, VirtualHeap *VH);
void print(CLIST C, VirtualHeap VH);


void initCList(CLIST *C)
{
    *C = -1;
}

void initVHeap(VirtualHeap *VH)
{
    int x;
    (*VH)->avail = SIZE-1;
    for(x=(*VH)->avail; x>=0; x--)
    {
        (*VH)->Node[x].link = x-1;
    }
}

int allocSpace(VirtualHeap *VH)
{
    int retval = (*VH)->avail;
    if(retval!=-1)
    {
        (*VH)->avail = (*VH)->Node[retval].link;
    }

    return retval;
}

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<SIZE)
    {
        (*VH)->Node[ndx].link = (*VH)->avail;
        (*VH)->avail = ndx;
    }
}

void insertAtBeginning(CLIST *C, VirtualHeap *VH, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        (*VH)->Node[ndx].data = data;
        (*VH)->Node[ndx].link = *C;
        *C = ndx;
    }
}

void insertAtEnd(CLIST *C, VirtualHeap *VH, int data)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        (*VH)->Node[ndx].data = data;

        if(isEmpty(*C))
        {
            *C = ndx;
        }
        else
        {
            int x;
            for(x=*C; (*VH)->Node[x].link!=-1; x=(*VH)->Node[x].link){}

            (*VH)->Node[x].link = ndx;
        }

        (*VH)->Node[ndx].link = -1;

    }
}

void insertAtPos(CLIST *C, VirtualHeap *VH, int data, int pos)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1 && pos>=1 && pos<=SIZE)
    {
        (*VH)->Node[ndx].data = data;
        if(pos==1)
        {
            (*VH)->Node[ndx].link = *C;
            *C = ndx;
        }
        else if(pos==SIZE)
        {
            int x;

            printf("\nyes\n");
            for(x=*C; (*VH)->Node[x].link!=-1; x=(*VH)->Node[x].link){}
            (*VH)->Node[x].link = ndx;
            (*VH)->Node[ndx].link = -1;
        }   
        else
        {
            int x, ctr;
            for(x=*C, ctr=1; (*VH)->Node[x].link!=-1 && ctr<pos-1; x=(*VH)->Node[x].link, ctr++){}
            (*VH)->Node[ndx].link = (*VH)->Node[x].link;
            (*VH)->Node[x].link = ndx;
        }
    }
}

void deleteAtBeginning(CLIST *C, VirtualHeap *VH)
{
    if(!isEmpty(*C))
    {
        int ndx;
        ndx = *C;
        *C = (*VH)->Node[ndx].link;
        deallocSpace(VH, ndx);
    }
}

void deleteAtEnd(CLIST *C, VirtualHeap *VH)
{
    if(!isEmpty(*C))
    {
        int ndx, x;
        for(x=*C; (*VH)->Node[x].link!=-1; x=(*VH)->Node[x].link){}

        if(x==*C)
        {
            ndx = *C;
            *C = -1;
        }
        else
        {
            int y;
            for(y=*C; (*VH)->Node[y].link!=x; y=(*VH)->Node[y].link){}

            (*VH)->Node[y].link = -1;
            ndx = x;
        }
        
        deallocSpace(VH, ndx);
    }
}

void deleteAtPos(CLIST *C, VirtualHeap *VH, int pos)
{
    if(!isEmpty(*C) && pos>=1 && pos<SIZE)
    {
        int ndx, x, y, ctr;
        if(pos==1)
        {
            deleteAtBeginning(C, VH);
        }
        else if(pos==SIZE)
        {
            for(x=*C; (*VH)->Node[x].link!=-1; x=(*VH)->Node[x].link){}

            for(y=*C; (*VH)->Node[y].link!=x; y=(*VH)->Node[y].link){}
            (*VH)->Node[y].link = -1;

            deallocSpace(VH, x);
        }
        else
        {
            for(x=*C, ctr=0; ctr<pos-1; ctr++, x=(*VH)->Node[x].link){}

            for(y=*C; (*VH)->Node[y].link!=x; y=(*VH)->Node[y].link){}

            (*VH)->Node[y].link = (*VH)->Node[x].link;
            ndx = x;

            deallocSpace(VH, ndx);
        }    
    }
}

void deleteFirstOccurrence(CLIST *C, VirtualHeap *VH, int data)
{
    if(!isEmpty(*C))
    {
        int x;
        for(x=*C; x!=-1 && (*VH)->Node[x].data!=data; x=(*VH)->Node[x].link){}

        if((*VH)->Node[x].data==data)
        {
            if(x==*C)
            {
                deleteAtBeginning(C, VH);
            }
            else if(x==SIZE-1)
            {
                deleteAtEnd(C, VH);
            }
            else
            {
                int y;
                for(y=*C; (*VH)->Node[y].link!=x; y=(*VH)->Node[y].link){}
                (*VH)->Node[y].link = (*VH)->Node[x].link;
                deallocSpace(VH, x);
            }
        }
    }
}

void deleteAllOccurrence(CLIST *C, VirtualHeap *VH, int data)
{
    if(!isEmpty(*C))
    {
        int x;
        for(x=*C; x!=-1; )
        {
            if((*VH)->Node[x].data == data)
            {
                if(x==*C)
                {
                    deleteAtBeginning(C, VH);
                }
                else if(x==SIZE-1)
                {
                    deleteAtEnd(C, VH);
                }
                else
                {
                    int y;
                    for(y=*C; (*VH)->Node[y].link!=x; y=(*VH)->Node[y].link){}

                    (*VH)->Node[y].link = (*VH)->Node[x].link;
                    deallocSpace(VH, x);
                }

                x=*C;
            }
            else
            {
                x=(*VH)->Node[x].link;
            }
        }
    }
}

bool isEmpty(CLIST C)
{
    return (C==-1)? true : false;
}

bool isFull(CLIST C)
{
    return (C==SIZE) ? true : false;
}

void populate(CLIST *C, VirtualHeap *VH)
{
    insertAtBeginning(C, VH, 1);
    insertAtBeginning(C, VH, 4);
    insertAtEnd(C, VH, 1);
    insertAtBeginning(C, VH, 1);
    insertAtPos(C, VH, 100, 3);
}

void print(CLIST C, VirtualHeap VH)
{
    if(!isEmpty(C))
    {
        int x;
        printf("\n===\nList: ");
        for(x=C; x!=-1; x=VH->Node[x].link)
        {
            printf("%d ", VH->Node[x].data);
        }

        printf("\n\n");
    }
}

int main()
{
    CLIST Head;
    initCList(&Head);
    myHeap Heap;
    VirtualHeap pHeap = &Heap;
    initVHeap(&pHeap);

    populate(&Head, &pHeap);

    print(Head, pHeap);

    deleteAllOccurrence(&Head, &pHeap, 1);
    print(Head, pHeap);
    return 0;
}