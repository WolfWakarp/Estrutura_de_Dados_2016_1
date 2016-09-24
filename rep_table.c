#include "rep_table.h"

Huff_table* create_huff_table(){
	Huff_table *ht = (Huff_table*) malloc(sizeof(Huff_table));
	int i;
	for(i = 0; i < 256; i++){
		ht->table[i]->size = 0;
		ht->table[i]->first = NULL;
	}
	return ht;
}
