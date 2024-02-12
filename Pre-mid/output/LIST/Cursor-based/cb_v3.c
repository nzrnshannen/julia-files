#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define SIZE 5

typedef struct{
    char elem;
    int link;
}nodeType;

typedef struct{
    nodeType *Nodes;
    int avail;
}VirtualHeap;

typedef int CLIST;

void deallocSpace(VirtualHeap *VH, int ndx);
int allocSpace(VirtualHeap *VH);
void initVirtualHeap(VirtualHeap *VH);
void initCList(CLIST *C);

void insertAtBeginning(CLIST *C, VirtualHeap *VH, char elem);
void insertAtEnd(CLIST *C, VirtualHeap *VH, char elem);
void insertAtPos(CLIST *C, VirtualHeap *VH, char elem, int pos);
void deleteAtBeginning(CLIST *C, VirtualHeap *VH);
void deleteAtEnd(CLIST *C, VirtualHeap *VH);
void deleteAtPos(CLIST *C, VirtualHeap *VH, int pos);
void clearVHeap(VirtualHeap *VH);
bool isPresent(CLIST *C, VirtualHeap *VH, char elem);
int searchElem(CLIST *C, VirtualHeap *VH, char elem); //returns index of elem (first occur)
void displayList(CLIST C, VirtualHeap VH);
void populate(CLIST *C, VirtualHeap *VH);
void deleteFirstOccur(CLIST *C, VirtualHeap *VH, char elem);
void deleteAllOccur(CLIST *C, VirtualHeap *VH, char elem);

void initCList(CLIST *C)
{
    *C = -1; ///empty
}

void initVirtualHeap(VirtualHeap *VH)
{
    VH->avail = 0;
    VH->Nodes = (nodeType*)malloc(sizeof(nodeType) * SIZE);
    if(VH->Nodes!=NULL)
    {
        int x;
        for(x=0; x<SIZE-1; x++)
        {
            VH->Nodes[x].link = x+1;
        }
        VH->Nodes[x].link=-1;
    }
    else
    {
        printf("\nMemory allocation failure\n");
        exit(1);
    }
}

int searchElem(CLIST *C, VirtualHeap *VH, char elem)
{
    int x;
    for(x=*C; x!=-1 && VH->Nodes[x].elem!=elem; x=VH->Nodes[x].link){}

    return (x!=-1 && VH->Nodes[x].elem == elem) ? x : -1;
}

bool isPresent(CLIST *C, VirtualHeap *VH, char elem)
{
    int x;
    for(x=*C; x!=-1 && VH->Nodes[x].elem!=elem; x=VH->Nodes[x].link){}

    return (x!=-1 && VH->Nodes[x].elem==elem) ? true : false;
}

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<SIZE)
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

void insertAtBeginning(CLIST *C, VirtualHeap *VH, char elem)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Nodes[ndx].elem = elem;
        VH->Nodes[ndx].link = *C; //*C is -1 at the start
        *C = ndx;
    }
    else
    {
        printf("\n\tList is full!\n\n");
        //you can resize
    }

}

void displayList(CLIST C, VirtualHeap VH)
{
    if(C!=-1)
    {
        printf("\n==========================\nList: ");
        int x;
        for(x=C; x!=-1; x=VH.Nodes[x].link)
        {
            printf("%c ", VH.Nodes[x].elem);
        }

        printf("\n\n");
    }
}

void insertAtEnd(CLIST *C, VirtualHeap *VH, char elem)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Nodes[ndx].elem = elem;
        VH->Nodes[ndx].link = -1;
        
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

void insertAtPos(CLIST *C, VirtualHeap *VH, char elem, int pos)
{
    if(pos==1)
    {
        insertAtBeginning(C, VH, elem);
    }
    else if(pos>=SIZE)
    {
        insertAtEnd(C, VH, elem);
    }
    else
    {
        int ndx = allocSpace(VH);
        if(ndx!=-1)
        {
            int x, ctr;
            VH->Nodes[ndx].elem = elem;
            for(x=*C, ctr=0; x!=-1 && ctr<pos-1; x=VH->Nodes[x].link, ctr++){}

            int y;
            for(y=*C; VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}

            VH->Nodes[ndx].link = VH->Nodes[y].link;
            VH->Nodes[y].link = ndx;
        }
        else
        {
            printf("\n\n\tList is full!\n\n");
        }
    }
}

void populate(CLIST *C, VirtualHeap *VH)
{
    insertAtEnd(C, VH, 'A');
    insertAtBeginning(C, VH, 'B');
    insertAtBeginning(C, VH, 'A');
    insertAtBeginning(C, VH, 'A');
    insertAtPos(C, VH, 'A', 5);
}

void deleteAtBeginning(CLIST *C, VirtualHeap *VH)
{
    int ndx = *C;
    *C = VH->Nodes[ndx].link;
    deallocSpace(VH, ndx);
}

void deleteAtEnd(CLIST *C, VirtualHeap *VH)
{
    int x;
    for(x=*C; x!=-1 && VH->Nodes[x].link!=-1; x=VH->Nodes[x].link){}

    int y;
    for(y=*C; y!=-1 && VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}

    VH->Nodes[y].link = VH->Nodes[x].link;
    deallocSpace(VH, x);
}

void deleteAtPos(CLIST *C, VirtualHeap *VH, int pos)
{
    if(pos>=1 && pos <=SIZE)
    {
        if(pos==1)
        {
            deleteAtBeginning(C, VH);
        }
        else
        {
            int x, ctr, y;
            for(x=*C, ctr=0; x!=-1 && ctr<pos-1; x=VH->Nodes[x].link, ctr++){}

            for(y=*C; VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}

            VH->Nodes[y].link = VH->Nodes[x].link;
            deallocSpace(VH, x);
        }
    }
    else
    {
        printf("\n\tInvalid position!\n");
    }
}

void clearVHeap(VirtualHeap *VH)
{
    free(VH->Nodes);
    printf("\nMemory cleared.\n");
}

void deleteFirstOccur(CLIST *C, VirtualHeap *VH, char elem)
{
    int ndx = searchElem(C, VH, elem);
    if(ndx!=-1)
    {
        if(ndx==*C)
        {
            *C = VH->Nodes[ndx].link;
            deallocSpace(VH, ndx);
        }
        else
        {
            int y;
            for(y=*C; y!=-1 && VH->Nodes[y].link!=ndx; y=VH->Nodes[y].link){}
            VH->Nodes[y].link = VH->Nodes[ndx].link;
            deallocSpace(VH, ndx);
        }


        printf("\n\n\tSuccessfully deleted character %c at position %d.\n\n", elem, ndx+1); //position is based on how the links were formed
    }
    else
    {
        printf("\n\n\tElement %c cannot be found!\n\n", elem);
    }
}

void deleteAllOccur(CLIST *C, VirtualHeap *VH, char elem)
{
    if(isPresent(C, VH, elem))
    {
        int x;
        for(x=*C; x!=-1; )
        {
            if(VH->Nodes[x].elem==elem)
            {
                if(x==*C)
                {
                    *C = VH->Nodes[x].link;
                }
                else
                {
                    int y;
                    for(y=*C; VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}

                    VH->Nodes[y].link = VH->Nodes[x].link;
                }

                deallocSpace(VH, x);
                x = *C;
            }
            else
            {
                x = VH->Nodes[x].link;
            }
        }

        printf("\n\tSuccessfully deleted all occurrences of character %c.\n\n", elem);
    }
    else
    {
        printf("\n\n\tElement %c cannot be found!\n\n", elem);
    }
}

int main()
{
    CLIST test;
    VirtualHeap testVH;
    initCList(&test);
    initVirtualHeap(&testVH);
    populate(&test, &testVH);

    displayList(test, testVH);
    deleteFirstOccur(&test, &testVH, 'A');
    displayList(test, testVH);
    clearVHeap(&testVH);
    return 0;
}