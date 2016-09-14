#pragma once
#include "priorityQueue.h"

// Cria um novo node e faz com que o primeiro da fila de prioridade seja o filho
// à esquerda e com que o segundo seja o filho à direita
// esse node vai ter como caractere o * e sua frequência vai ser a soma da
// frequência dos filhos, e então ele é inserido novamente na fila
Node *mergeNodes(Node* queue);

void printPreOrder(Node *bt);

// Transforma toda a fila de prioridade feita com lista em uma árvore de Huffman
Node *convert_list_to_tree(Node *list);

Node* create_empty_tree();
