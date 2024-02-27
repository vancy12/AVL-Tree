// initAVL()
// insertNode()
// removeNode()
// traverse()
// destroyTree()

// balanceFactor()
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define max(a, b) (a > b? a : b)

typedef struct node{
    struct node* parent;
    struct node* left;
    struct node* right;
    char* name;
    int MIS;
    int balance;
}node;