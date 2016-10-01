#include "queue_and_tree.h"

Node* create_priority_queue(){
    return NULL;
}

int is_empty(Node *node){
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

		return node;
	}
}

Node *insert_node(Node *node, Node *inserted){
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

void print_priority_queue(Node *node){
	Node *temp;
	if(node == NULL)
		printf("\nFila de prioridade vazia!\n");
	for(temp = node; temp != NULL; temp = temp->Next){
		printf("Char: %c  Rep: %d | ", temp->m_data, temp->m_frequency);
	}
}

Node *merge_nodes(Node* queue){
	//criando o node e definindo seus filhos
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->m_left = queue;
	newNode->m_right = queue->Next;

	//fazendo queue apontar para o terceiro elemento, se possível, pois
	// os dois primeiros já vão ser tomados para serem filhos do novo node
	if(newNode->m_right->Next != NULL)
		queue = newNode->m_right->Next;
	else //se não for possível, a fila vai apontar pro novo node
		queue = newNode;

	newNode->m_left->Next = NULL;
	newNode->m_right->Next = NULL;
	newNode->m_data = '*';
	//a freq desse novo node vai ser a soma da freq de seus filhos
	newNode->m_frequency = newNode->m_left->m_frequency + newNode->m_right->m_frequency;

	//inserindo esse node na fila novamente
	queue = insert_node(queue, newNode);

	return queue;
}

Node *convert_list_to_tree(Node *list){
	//caso a lista só tenha um elemento
	if(list->Next == NULL){
		Node *newNode = (Node*) malloc(sizeof(Node));
		newNode->m_left = list;
		newNode->m_right = NULL;
		//não precisa definir os netos como null pois eles
		//já são nulos pela inserção na priority queue
		newNode->m_data = '*';
		//a freq desse node vai ser apenas o node da lista
		newNode->m_frequency = list->m_frequency;
		list = newNode;
	}
	else{ //caso a fila tenha dois ao mais elementos
		//até acabar a lista ele vai dando merge
		while(list->Next != NULL){
				list = merge_nodes(list);
				DEBUG printf("\nLista na convert to tree:\n");
				DEBUG print_priority_queue(list);
			}
	}
	return list;
}

Node* create_empty_tree() {
	return NULL;
}

int is_leaf(Node *tree){
	return (tree->m_left == NULL && tree->m_right == NULL);
}
