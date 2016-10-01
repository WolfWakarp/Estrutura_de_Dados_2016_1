#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG if(0)

typedef struct node Node;
struct node{
  unsigned char m_data;
  int m_frequency; //prioridade, o menor fica na frente
  Node *Next;
  Node *m_left;
  Node *m_right;
};

Node* create_priority_queue();

int is_empty(Node *node);

//Inser��o padr�o de uma fila de prioridade, se o elemento inserido for igual a um
//elemento na lista, o novo elemento ficar� posicionado ANTES do elemento antigo
Node* insert(Node *node, unsigned char data, int frequency);

//Inser��o padr�o de uma fila de prioridade, obecendo as mesmas regras do insert normal
//por�m esse insere um node inteiro, e n�o itens de um node, como a fun��o acima
Node *insert_node(Node *queue, Node *inserted_node);

void print_priority_queue(Node *node);

/* Cria um novo node e faz com que o primeiro da fila de prioridade seja o filho
 * � esquerda e com que o segundo seja o filho � direita
 * esse node vai ter como caractere o * e sua frequ�ncia vai ser a soma da
 * frequ�ncia dos filhos, e ent�o ele � inserido novamente na fila
 */
Node *merge_nodes(Node* queue);

void print_pre_order(Node *bt);

/* RECEBE apenas a raiz da árvore
 * vai concatenando na string global tree_string
 */
void get_pre_order_string(Node *bt);

// Transforma toda a fila de prioridade feita com lista em uma �rvore de Huffman
Node *convert_list_to_tree(Node *list);

Node* create_empty_tree();

int is_leaf(Node *tree);

// imprime a àrvore de huffman
void print_huff_tree(Node* huff);
