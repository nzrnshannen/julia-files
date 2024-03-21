#include<stdio.h>
#include<stdbool.h>
#define MAX 20

typedef struct{
    int data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int avail;
}VirtualHeap;

typedef int SET;

void initSet(SET *A);
void initVHeap(VirtualHeap *VH); //version 2
void insert(SET *A, VirtualHeap *VH, int data); //insert at end && insert unique
void display(SET A, VirtualHeap VH);

void Union(SET A, VirtualHeap VH_A, SET B, VirtualHeap VH_B);
void Intersection(SET A, VirtualHeap VH_A, SET B, VirtualHeap VH_B);
void Difference(SET A, VirtualHeap VH_A, SET B, VirtualHeap VH_B);

bool isSubset(SET A, VirtualHeap VH_A, SET B, VirtualHeap VH_B);
bool isSuperset(SET B, VirtualHeap VH_B, SET A, VirtualHeap VH_A);
bool isMember(SET A, VirtualHeap VH, int data);

void populateA(SET *A, VirtualHeap *VH_A);
void populateB(SET *B, VirtualHeap *VH_B);

int allocSpace(VirtualHeap *VH);
// void deallocSpace(VirtualHeap *VH, int ndx); 

void initSet(SET *A)
{
    *A = -1;
}

void initVHeap(VirtualHeap *VH)
{
    int x;
    VH->avail = MAX-1;
    for(x=VH->avail; x>=0; x--)
    {
        VH->Nodes[x].link = x-1;
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

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<MAX)
    {
        VH->Nodes[ndx].link = VH->avail;
        VH->avail = ndx;
    }
}

void insert(SET *A, VirtualHeap *VH, int data)
{
    if(isMember(*A, *VH, data)==0)
    {
        int ndx = allocSpace(VH);
        if(ndx!=-1)
        {
            VH->Nodes[ndx].data = data;
            VH->Nodes[ndx].link = -1;

            if(*A==-1)
            {
                *A = ndx;
            }
            else
            {
                SET *trav;
                for(trav=A; *trav!=-1; trav=&(VH->Nodes[*trav].link)){}

                *trav = ndx;
            }
        }
    }
}

void display(SET A, VirtualHeap VH)
{
    if(A!=-1)
    {
        SET trav;
        printf(" {"); 
        for(trav=A; trav!=-1; trav=VH.Nodes[trav].link)
        {
            printf(" %d ", VH.Nodes[trav].data);
        }
        printf("}\n");
    }
    else
    {
        printf("\n\t>> Empty set <<\n\n");
    }
}

bool isSubset(SET A, VirtualHeap VH_A, SET B, VirtualHeap VH_B)
{
    bool isSub;
    isSub = (VH_A.Nodes[A].data <= VH_B.Nodes[B].data) ? true : false;

    SET trav_A, trav_B;

    for(trav_A=A; isSub != false && trav_A!=-1; trav_A = VH_A.Nodes[trav_A].link)
    {
        for(trav_B=B; trav_B!=-1 && VH_A.Nodes[trav_A].data != VH_B.Nodes[trav_B].data; trav_B=VH_B.Nodes[trav_B].link){}

        isSub = (trav_B !=- 1) ? true : false;
    }

    return isSub;
}

bool isSuperset(SET B, VirtualHeap VH_B, SET A, VirtualHeap VH_A)
{
    bool isSup;
    isSup = (VH_B.Nodes[B].data >= VH_A.Nodes[A].data) ? true : false;

    SET trav_A, trav_B;

    for(trav_A=A; isSup!= false && trav_A!=-1; trav_A = VH_A.Nodes[trav_A].link)
    {
        for(trav_B = B; trav_B!=-1 && VH_A.Nodes[trav_A].data != VH_B.Nodes[trav_B].data; trav_B=VH_B.Nodes[trav_B].link){}
        
        isSup = (trav_B!=-1) ? true : false;
    }

    return isSup;
}

bool isMember(SET A, VirtualHeap VH, int data)
{
    SET trav;
    for(trav=A; trav!=-1 && VH.Nodes[trav].data!=data; trav=VH.Nodes[trav].link){}

    return (trav!=-1 && VH.Nodes[trav].data==data) ? true : false; 
}

void Union(SET A, VirtualHeap VH_A, SET B, VirtualHeap VH_B)
{
    SET C;
    VirtualHeap VH_C;

    initSet(&C);
    initVHeap(&VH_C);

    SET trav_a, trav_b;
    int count = 0;

    for(trav_a=A, trav_b=B; trav_a!=-1 && trav_b!=-1; )
    {
        count++;
        if(VH_A.Nodes[trav_a].data < VH_B.Nodes[trav_b].data)
        {
            insert(&C, &VH_C, VH_A.Nodes[trav_a].data);
            trav_a = VH_A.Nodes[trav_a].link;
        }
        else if(VH_B.Nodes[trav_b].data < VH_A.Nodes[trav_a].data)
        {
            insert(&C, &VH_C, VH_B.Nodes[trav_b].data);
            trav_b = VH_B.Nodes[trav_b].link;
        }
        else
        {
            insert(&C, &VH_C, VH_A.Nodes[trav_a].data);
            trav_a = VH_A.Nodes[trav_a].link;
            trav_b = VH_B.Nodes[trav_b].link;
        }
    }

    if(trav_a!=-1)
    {
        for(; trav_a!=-1; trav_a = VH_A.Nodes[trav_a].link)
        {
            count++;
            insert(&C, &VH_C, VH_A.Nodes[trav_a].data);
        }
    }

    if(trav_b!=-1)
    {
        for(; trav_b!=-1; trav_b = VH_B.Nodes[trav_b].link)
        {
            count++;
            insert(&C, &VH_C, VH_B.Nodes[trav_b].data);
        }
    }

    //insert at beginning: 1st node will be number of nodes

    int ndx = allocSpace(&VH_C);
    if(ndx!=-1)
    {
        VH_C.Nodes[ndx].data = count;
        VH_C.Nodes[ndx].link = C;
        C = ndx;
    }

    printf("\nUnion: ");
    display(C, VH_C);
}

void Intersection(SET A, VirtualHeap VH_A, SET B, VirtualHeap VH_B)
{
    SET C;
    VirtualHeap VH_C;
    initSet(&C);
    initVHeap(&VH_C);

    int count=0;

    SET trav_A, trav_B;

    for(trav_A=A, trav_B =B; trav_A!=-1 && trav_B!=-1; )
    {
        if(VH_A.Nodes[trav_A].data < VH_B.Nodes[trav_B].data)
        {
            trav_A = VH_A.Nodes[trav_A].link;
        }
        else if(VH_B.Nodes[trav_B].data < VH_A.Nodes[trav_A].data)
        {
            trav_B = VH_B.Nodes[trav_B].link;
        }
        else
        {
            count++;
            insert(&C, &VH_C, VH_A.Nodes[trav_A].data);

            trav_A = VH_A.Nodes[trav_A].link;
            trav_B = VH_B.Nodes[trav_B].link;
        }
    }


    int ndx = allocSpace(&VH_C);
    if(ndx!=-1)
    {
        VH_C.Nodes[ndx].data = count;
        VH_C.Nodes[ndx].link = C;
        C = ndx;
    }

    printf("\n===\nIntersection: ");
    display(C, VH_C);
}

void Difference(SET A, VirtualHeap VH_A, SET B, VirtualHeap VH_B)
{
    SET C;
    VirtualHeap VH_C;

    initSet(&C);
    initVHeap(&VH_C);

    SET trav_a, trav_b;
    int count = 0;

    for(trav_a = A, trav_b = B; trav_a!=-1 && trav_b!=-1; )
    {
        if(VH_A.Nodes[trav_a].data < VH_B.Nodes[trav_b].data)
        {
            count++;
            insert(&C, &VH_C, VH_A.Nodes[trav_a].data);
            trav_a = VH_A.Nodes[trav_a].link;
        }
        else if(VH_B.Nodes[trav_b].data < VH_A.Nodes[trav_a].data)
        {
            trav_b = VH_B.Nodes[trav_b].link;
        }
        else
        {
            trav_a = VH_A.Nodes[trav_a].link;
            trav_b = VH_B.Nodes[trav_b].link;
        }
    }

    if(trav_a!=-1)
    {
        for(; trav_a!=-1; trav_a = VH_A.Nodes[trav_a].link)
        {
            count++;
            insert(&C, &VH_C, VH_A.Nodes[trav_a].data);
        }
    }

    //insert at beginning

    int ndx = allocSpace(&VH_C);
    if(ndx!=-1)
    {
        VH_C.Nodes[ndx].data = count;
        VH_C.Nodes[ndx].link = C;
        C = ndx;
    }

    printf("\nDifference: ");
    display(C, VH_C);
}

void populateA(SET *A, VirtualHeap *VH_A)
{
    insert(A, VH_A, 1);
    insert(A, VH_A, 3);
    insert(A, VH_A, 4);
}

void populateB(SET *B, VirtualHeap *VH_B)
{
    insert(B, VH_B, 1);
    insert(B, VH_B, 3);
    insert(B, VH_B, 4);
    insert(B, VH_B, 8);
    insert(B, VH_B, 9);
}

int main()
{
    SET A, B;
    VirtualHeap VHA, VHB;

    initSet(&A);
    initSet(&B);

    initVHeap(&VHA);
    initVHeap(&VHB);

    populateA(&A, &VHA);
  
    populateB(&B, &VHB);

    display(A, VHA);
    display(B, VHB);

    Union(A, VHA, B, VHB);
    Intersection(A, VHA, B, VHB);
    Difference(A, VHA, B, VHB);

    printf("\n===\nTest if A is subset of B: %d\n", isSubset(A, VHA, B, VHB));
    printf("===\nTest if B is superset of A: %d\n", isSuperset(B, VHB, A, VHA));
    
    return 0;
}