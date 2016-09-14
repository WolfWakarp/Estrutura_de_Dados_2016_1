#pragma once
#include "reader.h"

typedef struct node Node;
struct node{
  unsigned char m_data;
  int m_frequency; //prioridade
  Node *Next;
  Node *m_left;
  Node *m_right;
};

Node* createPriorityQueue();

int isEmpty(Node *node);

//Inserção padrão de uma fila de prioridade, se o elemento inserido for igual a um
//elemento na lista, o novo elemento ficará posicionado ANTES do elemento antigo
Node* insert(Node *node, unsigned char data, int frequency);

//Inserção padrão de uma fila de prioridade, obecendo as mesmas regras do insert normal
//porém esse insere um node inteiro, e não itens de um node, como a função acima
Node *insertNode(Node *queue, Node *inserted_node);

void printPriorityQueue(Node *node);
