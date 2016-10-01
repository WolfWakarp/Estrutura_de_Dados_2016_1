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

//Cria um nó pra inserir usando o insert_node
Node* insert(Node *queue, unsigned char data, int frequency);

//Inserção padrão de uma fila de prioridade, o nó com menor frequência fica na frente
Node *insert_node(Node *queue, Node *inserted_node);

void print_priority_queue(Node *node);

/* Cria um novo node e faz com que o primeiro da fila de prioridade seja o filho
 * à esquerda e com que o segundo seja o filho à direita
 * esse node vai ter como caractere o * e sua frequência vai ser a soma da
 * frequência dos filhos, e então ele é inserido novamente na fila
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
