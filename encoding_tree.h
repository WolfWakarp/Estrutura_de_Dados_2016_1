#pragma once
#include "priority_queue.h"

// Cria um novo node e faz com que o primeiro da fila de prioridade seja o filho
// � esquerda e com que o segundo seja o filho � direita
// esse node vai ter como caractere o * e sua frequ�ncia vai ser a soma da
// frequ�ncia dos filhos, e ent�o ele � inserido novamente na fila
Node *merge_nodes(Node* queue);

void print_pre_order(Node *bt);

// Transforma toda a fila de prioridade feita com lista em uma �rvore de Huffman
Node *convert_list_to_tree(Node *list);

Node* create_empty_tree();

int is_leaf(Node *tree);
