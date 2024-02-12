#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 5

typedef struct{
    char elem;
    int link;
}nodeType;

typedef struct{
    nodeType *Nodes;
    int avail;
}VirtualHeap, *VH;

typedef int CLIST;

int allocSpace(VH* V);
void deallocSpace(VH* V, int ndx);
void initVheap(VH* V); //version 2
void initCList(CLIST *C);
void insertAtBeginning(CLIST *C, VH* V, char elem);
void insertAtEnd(CLIST *C, VH* V, char elem);
void insertAtPos(CLIST *C, VH* V, int pos, char elem);
void deleteAtBeginning(CLIST *C, VH* V);
void deleteAtEnd(CLIST *C, VH* V);
void deleteAtPos(CLIST *C, VH* V, int pos);

void deleteFirstOccur(CLIST *C, VH* V, char elem);
void deleteAllOccur(CLIST *C, VH* V, char elem);

void displayList(CLIST C, VH V);
void populate(CLIST *C, VH* V);

bool isPresent(CLIST C, VH V, char elem);
int searchElem(CLIST C, VH V, char elem); //returns index of the elem (first occur only)
int countElem(CLIST C, VH V);

bool isPresent(CLIST C, VH V, char elem)
{
    int x;
    for(x=C; x!=-1 && V->Nodes[x].elem!=elem; x=V->Nodes[x].link){}

    return (x!=-1 && V->Nodes[x].elem==elem) ? true : false;
}

int searchElem(CLIST C, VH V, char elem)
{
    int x;
    for(x=C; x!=-1 && V->Nodes[x].elem!=elem; x=V->Nodes[x].link){}

    return x; 
}

void displayList(CLIST C, VH V)
{
    if(C==-1)
    {
        printf("\n\n\tList is empty!\n\n");
    }
    else
    {
        int x;
        printf("\n=====\nList: ");
        for(x=C; x!=-1; x=V->Nodes[x].link)
        {
            printf("%c ", V->Nodes[x].elem);
        }

        printf("\n\n");
    }
}

int allocSpace(VH* V)
{
    int retval = (*V)->avail;
    if(retval!=-1)
    {
        (*V)->avail = (*V)->Nodes[retval].link;
    }

    return retval;
}

void deallocSpace(VH* V, int ndx)
{
    if(ndx>=0 && ndx < MAX)
    {
        (*V)->Nodes[ndx].link = (*V)->avail;
        (*V)->avail = ndx;
    }
}

void initCList(CLIST *C)
{
    *C = -1;
}

void initVheap(VH *V) //version 2
{
    (*V)->avail = MAX - 1;

    (*V)->Nodes= (nodeType*)malloc(sizeof(nodeType) * MAX);
    if((*V)->Nodes!=NULL)
    {
        int x;
        for(x=(*V)->avail; x>=0; x--)
        {
            (*V)->Nodes[x].link = x-1;
        }
    }
}

int countElem(CLIST C, VH V)
{
    int x, count;
    for(x=C, count=1; x!=1; x=V->Nodes[x].link, count++){}

    return count;
}

void populate(CLIST *C, VH *V)
{
    insertAtBeginning(C, V, 'A');
    insertAtBeginning(C, V, 'B');
    insertAtBeginning(C, V, 'C');
    insertAtBeginning(C, V, 'D');
    insertAtEnd(C, V, 'E');
}

void insertAtBeginning(CLIST *C, VH *V, char elem)
{
    int ndx = allocSpace(V);
    if(ndx!=-1)
    {
        //expand
        // int INIT_CAP = countElem(*C, *V);
        // printf("\ntest: %d", INIT_CAP);
        // printf("\n\t>> List is full! Resizing... <<\n\n");
        // (*V)->Nodes = (nodeType*)realloc((*V)->Nodes, sizeof(nodeType) * (INIT_CAP + 1));
        // if((*V)->Nodes==NULL)
        // {
        //     printf("\nMemory allocation failure!\n\n");
        //     exit(1);
        // }
        (*V)->Nodes[ndx].elem = elem;
        (*V)->Nodes[ndx].link = *C;
        *C = ndx;
    }
}

void insertAtEnd(CLIST *C, VH *V, char elem)
{
    int ndx = allocSpace(V);
    if(ndx!=-1)
    {

        int x;
        for(x=*C; (*V)->Nodes[x].link!=-1; x=(*V)->Nodes[x].link){}

        (*V)->Nodes[ndx].elem = elem;
        (*V)->Nodes[ndx].link = -1;
        (*V)->Nodes[x].link = ndx;

        if(*C==-1)
        {
            *C = ndx;
        }
    }
}

void insertAtPos(CLIST *C, VH *V, int pos, char elem)
{
    
}

int main()
{
    VirtualHeap myVHeap;
    CLIST H;
    VH testVH = &myVHeap;
    initCList(&H);
    initVheap(&testVH);

    populate(&H, &testVH);
    displayList(H, testVH);

    return 0;
}
