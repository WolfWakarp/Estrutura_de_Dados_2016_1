#pragma once
#include "reader.h"

typedef struct node Node;
struct node{
  unsigned char m_data;
  int m_frequency; //prioridade, o menor fica na frente
  Node *Next;
  Node *m_left;
  Node *m_right;
};

Node* createPriorityQueue();

int isEmpty(Node *node);

//Inser��o padr�o de uma fila de prioridade, se o elemento inserido for igual a um
//elemento na lista, o novo elemento ficar� posicionado ANTES do elemento antigo
Node* insert(Node *node, unsigned char data, int frequency);

//Inser��o padr�o de uma fila de prioridade, obecendo as mesmas regras do insert normal
//por�m esse insere um node inteiro, e n�o itens de um node, como a fun��o acima
Node *insertNode(Node *queue, Node *inserted_node);

void printPriorityQueue(Node *node);
