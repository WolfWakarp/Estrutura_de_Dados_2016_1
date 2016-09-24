#include "encodingTree.h"

Node *mergeNodes(Node* queue){
	//criando o node e definindo seus filhos
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->m_left = queue;
	newNode->m_right = queue->Next;

	//fazendo queue apontar para o terceiro elemento, se poss�vel, pois
	// os dois primeiros j� v�o ser tomados para serem filhos do novo node
	if(newNode->m_right->Next != NULL)
		queue = newNode->m_right->Next;
	else //se n�o for poss�vel, a fila vai apontar pro novo node
		queue = newNode;

	newNode->m_left->Next = NULL;
	newNode->m_right->Next = NULL;
	newNode->m_data = '*';
	//a frequ�ncia desse novo n� vai ser a soma da frequ�ncia de seus filhos
	newNode->m_frequency = newNode->m_left->m_frequency + newNode->m_right->m_frequency;

	//inserindo esse no da fila novamente
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
	//at� acabar a lista ele vai dando merge
	while(list->Next != NULL){
			list = mergeNodes(list);
			DEBUG printf("\nLista na convert to tree:\n");
			DEBUG printPriorityQueue(list);
		}
	return list;
}

Node* create_empty_tree() {
	return NULL;
}

int isLeaf(Node *tree){
	return (tree->m_left == NULL && tree->m_right == NULL);
}
