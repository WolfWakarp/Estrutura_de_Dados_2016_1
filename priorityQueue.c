#include "priorityQueue.h"



Node* createPriorityQueue(){
    return NULL;
}

int isEmpty(Node *node){
	return ((node == NULL) ? 1 : 0);
}

Node* insert(Node *node, unsigned char data, int frequency){
	if((node == NULL) || (frequency <= node->m_frequency)){
		Node *newNode = (Node*) malloc(sizeof(Node));
		newNode->m_data = data;
		newNode->m_frequency = frequency;
		newNode->m_left = NULL;
		newNode->m_right = NULL;
		newNode->Next = node;
		DEBUG printf("\nNo if Inseriu: %c | Com Rep: %d\n", data, frequency);

		return newNode;
	}
	else{
		Node *temp = node;
		Node *newNode = (Node*) malloc(sizeof(Node));

		while(temp->Next != NULL && frequency > temp->Next->m_frequency){
		        temp = temp->Next;
		}

		newNode->Next = temp->Next;
		newNode->m_data = data;
		newNode->m_frequency = frequency;
		newNode->m_left = NULL;
		newNode->m_right = NULL;
		temp->Next = newNode;

		DEBUG printf("\nNo else Inseriu: %c | Com Rep: %d\n", data, frequency);

		return node;
	}
}

Node *insertNode(Node *node, Node *inserted){
	if(node == inserted){
		inserted->Next = NULL;
		return inserted;
	}
	else if((node == NULL) || (inserted->m_frequency <= node->m_frequency)){
			inserted->Next = node;
			return inserted;
		}
	else{
		Node *temp = node;

		while(temp->Next != NULL && inserted->m_frequency > temp->Next->m_frequency){
		        temp = temp->Next;
		}

		inserted->Next = temp->Next;
		temp->Next = inserted;

		return node;
	}
}

void printPriorityQueue(Node *node){
	Node *temp;
	if(node == NULL)
		printf("\nFila de prioridade vazia!\n");
	for(temp = node; temp != NULL; temp = temp->Next){
		printf("Char: %c  Rep: %d | ", temp->m_data, temp->m_frequency);
	}
}

