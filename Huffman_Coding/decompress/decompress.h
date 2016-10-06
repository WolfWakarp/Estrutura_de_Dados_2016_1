#pragma once
#include <stdio.h>
#include "../compress/rep_table.h"

//cria um node para inserir na árvore, usando na reconstrução (make_tree)
Node* create_node(char value, Node* left, Node* right);

// reconstroi a árvore de huffman a partir da árvore em pre-order lida no .huff
Node* rebuild_tree(char* str_tree, int* pos);

//pega o tamanho da árvore lendo o .huff
int get_tree_size(FILE* file);

// pega o tamanho do lixo lendo o .huff
int get_trash_size(FILE* file);

// descomprime o huffman
void decompress(char* source_file_name, char* dest_file_name);
