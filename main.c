#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "lib/tree.h"
#include "lib/random.h"
#include "lib/util.h"

#define DEBUG 0

int main(int argc, char *argv[]){

	if(argc < 3){
		printf("uso: %s tamanho quantidade_sorteios [s]equencial|[r]andomico [min max]\n", argv[0]);
		exit(1);
	}

	bt* bst = create_empty_tree();
	bt* avl = create_empty_tree();
	
	srand (time(NULL));

	int i;
	int min = 0, max = INT_MAX, n_st = atoi(argv[2]);
	int size = atoi(argv[1]);
	int arr[size];

	if(n_st > size){
		printf("erro: quantidade de sorteios nao pode ser maior que o tamanho\n");
		exit(1);
	}

	char option = *argv[3];
	printf("%c\n", option);
	if(option != 's' && option != 'r'){
		printf("erro: deve ser informado o tipo de geracao [s ou r]\n");
		exit(0);
	}

	if(argc > 4){
		min = atoi(argv[3]);
	} 

	if(argc > 5){
		max = atoi(argv[4]);
	}

	if(min > max){
		printf("erro: min nao pode ser maior que max\n");
		exit(1);
	}

	if(option == 'r'){
		random_arr_numbers(arr, size, min, max);
	}else if(option == 's'){
		sequence_arr_numbers(arr, size);
	}

	bst = bst_insert_array(bst, arr, size, 0);
	avl = bst_insert_array(avl, arr, size, 1);

	if(DEBUG) bst_print(avl);
	if(DEBUG) bst_print(bst);

	int num, qt_numbers = size-1;
	int comp_bst[n_st];
	int comp_avl[n_st];

	for(i = 0; i < n_st; i++){
		num = 0;
		
		if(qt_numbers != 0)
			num = random_number(0, qt_numbers);

		swap(&arr[num], &arr[qt_numbers]);

		comp_avl[i] = bst_search(avl, arr[qt_numbers]);
		comp_bst[i] = bst_search(bst, arr[qt_numbers]);
		
		qt_numbers--;
	}
		
	bubble(comp_bst, size);
	bubble(comp_avl, size);

	if(write_r_file(comp_bst, comp_avl, size)){
		printf("arquivo gerado com sucesso\n");
	}else{
		printf("falha ao gerar arquivo\n");
	}

	bst_free(bst);
	bst_free(avl);
	
	return 0;
}
