#include<stdio.h>
#include<stdbool.h>

#define SIZE 5

typedef struct{
    char elem;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[SIZE];
    int Avail;
}VirtualHeap, *VHeap;

typedef int *CLIST;

bool isEmpty(CLIST C);

void deallocSpace(VHeap *VH, int ndx);
int allocSpace(VHeap *VH);

void insertAtBeginning(CLIST *C, VHeap *VH, char elem);
void insertAtEnd(CLIST *C, VHeap *VH, char elem);
void insertAtPos(CLIST *C, VHeap *VH, int pos, char elem);
void deleteAtBeginning(CLIST *C, VHeap *VH);
void deleteAtEnd(CLIST *C, VHeap *VH);
void deleteAtPos(CLIST *C, VHeap *VH, int pos);
void deleteFirstOccur(CLIST *C, VHeap *VH, char elem);
void deleteAllOccur(CLIST *C, VHeap *VH, char elem);

void initVirtualHeap(VHeap *VH);
void initCList(CLIST *C);
void displayList(CLIST C, VHeap VH);
void populate(CLIST *C, VHeap *VH);


bool isEmpty(CLIST C)
{
    return(*C==-1)? true: false;
}

void initVirtualHeap(VHeap *VH)
{
    (*VH)->Avail = 0;
    int x;
    for(x=0; x<SIZE-1; x++)
    {
        (*VH)->Nodes[x].link = x+1; //making the link part
    }

    (*VH)->Nodes[x].link = -1;
}

void initCList(CLIST *C)
{
    **C = -1;
}

int allocSpace(VHeap *VH)
{
    int retval = (*VH)->Avail;
    if(retval!=-1)
    {
        (*VH)->Avail = (*VH)->Nodes[retval].link;
    }

    return retval;
}

void deallocSpace(VHeap *VH, int ndx)
{
    if(ndx>=0 && ndx < SIZE)
    {
        (*VH)->Nodes[ndx].link = (*VH)->Avail;
        (*VH)->Avail = ndx;
    }
}

void insertAtBeginning(CLIST *C, VHeap *VH, char elem)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        (*VH)->Nodes[ndx].elem = elem;
        (*VH)->Nodes[ndx].link = **C;
        **C = ndx;
    }
    else
    {
        printf("\n\tList is full!\n\n");
    }
}

void insertAtEnd(CLIST *C, VHeap *VH, char elem)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        (*VH)->Nodes[ndx].elem = elem;
        (*VH)->Nodes[ndx].link = -1;

        if(isEmpty(*C))
        {
            **C = -1;
        }
        else
        {
            int x;
            for(x=**C; (*VH)->Nodes[x].link!=-1; x=(*VH)->Nodes[x].link){}
            (*VH)->Nodes[x].link = ndx;
        }
    }
    else
    {
        printf("\n\tList is full!\n\n");
    }
}

void insertAtPos(CLIST *C, VHeap *VH, int pos, char elem)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        (*VH)->Nodes[ndx].elem = elem;

        if(isEmpty(*C))
        {
            **C = ndx;
            (*VH)->Nodes[ndx].link=-1;
        }
        else if(pos==1)
        {
            insertAtBeginning(C, VH, elem);
        }
        else
        {
            int ctr, x, y;
            for(ctr=0, y=**C; ctr<pos-1 && y!=-1; ctr++, y=(*VH)->Nodes[y].link){}

            for(x=**C; (*VH)->Nodes[x].link!=y; x=(*VH)->Nodes[x].link){}

            (*VH)->Nodes[ndx].link = y;
            (*VH)->Nodes[x].link = ndx;
        }
    }
    else
    {
        printf("\n\tList is full!\n\n");
    }
}

void deleteAtBeginning(CLIST *C, VHeap *VH)
{
    int ndx = **C;
    **C = (*VH)->Nodes[ndx].link;
    deallocSpace(VH, ndx);
}

void deleteAtEnd(CLIST *C, VHeap *VH)
{
    int x;
    for(x=**C; (*VH)->Nodes[x].link!=-1; x=(*VH)->Nodes[x].link){}

    int y;
    for(y=**C; (*VH)->Nodes[y].link!=x; y=(*VH)->Nodes[y].link){}

    (*VH)->Nodes[y].link=-1;
    deallocSpace(VH, x);
}

void deleteAtPos(CLIST *C, VHeap *VH, int pos)
{
    if(isEmpty(*C))
    {
        printf("\n\n\tList is empty!\n\n");
    }
    else if(pos>SIZE || pos < 1)
    {
        printf("\n\n\tInvalid position!\n\n");
    }
    else
    {
        if(pos==1)
        {
            deleteAtBeginning(C, VH);
        }
        else
        {
            int ctr, x, y;
            for(y=**C, ctr=0; ctr<pos-1 && y!=-1; y=(*VH)->Nodes[y].link, ctr++){}

            for(x=**C; (*VH)->Nodes[x].link!=y; x=(*VH)->Nodes[x].link){}

            (*VH)->Nodes[x].link = (*VH)->Nodes[y].link;
            deallocSpace(VH, y);
        }
    }
}

void deleteFirstOccur(CLIST *C, VHeap *VH, char elem)
{
    if(isEmpty(*C))
    {
        printf("\n\n\\tEmpty list!\n\n");
    }
    else
    {
        int x;
        for(x=**C; x!=-1 && (*VH)->Nodes[x].elem!=elem; x=(*VH)->Nodes[x].link){}

        if(x==**C)
        {
            **C = (*VH)->Nodes[x].link;
            deallocSpace(VH, x);
        }
        else
        {
            int y;
            for(y=**C; (*VH)->Nodes[y].link!=x; y=(*VH)->Nodes[y].link){}

            (*VH)->Nodes[y].link = (*VH)->Nodes[x].link;
            deallocSpace(VH, x);
        }
    }
}

void deleteAllOccur(CLIST *C, VHeap *VH, char elem)
{
    if(isEmpty(*C))
    {
        printf("\n\n\tEmpty list!\n\n");
    }
    else
    {
        int x;
        for(x=**C; x!=-1; )
        {
            if((*VH)->Nodes[x].elem==elem)
            {
                if(x==**C)
                {
                    **C = (*VH)->Nodes[**C].link;
                    deallocSpace(VH, x);
                }
                else
                {
                    int y;
                    for(y=**C; (*VH)->Nodes[y].link!=x; y=(*VH)->Nodes[y].link){}
                    (*VH)->Nodes[y].link = (*VH)->Nodes[x].link;
                    deallocSpace(VH, x);
                }

                x = **C; //if we don't have this line, there would be a logical error
                //since x is the ndx of the node to be deleted, 
                //we also need to update x after deallocSpace
                //since x (before updating) is now a node that belongs to 'avail nodes'
                //and avail nodes doesn't belong to our list yet
                //we're like accessing the link part of the list that doesn't exist
            }
            else
            {
                x = (*VH)->Nodes[x].link;
            }
        }
    }
}


void displayList(CLIST C, VHeap VH)
{
    if(isEmpty(C))
    {
        printf("\n\n\tEmpty list!\n\n");
    }
    else
    {
        int x;
        printf("\n===================\nList: ");
        for(x=*C; x!=-1; x=VH->Nodes[x].link)
        {
            printf("%c ", VH->Nodes[x].elem);
        }

        printf("\n\n");
    }
}

void populate(CLIST *C, VHeap *VH)
{
    insertAtBeginning(C, VH, 'B');
    insertAtBeginning(C, VH, 'A');
    insertAtPos(C, VH, 4, 'Z');
    insertAtEnd(C, VH, 'A');
    insertAtEnd(C, VH, 'D');
    insertAtEnd(C, VH, 'E');
}

int main()
{
    int test;
    VirtualHeap testHeap;
    
    VHeap VH = &testHeap;
    CLIST C = &test;

    initVirtualHeap(&VH);
    initCList(&C);

    populate(&C, &VH);
    displayList(C, VH);
    deleteAllOccur(&C, &VH, 'A');
    displayList(C, VH);
    return 0;
}