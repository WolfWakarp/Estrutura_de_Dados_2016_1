#include "priorityQueue.h"

struct node{
  unsigned char m_data;
  int m_frequency; //prioridade
  Node *Next;
};

Node* createPriorityQueue(){
    return NULL;
}

int isEmpty(Node *node){
	return ((node == NULL) ? 1 : 0);
}

Node* insert(Node *node, unsigned char data, int frequency){
	if((node == NULL) || (frequency < node->m_frequency)){
		Node *newNode = (Node*) malloc(sizeof(Node));
		newNode->m_data = data;
		newNode->m_frequency = frequency;
		newNode->Next = node;
		printf("\nNo if Inseriu: %c | Com Rep: %d\n", data, frequency);

		return newNode;
	}
	else{
		Node *temp = node;
		Node *newNode = (Node*) malloc(sizeof(Node));

		while(temp->Next != NULL && frequency >= temp->Next->m_frequency){
		        temp = temp->Next;
		}

		newNode->Next = temp->Next;
		newNode->m_data = data;
		newNode->m_frequency = frequency;
		temp->Next = newNode;

		printf("\nNo else Inseriu: %c | Com Rep: %d\n", data, frequency);

		return node;
	}
}

void printPriorityQueue(Node *node){
	Node *temp;
	if(node == NULL)
		printf("\nFila de prioridade vazia!\n");
	for(temp = node; temp != NULL; temp = temp->Next){
		printf("Char: %c ~ Rep: %d | ", temp->m_data, temp->m_frequency);
	}
}
