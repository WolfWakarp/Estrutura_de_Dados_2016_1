#pragma once
#include "encodingTree.h"

typedef struct huff_table Huff_table;
struct huff_table{
  int size;
  List *first;
};

typedef struct list List;
struct list{
  short bit;
  List *Next;
};

void create_huff_table(Huff_table* ht);
