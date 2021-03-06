#include "queue_and_tree.h"

Node* create_empty_priority_queue(){
    return NULL;
}

int is_empty(Node *node){
	return (node == NULL);
}

//chamada na main.c
Node* insert_pq(Node *queue, unsigned char data, int frequency){
  Node *newNode = (Node*) malloc(sizeof(Node));
  newNode->m_data = data;
  newNode->m_frequency = frequency;
  newNode->m_left = NULL;
  newNode->m_right = NULL;
  newNode->Next = NULL;

  queue = insert_node(queue, newNode);
  return queue;
}

Node *insert_node(Node *queue, Node *inserted){
  //quando a função merge_nodes chama essa função chega uma hora
  //que queue e
  if(queue == inserted){
		inserted->Next = NULL;
		return inserted;
	}
  else if((queue == NULL) || (inserted->m_frequency <= queue->m_frequency)){
			inserted->Next = queue;
			return inserted;
		}
	else{
		Node *temp = queue;
		while(temp->Next != NULL && inserted->m_frequency > temp->Next->m_frequency){
		        temp = temp->Next;
		}
		inserted->Next = temp->Next;
		temp->Next = inserted;

		return queue;
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

Node *convert_queue_to_tree(Node *queue){
	//caso a fila só tenha um elemento
	if(queue->Next == NULL){
		Node *newNode = (Node*) malloc(sizeof(Node));
		newNode->m_left = queue;
		newNode->m_right = NULL;
		//não precisa definir os netos como null pois eles
		//já são nulos pela inserção na priority queue
		newNode->m_data = '*';
		//a freq desse node vai ser apenas o node da lista
		newNode->m_frequency = queue->m_frequency;
		queue = newNode;
	}
	else{ //caso a fila tenha dois ao mais elementos
		//até acabar a lista ele vai dando merge
		while(queue->Next != NULL){
				queue = merge_nodes(queue);
			}
	}
	return queue;
}

Node* create_empty_tree() {
	return NULL;
}

int is_leaf(Node *tree){
	return (tree->m_left == NULL && tree->m_right == NULL);
}

void print_huff_tree(Node* huff){
	if(huff != NULL){
		printf("%c", huff->m_data);
		print_huff_tree(huff->m_left);
		print_huff_tree(huff->m_right);
	}
}
