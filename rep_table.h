#pragma once
#include "encodingTree.h"

typedef struct list List;
struct list{
  short bit;
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
