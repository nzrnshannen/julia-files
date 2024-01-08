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

typedef int LIST;

void initCursorList(LIST *L);
void initVirtualHeap(VirtualHeap *VH);
void insertAtBeginning(char elem, LIST *L, VirtualHeap *VH);
void insertAtEnd(char elem, LIST *L, VirtualHeap *VH);
void insertAtPos(char elem, int pos, LIST *L, VirtualHeap *VH); 
void deleteAtBeginning(VirtualHeap *VH, LIST *L);
void deleteAtEnd(VirtualHeap *VH, LIST *L);
void deleteAtPos(int pos, LIST *L, VirtualHeap *VH);
void displayList(VirtualHeap VH, LIST L);
int allocSpace(VirtualHeap *VH);
void deallocSpace(int ndx, VirtualHeap *VH);
void populate(LIST *L, VirtualHeap *VH);
int elemCount(LIST L, VirtualHeap VH);
void deleteFirstOccur(char elem, LIST *L, VirtualHeap *VH);
void deleteAllOccur(char elem, LIST *L, VirtualHeap *VH);

bool isEmpty(LIST L);

void initCursorList(LIST *L)
{
    *L = -1;
}

void initVirtualHeap(VirtualHeap *VH)
{
    VH->avail = 0;
    int x;
    for(x=0; x<SIZE-1; x++)
    {
        VH->Nodes[x].link = x+1;
    }
    VH->Nodes[x].link=-1;
}

bool isEmpty(LIST L)
{
    return (L==-1)? true : false;
}

void insertAtBeginning(char elem, LIST *L, VirtualHeap *VH)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Nodes[ndx].elem = elem;
        VH->Nodes[ndx].link = *L;
        *L = ndx;
    }
    else
    {
        printf("\n\tList already full!\n");
    }
}

void insertAtEnd(char elem, LIST *L, VirtualHeap *VH)
{
    int ndx = allocSpace(VH);
    if(ndx!=-1)
    {
        VH->Nodes[ndx].elem = elem;
        if(isEmpty(*L))
        {
            VH->Nodes[ndx].link = *L; //*L here is -1 (empty at first)
            *L = ndx;
        }
        else
        {
            int x;
            for(x=0; VH->Nodes[x].link!=-1; x=VH->Nodes[x].link){}

            VH->Nodes[ndx].link = -1;
            VH->Nodes[x].link = ndx;
        }

        
    }
    else
    {
        printf("\n\tList already full!\n\n");
    }
}

void insertAtPos(char elem, int pos, LIST *L, VirtualHeap *VH)
{
    int ndx = allocSpace(VH);
    if(!(pos>=1 && pos <= elemCount(*L, *VH) + 1))
    {
        printf("\nInvalid position!\n");
    }
    else if(ndx!=-1)
    {
        int x, ctr = 1, y;
        for(x=*L; ctr < pos; x = VH->Nodes[x].link, ctr++){}

        for(y=*L; VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}

        VH->Nodes[ndx].elem = elem;
        VH->Nodes[ndx].link = x;
        VH->Nodes[y].link = ndx;    

        if(pos==1)
        {
            *L = ndx;
        }
    }
    else
    {
        printf("\nList is full!\n");
    }
}

int elemCount(LIST L, VirtualHeap VH)
{  
    int count=0;
    int x;
    for(x=L; x!=-1; x=VH.Nodes[x].link, count++){}

    return count;
}  

int allocSpace(VirtualHeap *VH)
{
    int retval = -1;
    if(VH->avail!=-1)
    {
        retval = VH->avail;
        VH->avail = VH->Nodes[retval].link;
    }
    return retval;
}

void deallocSpace(int ndx, VirtualHeap *VH)
{
    if(ndx>=0 && ndx<SIZE)
    {
        VH->Nodes[ndx].link = VH->avail;
        VH->avail = ndx;
    }
}

void displayList(VirtualHeap VH, LIST L)
{
    if(isEmpty(L))
    {
        printf("\n\n\tEmpty list!\n\n");
    }
    else
    {
        int x;
        printf("\n=====\nList: ");
        for(x=L; x!=VH.avail && x!=-1; x=VH.Nodes[x].link)
        {
            printf("%c ", VH.Nodes[x].elem);
        }
        printf("\n");
    }
}

void deleteAtBeginning(VirtualHeap *VH, LIST *L)
{
    if(!isEmpty(*L))
    {
        int ndx = *L; //store *L in ndx 
        *L = VH->Nodes[ndx].link; //move L (head) to the next node
        deallocSpace(ndx, VH);
    } 
}

void deleteAtEnd(VirtualHeap *VH, LIST *L)
{
    if(!isEmpty(*L))
    {
        int x, y;
        for(x=*L; VH->Nodes[x].link!=-1; x=VH->Nodes[x].link){}
        for(y=*L; VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}

        VH->Nodes[y].link = VH->Nodes[x].link;
        deallocSpace(x, VH);
    }
}

void deleteAtPos(int pos, LIST *L, VirtualHeap *VH)
{
    if(pos<1 || pos > elemCount(*L, *VH))
    {
        printf("\nInvalid position!");
    }
    else
    {
        int ctr = 1, x, y;
        for(x=*L; ctr<pos; x=VH->Nodes[x].link, ctr++){}

        for(y=*L; VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}

        VH->Nodes[y].link = VH->Nodes[x].link;

        if(pos==1)
        {
            *L = VH->Nodes[*L].link;
        }

        deallocSpace(x, VH);
    }
}

void deleteFirstOccur(char elem, LIST *L, VirtualHeap *VH)
{
    if(isEmpty(*L))
    {
        printf("\n\tList is empty!\n\n");
    }
    else
    {
        int x;
        for(x=*L; x!=-1 && VH->Nodes[x].elem!=elem; x=VH->Nodes[x].link){}

        if(x!=-1 && VH->Nodes[x].elem==elem)
        {
            int y;
            for(y=*L; VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}
            VH->Nodes[y].link = VH->Nodes[x].link;

            if(x==*L)
            {
                *L = VH->Nodes[x].link;
            }
            deallocSpace(x, VH);
        }
    }
}

void deleteAllOccur(char elem, LIST *L, VirtualHeap *VH)
{
    if(isEmpty(*L))
    {
        printf("\nList is empty!\n");
    }
    else
    {
        int x;
        for(x=*L; x!=-1; )
        {
            if(VH->Nodes[x].elem==elem)
            {
                if(x==*L)
                {
                    *L = VH->Nodes[*L].link;
                }
                else
                {
                    int y;
                    for(y=*L; VH->Nodes[y].link!=x; y=VH->Nodes[y].link){}

                    VH->Nodes[y].link = VH->Nodes[x].link;
                }

                deallocSpace(x, VH);
                x = *L;
            }
            else
            {
                x = VH->Nodes[x].link;
            }
        }
    }
}

void populate(LIST *L, VirtualHeap *VH)
{
    insertAtEnd('B', L, VH);
    insertAtEnd('F', L, VH);
    insertAtBeginning('A', L, VH);
    insertAtBeginning('B', L, VH);
    insertAtEnd('C', L, VH);
}

int main()
{
    LIST test;
    VirtualHeap testVH;
    initCursorList(&test);
    initVirtualHeap(&testVH);

    populate(&test, &testVH);
    displayList(testVH, test);
    // deleteAtBeginning(&testVH, &test);
    // deleteAtBeginning(&testVH, &test);
    displayList(testVH, test);
    deleteAtEnd(&testVH, &test);
    displayList(testVH, test);
    deleteAtEnd(&testVH, &test);
    displayList(testVH, test);

    insertAtPos('Z', 4, &test, &testVH);
    displayList(testVH, test);
    deleteAllOccur('B', &test, &testVH);
    displayList(testVH, test);
    printf("Test count = %d\n", elemCount(test, testVH));
    return 0;
}