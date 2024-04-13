//simple binary tree implementation

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}nodeType, *Tree;

Tree InitializeTree();
void PreOrderDisplay(Tree T);
void PostOrderDisplay(Tree T);
void InOrderDisplay(Tree T);
void Display(Tree T);
void Clear(Tree *T);

Tree Insert();

Tree InitializeTree()
{
    Tree T;
    T = NULL;

    return T;
}

Tree Insert()
{
    int x;
    Tree newNode;
    newNode = (Tree)malloc(sizeof(nodeType));
    if(newNode!=NULL)
    {
        printf("\n==========\nEnter data [-1 to EXIT]: ");
        scanf("%d", &x);

        if(x==-1)
        {
            return NULL;
        }

        newNode->data = x;

        printf("\n\n> Enter LEFT child of %d: ", x);
        newNode->left = Insert();

        printf("\n\n> Enter RIGHT child of %d: ", x);
        newNode->right = Insert();
    }

    return newNode;
}

void PreOrderDisplay(Tree T)
{
    if(T!=NULL)
    {
        printf("%d ", T->data);

        PreOrderDisplay(T->left);
        PreOrderDisplay(T->right);
    }
}

void PostOrderDisplay(Tree T)
{
    if(T!=NULL)
    {
        PostOrderDisplay(T->left);
        PostOrderDisplay(T->right);

        printf("%d ", T->data);
    }
}

void InOrderDisplay(Tree T)
{
    if(T!=NULL)
    {
        InOrderDisplay(T->left);

        printf("%d ", T->data);

        InOrderDisplay(T->right);
    }
}

void Display(Tree T)
{
    printf("\n=============================\nPre order: ");
    PreOrderDisplay(T);
    printf("\nPost order: ");
    PostOrderDisplay(T);
    printf("\nIn order: ");
    InOrderDisplay(T);
}

void Clear(Tree *T)
{
    if(*T!=NULL)
    {
        Tree temp;
        temp = *T;
        Clear(&(*T)->left);
        Clear(&(*T)->right);
        free(temp);
        *T = NULL;
    }
}

int main()
{
    Tree myTree = InitializeTree();

    myTree = Insert();

    Display(myTree);
    Clear(&myTree);

    if(myTree==NULL)
    {
        printf("\nTree set to empty."); //test
    }

    return 0;
}