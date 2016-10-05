#include "rbtree.h"

int main(){
    rbTree* tree = createTree();
    int i, key, option = 0;
    bool found;
    printf("Options:\n");
    printf("(1) insert element\n");
    printf("(2) search element\n");
    printf("(3) print tree pre order\n");
    printf("(4) print tree in order\n");
    printf("(5) print tree pos order\n");
    printf("(6) quit\n");
    while(option != 6){
        do option = fgetc(stdin);
        while(option != -1 && isspace(option));
        option -= '0';
        if(option == 1){
            scanf("%d", &key);
            insertRB(tree, key);
        }
        else if(option == 2){
            scanf("%d", &key);
            found = searchRB(tree, key);
        }
        else if(option == 3){
            printPreOrder(tree, ROOT);
            printf("\n");
        }
        else if(option == 4){
            printInOrder(tree, ROOT);
            printf("\n");
        }
        else if(option == 5){
            printPosOrder(tree, ROOT);
            printf("\n");
        }
    }
    return 0;

}

rbTree* createTree(){
    rbTree* tree;
    tree = (rbTree*) malloc(sizeof(rbTree));
    // Nil is the node that has key -1, is black and its parent, left child and right child are nil nodes
    NIL = (rbNode*) malloc(sizeof(rbNode));
    NIL->color = black;
    NIL->key = -1;
    NIL->parent = NIL->left = NIL->right = NIL;
    // initially, root has key -1, is black and its parent, left child and right child  are nil nodes
    ROOT = (rbNode*) malloc(sizeof(rbNode));
    ROOT->color = black;
    ROOT->key = -1;
    ROOT->parent = ROOT->left = ROOT->right = NIL;
    return tree;
}

void insertRB(rbTree* tree, int key){
    rbNode *x, *y;
    // create node to insert with color red and nil children
    x = (rbNode*) malloc(sizeof(rbNode));
    x->key = key;
    x->color = red;
    x->left = x->right = NIL;
    // insert as a binary tree
    insertTree(tree, x);
    // fix while x->parent != root
    while(x->parent->color == red){
       if (x->parent == x->parent->parent->left){
           y = x->parent->parent->right;
           // Case 1: x's uncle is red
           if(y->color == red){
               x->parent->color = black;
               y->color = black;
               x->parent->parent->color = red;
               x = x->parent->parent;
           }
           else{
               // Case 2: x's uncle is black and x is a right child
               if(x == x->parent->right){
                   x = x->parent;
                   rotateLeft(tree, x);
               }
               // Case 3: x's uncle is black and x is a left child
               x->parent->color = black;
               x->parent->parent->color = red;
               rotateRight(tree, x->parent->parent);
               }
       }
       else{
       // Same as if with left and right exchanged
           y = x->parent->parent->left;
           if(y->color == red){
               x->parent->color = black;
               y->color = black;
               x->parent->parent->color = red;
               x = x->parent->parent;
           }
           else{
               if(x == x->parent->left){
                   x = x->parent;
                   rotateRight(tree, x);
               }
               x->parent->color = black;
               x->parent->parent->color = red;
               rotateLeft(tree, x->parent->parent);
           }
       }
    }
    ROOT->color = black;
}

void insertTree(rbTree* tree, rbNode* z){
    rbNode *x;
    rbNode *y;
    y = NIL;
    x = ROOT;
    while(x != NIL){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    // if it's the first element, z is root and its parent is NIL
    if(ROOT->key == NIL->key){
        ROOT = z;
        ROOT->parent = NIL;
    }
    else{
        z->parent = y;
        if(z->key < y->key){
            // z is left child of y
            y->left = z;
        }
        else{
            // z is right child of y
            y->right = z;
        }
    }
}

void rotateLeft(rbTree* tree, rbNode* x){
    rbNode* y;
    y = x->right;
    x->right = y->left;
    if(y->left != NIL){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NIL){
        ROOT = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rotateRight(rbTree* tree, rbNode* y){
    rbNode* x;
    x = y->left;
    y->left = x->right;
    if(x->right != NIL){
        x->right->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NIL){
        ROOT = x;
    }
    else if(y == y->parent->left){
        y->parent->left = x;
    }
    else{
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

bool searchRB(rbTree* tree, int key){
    rbNode* node = ROOT;
    while(node != NIL){
        if(key < node->key){
            node = node->left;
        }
        else if(key > node->key){
            node = node->right;
        }
        else{
            printf("Element found!\n");
            if(node->parent == NIL){
                printf("Element is root\n");
            }
            else{
                printf("Parent of %d is %d\n", key, node->parent->key);
            }
            if(node->left == NIL){
                printf("Left child is nil\n");
            }
            else{
                printf("Left child is %d\n", node->left->key);
            }
            if(node->right == NIL){
                printf("Right child is nil\n");
            }
            else{
                printf("Right child is %d\n", node->right->key);
            }
            return true;
        }
    }
    printf("Element is not in RB tree!\n");
    return false;
}

void printPreOrder(rbTree* tree, rbNode* x){
    if(x != NIL){
        printf("%d-%c ", x->key, x->color);
        printPreOrder(tree, x->left);
        printPreOrder(tree, x->right);
    }
}

void printInOrder(rbTree* tree, rbNode* x){
    if(x != NIL){
        printInOrder(tree, x->left);
        printf("%d-%c ", x->key, x->color);
        printInOrder(tree, x->right);
    }
}

void printPosOrder(rbTree* tree, rbNode* x){
    if(x != NIL){
        printPosOrder(tree, x->left);
        printPosOrder(tree, x->right);
        printf("%d-%c ", x->key, x->color);
    }
}
