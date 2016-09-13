#pragma once
#include "reader.h"

typedef struct node Node;

Node* createPriorityQueue();

int isEmpty(Node *node);

Node* insert(Node *node, unsigned char data, int frequency);

void printPriorityQueue(Node *node);
