#include "rep_table.h"

Huff_table* create_huff_table(){
	Huff_table *ht = (Huff_table*) malloc(sizeof(Huff_table));
	int i;
	for(i = 0; i < 256; i++){
		ht->table[i] = NULL;
	}
	return ht;
}

void build_representations(Node *tree, unsigned char *bit_string, int index, unsigned char bit, Huff_table *ht){
	if(index == -1 && is_leaf(tree)){
	    Element *newElement = (Element*) malloc(sizeof(Element));
		newElement->size = index + 1;
		newElement->first = NULL;
		ht->table[tree->m_data] = newElement;
		ht->table[tree->m_data]->first = insert_in_list(ht->table[tree->m_data]->first, '0');
		return;
	}
	if(index > -1){ //Se estiver em -1 foi a primeira chamada da função, portanto tree ainda é a raiz da árvore
		bit_string[index] = bit; //vai sempre salvando o bit passado na pos correta da string

		if(is_leaf(tree)){
			Element *newElement = (Element*) malloc(sizeof(Element));
			newElement->size = index + 1;
			newElement->first = NULL;
			ht->table[tree->m_data] = newElement;

			int i;
			for(i = 0; i <= index; i++){
				ht->table[tree->m_data]->first = insert_in_list(ht->table[tree->m_data]->first, bit_string[i]);
			}
			return;
		}

	}
	//As chamadas recursivas vão para esquerda ou para direita, passando respectivamente 0 ou 1 como bits
	//e incrementando o index para avançar na string, quando for feito o backtrack o index volta para o anterior
	if(tree->m_left != NULL) build_representations(tree->m_left, bit_string, index + 1, '0', ht);
	if(tree->m_right != NULL) build_representations(tree->m_right, bit_string, index + 1, '1', ht);
	return;
}

List* insert_in_list(List *first, unsigned char bit){
	List *newNode = (List*) malloc(sizeof(List));
	newNode->bit = bit;
	newNode->Next = NULL;
	if(first == NULL){
		first = newNode;
	} else {
		List *temp;
		for(temp = first; temp->Next != NULL; temp = temp->Next); //vai buscar o final da lista
		temp->Next = newNode;
	}
	return first;
}

void print_all_reps(Huff_table *ht){
	int i;
	for(i = 0; i < 256; i++){
		if(ht->table[i] != NULL){
			printf("\n%c ->", i); //o caractere vai ser o equivalente à sua pos na tabela ASCII. Ex: A no i=65.
			print_linked_list(ht->table[i]->first);
		}
	}
}

void print_linked_list(List *node){
	if(node == NULL) return;
	printf("%c", node->bit);
	print_linked_list(node->Next);
}



int count_trash_size(char* file_codification){
	unsigned int size = strlen(file_codification); //pega o tamanho da codificação
	unsigned int rest = size%8; //retorna um inteiro com o resto da divisão por 8, que é o tamanho do lixo
	return (8-rest);
}
