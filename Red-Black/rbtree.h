#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#define NIL tree->nil
#define ROOT tree->root
#define DEBUG if(0)
#define black 'b'
#define red 'r'

typedef struct rb_node rbNode;
typedef struct rb_tree rbTree;

struct rb_node{
    int key;
    char color;
    rbNode* parent;
    rbNode* left;
    rbNode* right;
};

struct rb_tree{
    rbNode* root;
    rbNode* nil;
};

rbTree* createTree();
void insertRB(rbTree* tree, int key);
void insertTree(rbTree* tree, rbNode* z);
void rotateLeft(rbTree* tree, rbNode* x);
void rotateRight(rbTree* tree, rbNode* y);
bool searchRB(rbTree* tree, int key);
void printPreOrder(rbTree* tree, rbNode* x);
void printInOrder(rbTree* tree, rbNode* x);
void printPosOrder(rbTree* tree, rbNode* x);
