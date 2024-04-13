#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define SIZE 15

typedef struct node{
    int elem;
    struct node *LC;
    struct node *RC;
}Cell, *BST;

void initTree(BST * Tree);
void populate(BST *Tree);
bool isMember(BST Tree, int elem);

void insertMem(BST *Tree, int elem);
void deleteMem(BST *Tree, int elem);
int deleteMin(BST *Tree);
int deleteMax(BST *Tree);

void preorder(BST Tree);
void postorder(BST Tree);
void inorder(BST Tree);

void levelOrder(BST Tree);
void display(BST Tree);

void initTree(BST *Tree)
{
    *Tree = NULL;
}

bool isMember(BST Tree, int elem)
{
    BST trav;
    for(trav=Tree; trav!=NULL && trav->elem!=elem; )
    {
        trav = (elem < trav->elem) ? trav->LC : trav->RC;
    }

    return (trav!=NULL) ? true : false;
}

void insertMem(BST *Tree, int elem)
{
    BST *trav;
    for(trav=Tree; *trav!=NULL && (*trav)->elem!=elem; )
    {
        trav = (elem < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav==NULL)
    {
        *trav = (BST)calloc(1, sizeof(Cell));
        (*trav)->elem = elem;
    }
}

int deleteMin(BST *Tree)
{
    BST *trav, temp;
    int num;

    for(trav=Tree; *trav!=NULL && (*trav)->LC!=NULL; trav=&(*trav)->LC){}

    if(*trav!=NULL) //if tree is not empty
    {
        temp = *trav;
        num = temp->elem;
        *trav = temp->RC; //it's like adopting the child of the leftmost node to be deleted :)
        free(temp);
    }

    return num;
}

int deleteMax(BST *Tree)
{
    BST *trav, temp;
    int num;

    for(trav=Tree; *trav!=NULL && (*trav)->RC!=NULL; trav=&(*trav)->RC){}

    if(*trav!=NULL) //if tree is not empty
    {
        temp = *trav;
        num = temp->elem;
        *trav = temp->LC; //it's like adopting the child of the rightmost node to be deleted :)
        free(temp);
    }

    return num;
}

void deleteMem(BST *Tree, int elem)
{
    BST *trav;

    //searching for elem if it exists in the BST
    for(trav=Tree; *trav!=NULL && (*trav)->elem!=elem; )
    {
        trav = (elem < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav!=NULL) //if the node to be deleted is found
    {
        BST temp;
        temp = *trav;

        if(temp->LC==NULL || temp->RC==NULL)
        {
            *trav = (temp->LC!=NULL) ? temp->LC : temp->RC;
            free(temp);
        }
        else
        {
            //using the successor

            //using temp (PN) only since we're gonna be modifying the data part only
            temp->elem = deleteMin(&temp->RC);
        }
    }
}

void preorder(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("%d ", Tree->elem);
        preorder(Tree->LC);
        preorder(Tree->RC);
    }
}

void postorder(BST Tree)
{
    if(Tree!=NULL)
    {
        postorder(Tree->LC);
        postorder(Tree->RC);
        printf("%d ", Tree->elem);
    }
}

void inorder(BST Tree)
{
    if(Tree!=NULL)
    {
        inorder(Tree->LC);
        printf("%d ", Tree->elem);
        inorder(Tree->RC);
    }
}

void levelOrder(BST Tree)
{
    BST tempQueue[SIZE], current;
    int front=1, rear=0;

    if(Tree!=NULL)
    {
        for(tempQueue[++rear]=Tree; front!=(rear+1)%SIZE; )
        {
            current = tempQueue[front];
            front = (front+1)%SIZE;

            if(current!=NULL)
            {
                printf("%d ", current->elem);

                rear = (rear+1)%SIZE;
                tempQueue[rear] = current->LC;
                rear= (rear+1)%SIZE;
                tempQueue[rear] = current->RC;
            }
        }
    }
}

void display(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("\n===================================\nTree: ");
        levelOrder(Tree);
        printf("\n\n");
    }
    else
    {
        printf("\n\n\tEmpty Tree!\n\n");
    }
}

void populate(BST *Tree)
{
    insertMem(Tree, 10);
    insertMem(Tree, 5);
    insertMem(Tree, 2);
    insertMem(Tree, 9);
    insertMem(Tree, 20);
}

int main()
{
    BST myTree;

    initTree(&myTree);
    populate(&myTree);

    display(myTree);

    printf("Inorder: ");
    inorder(myTree);

    printf("\nPreoder: ");
    preorder(myTree);

    printf("\nPostorder: ");
    postorder(myTree);

    return 0;
}