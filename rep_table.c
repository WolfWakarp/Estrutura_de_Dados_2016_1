#include "rep_table.h"

void create_huff_table(Huff_table* ht){
	int i;
	for(i = 0; i < 256; i++){
		ht[i]->size = 0;
		ht[i]->first = NULL;
	}
}
