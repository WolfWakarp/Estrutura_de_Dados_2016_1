#pragma once
#include "priorityQueue.h"

typedef struct min_heap min_heap;
struct min_heap {
	int size;
	Node *data[260];
};

min_heap* create_heap();

void enqueue(min_heap *heap, Node *node);

Node* create_aux_node();

int get_parent_index(min_heap *heap, int i);

int get_left_index(min_heap *heap, int i);

int get_right_index(min_heap *heap, int i);

Node* get_node(min_heap *heap, int i);

void min_heapify(min_heap *heap, int i);

Node* dequeue(min_heap *heap);

Node* create_tree_freq(min_heap *min_heap);
