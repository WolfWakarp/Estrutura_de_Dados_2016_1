#pragma once
#include <stdio.h>
#include "../compress/rep_table.h"

// reconstroi a árvore de huffman a partir da árvore em pre-order lida no .huff
Node* make_tree(char* s, int* pos);

//pega o tamanho da árvore lendo o .huff
int get_tree_size(FILE* file);

// pega o tamanho do lixo lendo o .huff
int get_trash_size(FILE* file);

// descomprime o huffman
void decompress(char* source_file_name, char* dest_file_name);
