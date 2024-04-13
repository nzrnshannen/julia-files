#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node{
    int label;
    struct node *LC;
    struct node *RC;
}cell,  *Tree;

void PreorderDisplay(Tree T);
void PostorderDisplay(Tree T);
void InorderDisplay(Tree T);
Tree InsertMem(Tree *T, int node);
void InitTree(Tree *T);
int height(Tree T, int n);

void InitTree(Tree *T)
{
    *T = NULL;
}

int main()
{

}