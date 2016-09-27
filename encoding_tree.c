#include "encoding_tree.h"

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
	//a frequ�ncia desse novo node vai ser a soma da freq de seus filhos
	newNode->m_frequency = newNode->m_left->m_frequency + newNode->m_right->m_frequency;

	//inserindo esse node na fila novamente
	queue = insert_node(queue, newNode);

	return queue;
}

void print_pre_order(Node *bt){
	if(!is_empty(bt)){
		printf("Char: %c | Freq: %d\n", bt->m_data, bt->m_frequency);
		//printf("%c", bt->m_data);
		print_pre_order(bt->m_left);
		print_pre_order(bt->m_right);
	}
}
/*
void get_pre_order_string(Node *bt){
	if(!is_empty(bt)){
		char cToStr[2]; //para concatenar um char numa string, preciso transoformá-lo em uma string antes
		cToStr[1] = '\0'; //strings tem o \0 no final
		cToStr[0] = bt->m_data;
		strcat(tree_string, cToStr);
		get_pre_order_string(bt->m_left);
		get_pre_order_string(bt->m_right);

	}
}*/

Node *convert_list_to_tree(Node *list){
	//at� acabar a lista ele vai dando merge
	while(list->Next != NULL){
			list = merge_nodes(list);
			DEBUG printf("\nLista na convert to tree:\n");
			DEBUG print_priority_queue(list);
		}
	return list;
}

Node* create_empty_tree() {
	return NULL;
}

int is_leaf(Node *tree){
	return (tree->m_left == NULL && tree->m_right == NULL);
}
