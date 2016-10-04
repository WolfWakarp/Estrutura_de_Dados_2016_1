#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG if(0)

//FILA-ARVORE
typedef struct node Node;
struct node{
  unsigned char m_data; //o caractere
  int m_frequency; //prioridade, o menor fica na frente
  Node *Next; //Aponta para o próximo node
  Node *m_left; //filho a esquerda
  Node *m_right; //filho a direita
};

//retorna uma fila nula
Node* create_priority_queue();

//RECEBE um node e vê se ele aponta para nulo. Se sim, retorna 1. 
int is_empty(Node *node);

//Cria um node pra inserir usando o insert_node
Node* insert(Node *queue, unsigned char data, int frequency);

//Inserção padrão de uma fila de prioridade, o node com menor frequência fica na frente
Node *insert_node(Node *queue, Node *inserted_node);

/* Cria um novo node e faz com que o primeiro da fila de prioridade seja o filho
 * à esquerda e com que o segundo seja o filho à direita
 * esse node vai ter como caractere o * e sua frequência vai ser a soma da
 * frequência dos filhos, e então ele é inserido novamente na fila
 */
Node *merge_nodes(Node* queue);

void print_pre_order(Node *bt);

// Transforma toda a fila de prioridade feita com lista em uma �rvore de Huffman
Node *convert_queue_to_tree(Node *queue);

Node* create_empty_tree();

int is_leaf(Node *tree);

// imprime a arvore de huffman
void print_huff_tree(Node* huff);
