#include "rep_table.h"

Huff_table* create_huff_table(){
	Huff_table *ht = (Huff_table*) malloc(sizeof(Huff_table));
	int i;
	for(i = 0; i < 256; i++){
		ht->table[i] = NULL;
	}
	return ht;
}

void build_representations(Node *tree, unsigned char *bit_string, int index, unsigned int bit, Huff_table *ht){
	if(index > -1){
		bit_string[index] = bit;

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
	build_representations(tree->m_left, bit_string, index + 1, 0, ht);
	build_representations(tree->m_right, bit_string, index + 1, 1, ht);
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
		for(temp = first; temp->Next != NULL; temp = temp->Next);
		temp->Next = newNode;
	}
	
	return first;
}

void print_all_reps(Huff_table *ht){
	int i;
	for(i = 0; i < 256; i++){
		if(ht->table[i] != NULL){
			printf("\n%c ->", i);
			print_linked_list(ht->table[i]->first);
		}
	}
}

void print_linked_list(List *node){
	if(node == NULL) return;
	printf("%d", node->bit);
	print_linked_list(node->Next);
}
