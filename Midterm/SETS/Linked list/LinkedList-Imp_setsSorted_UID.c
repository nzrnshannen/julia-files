#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *link;
}nodeType, *SET;

void initSet(SET *A);
void Display(SET A);
SET UnionSet(SET A, SET B);
SET IntersectionSet(SET A, SET B);
SET DifferenceSet(SET A, SET B);
void Insert(SET *A, int data); //insert at end && insert unique
bool isMember(SET A, int data);
SET populateA();
SET populateB();    

//first node will contain the number of elements in a SET
//hence, first element is located at the second node, second element at the third node, ... nth element at the nth+1 node

void initSet(SET *A)
{
    (*A) = NULL;
}

void Display(SET A)
{
    SET trav;
    printf("\n===\nSet: ");
    for(trav=A; trav!=NULL; trav=trav->link)
    {
        printf("%d ", trav->data);
    }

    printf("\n");
}

SET UnionSet(SET A, SET B)
{
    int count = 0;
    SET travA, travB;

    SET C;
    initSet(&C);

    for(travA = A, travB = B; travA!=NULL && travB!=NULL; )
    {
        count++;
        if(travA->data < travB->data)
        {
            Insert(&C, travA->data);
            travA = travA->link;
        }
        else if(travB->data < travA->data)
        {
            Insert(&C, travB->data);
            travB = travB->link;
        }
        else
        {
            Insert(&C, travA->data);
            travA = travA->link;
            travB = travB->link;
        }
    }


    if(travA!=NULL)
    {
        for(; travA!=NULL; travA=travA->link)
        {
            count++;
            Insert(&C, travA->data);
        }
    }

    if(travB!=NULL)
    {
        for(; travB!=NULL; travB=travB->link)
        {
            count++;
            Insert(&C, travB->data);
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

SET IntersectionSet(SET A, SET B)
{
    int count = 0;
    SET travA, travB;

    SET C;
    initSet(&C);

    for(travA=A, travB=B; travA!=NULL && travB!=NULL; )
    {
        if(travA->data < travB->data)
        {
            travA = travA->link;
        }
        else if(travB->data < travA->data)
        {
            travB = travB->link;
        }
        else
        {
            count++;
            Insert(&C, travA->data);
            travA = travA->link;
            travB = travB->link;
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

SET DifferenceSet(SET A, SET B)
{
    int count = 0;
    SET travA, travB;

    SET C;
    initSet(&C);

    for(travA=A, travB=B; travA!=NULL && travB!=NULL; )
    {
        if(travA->data < travB->data)
        {
            count++;
            Insert(&C, travA->data);
            travA=travA->link;
        }
        else if(travB->data < travA->data)
        {
            travB = travB->link;
        }
        else
        {
            travA = travA->link;
            travB = travB->link;
        }
    }


    if(travA!=NULL)
    {
        for(; travA!=NULL; travA=travA->link)
        {
            count++;
            Insert(&C, travA->data);
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

bool isMember(SET A, int data)
{
    SET trav;
    for(trav=A; trav!=NULL && trav->data != data; trav=trav->link){}

    return (trav!=NULL && trav->data==data) ? true : false;
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
    else
    {
        printf("\n\t>> Element %d exists <<\n\n", data);
    }
}

SET populateA()
{
    SET A;
    initSet(&A);

    Insert(&A, 1);
    Insert(&A, 2);
    Insert(&A, 3);
    Insert(&A, 5);
    Insert(&A, 6);
    Insert(&A, 11);
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

    return B;
}

int main()
{
    SET A = populateA();
    SET B = populateB();

    Display(A);
    Display(B);



    SET U = UnionSet(A, B);
    printf("test 2\n");
    SET I = IntersectionSet(A, B);
    printf("test 3\n");

    SET D = DifferenceSet(A, B);

    printf("\ntest union\n");
    Display(U);

    printf("\ntest intersection\n");
    Display(I);

    printf("\ntest difference: ");
    Display(D);

    free(A);
    free(B);
}