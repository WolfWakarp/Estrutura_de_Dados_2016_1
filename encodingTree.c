#include "encodingTree.h"

Node *mergeNodes(Node* queue){
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->m_left = queue;
	newNode->m_right = queue->Next;

	if(newNode->m_right->Next != NULL)
		queue = newNode->m_right->Next;
	else
		queue = newNode;

	newNode->m_left->Next = NULL;
	newNode->m_right->Next = NULL;
	newNode->m_data = '*';
	newNode->m_frequency = newNode->m_left->m_frequency + newNode->m_right->m_frequency;

	queue = insertNode(queue, newNode);

	return queue;
}

void printPreOrder(Node *bt){
	if(!isEmpty(bt)){
		printf("Char: %c | Freq: %d\n", bt->m_data, bt->m_frequency);
		//printf("%c", bt->m_data);
		printPreOrder(bt->m_left);
		printPreOrder(bt->m_right);
	}
}

Node *convert_list_to_tree(Node *list){
	while(list->Next != NULL){
			list = mergeNodes(list);
			DEBUG printf("\nLista na convert to tree:\n");
			printPriorityQueue(list);
		}
	return list;
}

Node* create_empty_tree() {
	return NULL;
}
