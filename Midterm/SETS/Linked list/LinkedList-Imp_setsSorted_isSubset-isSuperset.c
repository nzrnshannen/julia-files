#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *link;
}nodeType, *SET;

void initSet(SET *A);
void Insert(SET *A, int data); //insert at end && insert unique
void Display(SET A);
bool isMember(SET A, int data);

SET Union(SET A, SET B);
SET Intersection(SET A, SET B);
SET Difference(SET A, SET B);

bool isSuperset(SET A, SET B);
bool isSubset(SET A, SET B);

SET populateA();
SET populateB();

void initSet(SET *A)
{
    *A = NULL;
}

void Insert(SET *A, int data)
{
    if(isMember(*A, data)==0)
    {
        SET newNode = (SET)malloc(sizeof(nodeType));
        if(newNode!=NULL)
        {
            newNode->data = data;
            newNode->link = NULL;

            if(*A==NULL)
            {
                *A = newNode;
            }
            else
            {
                SET *trav;
                for(trav=A; *trav!=NULL; trav=&(*trav)->link){}

                *trav = newNode;
            }
        }
    }
}

void Display(SET A)
{
    printf("\n===\nSET: {");

    SET trav;
    for(trav=A; trav!=NULL; trav=trav->link)
    {
        printf(" %d ", trav->data);
    }
    printf("} ");

    printf("\n\n");
}

bool isMember(SET A, int data)
{
    SET trav;
    for(trav=A; trav!=NULL && trav->data!=data; trav=trav->link){}

    return (trav!=NULL && data==trav->data) ? true : false;
}

SET Union(SET A, SET B)
{
    SET C;
    initSet(&C);

    SET trav_a, trav_b;
    int count=0;

    for(trav_a=A, trav_b =B; trav_a!=NULL && trav_b!=NULL; )
    {
        count++;
        if(trav_a->data < trav_b->data)
        {
            Insert(&C, trav_a->data);
            trav_a=trav_a->link;
        }
        else if(trav_b->data < trav_a->data)
        {
            Insert(&C, trav_b->data);
            trav_b=trav_b->link;
        }
        else
        {
            Insert(&C, trav_a->data);
            trav_a=trav_a->link;
            trav_b=trav_b->link;
        }
    }

    if(trav_a!=NULL)
    {
        for(; trav_a!=NULL; trav_a=trav_a->link)
        {
            count++;
            Insert(&C, trav_a->data);
        }
    }

    if(trav_b!=NULL)
    {
        for(; trav_b!=NULL; trav_b=trav_b->link)
        {
            count++;
            Insert(&C, trav_b->data);
        }
    }

    SET newNode = (SET)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->data = count;
        newNode->link = C;
        C = newNode;
    }

    return C;
    
}

SET Intersection(SET A, SET B)
{
    SET C;
    initSet(&C);

    SET trav_a, trav_b;
    int count = 0;

    for(trav_a=A, trav_b=B; trav_a!=NULL && trav_b!=NULL; )
    {
        if(trav_a->data < trav_b->data)
        {
            trav_a = trav_a->link;
        }
        else if(trav_b->data < trav_a->data)
        {
            trav_b = trav_b->link; 
        }
        else
        {
            count++;
            Insert(&C, trav_a->data);
            trav_a = trav_a->link;
            trav_b = trav_b->link;
        }
    }

    SET newNode = (SET)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->data = count;
        newNode->link = C;
        C = newNode;
    }

    return C;
}

SET Difference(SET A, SET B)
{
    SET C;
    initSet(&C);

    SET trav_a, trav_b;
    int count = 0;

    for(trav_a=A, trav_b=B; trav_a!=NULL && trav_b!=NULL; )
    {
        if(trav_a->data < trav_b->data)
        {
            count++;
            Insert(&C, trav_a->data);
            trav_a=trav_a->link;
        }
        else if(trav_b->data < trav_a->data)
        {
            trav_b=trav_b->link;
        }
        else
        {
            trav_a = trav_a->link;
            trav_b = trav_b->link;
        }
    }

    if(trav_a!=NULL)
    {
        for(; trav_a!=NULL; trav_a=trav_a->link)
        {
            count++;
            Insert(&C, trav_a->data);
        }
    }

    SET newNode = (SET)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        newNode->data = count;
        newNode->link = C;
        C = newNode;
    }

    return C;
}

bool isSubset(SET A, SET B)
{
    SET trav_a, trav_b;
    bool isSub;

    isSub = (A->data <= B->data) ? true : false;

    for(trav_a=A; isSub!=false && trav_a!=NULL; trav_a=trav_a->link)
    {
        for(trav_b = B; trav_b!=NULL && trav_b->data!=trav_a->data; trav_b=trav_b->link){}

        isSub = (trav_b!=NULL) ? true : false;
    }

    return isSub;
}

bool isSuperset(SET B, SET A)
{
    SET trav_a, trav_b;
    bool isSup;

    isSup = (B->data >= A->data) ? true : false;

    for(trav_a=A; isSup!=false && trav_a!=NULL; trav_a=trav_a->link)
    {
        for(trav_b = B; trav_b!=NULL && trav_a->data!=trav_b->data; trav_b=trav_b->link){}

        isSup = (trav_b!=NULL) ? true : false;
    }

    return isSup;
}

SET populateA()
{
    SET A;
    initSet(&A);

    Insert(&A, 1);
    Insert(&A, 2);
    Insert(&A, 4);
    Insert(&A, 5);
    Insert(&A, 6);
    Insert(&A, 7);
    // Insert(&A, 9);
    return A;
}

SET populateB()
{
    SET B;
    initSet(&B);

    Insert(&B, 1);
    Insert(&B, 2);
    Insert(&B, 3);
    Insert(&B, 4);
    Insert(&B, 5);
    Insert(&B, 6);
    Insert(&B, 7);
    Insert(&B, 10);
    return B;
}

int main()
{
    SET A = populateA();
    SET B = populateB();

    Display(A);
    Display(B);


    SET U, I, D;
    U = Union(A, B);
    I = Intersection(A, B);
    D = Difference(A, B);

    Display(U);
    Display(I);
    Display(D);

    printf("TEST: A subset to B = %d\n", isSubset(A, B));
    printf("TEST: B superset of A = %d\n", isSuperset(B, A));

    return 0;
}