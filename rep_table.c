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
		DEBUG printf("Adicionou na string: %d na pos %d\n", bit_string[index], index);
		if(is_leaf(tree)){
			DEBUG printf("\nChar:  %c ", tree->m_data);
			int i;
			DEBUG printf("\nCod: ");
			DEBUG if(index == 0) printf("%d", bit_string[0]);
			if(index == 0){
				for(i = 1; i <= index; i++){
					DEBUG printf("%d", bit_string[i]);
				}
			} else {
				for(i = 0; i <= index; i++){
					DEBUG printf("%d", bit_string[i]);
				}
			}

			DEBUG printf("\n");
			return;
		}
	}

	build_representations(tree->m_left, bit_string, index + 1, 0, ht);
	build_representations(tree->m_right, bit_string, index + 1, 1, ht);
	return;
}

List* insert_in_list(List *first, int size, unsigned char bit){
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
