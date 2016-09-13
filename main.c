#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "lib/tree.h"
#include "lib/random.h"

#define DEBUG 1

int main(int argc, char *argv[]){

	if(argc < 3){
		printf("uso: %s tamanho quantidade_sorteios [min max]\n", argv[0]);
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

	if(argc > 3){
		min = atoi(argv[3]);
	} 

	if(argc > 4){
		max = atoi(argv[4]);
	}

	if(min > max){
		printf("erro: min nao pode ser maior que max\n");
		exit(1);
	}

	random_arr_numbers(arr, size, min, max);

	bst = bst_insert_array(bst, arr, size);
	avl = bst_insert_array(avl, arr, size);
	printf("\n");
	bst_print(bst);
	bst_print(avl);
	printf("\nQuantidade de sorteios: %d\n", n_st);
	
	int num, qt_numbers = size-1;
	
	for(i = 0; i < n_st; i++){
		num = 0;
		printf("Sorteio: #%d\n", i+1);
		
		if(qt_numbers != 0)
			num = random_number(0, qt_numbers);

		int aux = arr[num];
		arr[num] = arr[qt_numbers];
		arr[qt_numbers] = aux;

		printf("\tNumero sorteado: %d\n", arr[qt_numbers]);
		printf("\tComparacoes na AVL: %d\n", bst_search(avl, arr[qt_numbers]));
		printf("\tComparacoes na BST: %d\n", bst_search(bst, arr[qt_numbers]));
		
		qt_numbers--;
	}


	return 0;
}
