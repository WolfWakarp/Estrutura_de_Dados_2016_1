#pragma once
#include "encodingTree.h"

typedef struct list List;
struct list{
  unsigned char bit;
  List *Next;
};

typedef struct element Element;
struct element{
  int size;
  List *first;
};

typedef struct huff_table Huff_table;
struct huff_table{
  Element* table[256];
};

Huff_table* create_huff_table();

void build_representations(Node *tree, unsigned char *bit_string, int index, unsigned int bit, Huff_table *ht);
