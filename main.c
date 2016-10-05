#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "lib/tree.h"
#include "lib/random.h"
#include "lib/util.h"

#define DEBUG 0
#define DEFAULT_FILENAME "avl_vs_bst.R"

/* função para usar no qsort */
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[]){

	if(argc < 4){
		printf("uso: %s tamanho quantidade_sorteios [s]equencial|[r]andomico [min max]\n", argv[0]);
		exit(1);
	}

	bt* bst = create_empty_tree();
	bt* avl = create_empty_tree();
	
	srand (time(NULL));

	int i;
	int min = 1, max = 99999, n_st = atoi(argv[2]);
	int size = atoi(argv[1]);
	
	if(size <= 0 || size >= INT_MAX){
		printf("erro: quantidade de numeros abaixo/acima do permitido\n");
		exit(1);
	}	
	
	if(n_st <= 0){
		printf("erro: necessario pelo menos um sorteio\n");
		exit(1);	
	}

	int arr[size];
	
	if(n_st > size){
		printf("erro: quantidade de sorteios nao pode ser maior que o tamanho\n");
		exit(1);
	}

	char option = *argv[3];

	if(option != 's' && option != 'r'){
		printf("erro: deve ser informado o tipo de geracao [s ou r]\n");
		exit(1);
	}

	if(argc > 4){
		min = atoi(argv[4]);
	} 

	if(argc > 5){
		max = atoi(argv[5]);
	}

	if(min > max){
		printf("erro: min nao pode ser maior que max\n");
		exit(1);
	}

	int sorted;

	for(i = 0; i < size; i++){
		if(option == 'r'){
			sorted = random_number(min, max);
			arr[i] = sorted;
		}else{
			sorted = i;
		}
		bst = bst_insert(bst, sorted, 0);
		avl = bst_insert(avl, sorted, 1);
	}

	if(DEBUG){ bst_print(avl); printf("\n"); }
	if(DEBUG){ bst_print(bst); printf("\n"); }

	int num, qt_numbers = size-1;
	int comp_bst[n_st];
	int comp_avl[n_st];

	for(i = 0; i < n_st; i++){
		num = 0;
		
		if(qt_numbers != 0)
			num = random_number(0, qt_numbers);

		int aux = arr[num];
		arr[num] = arr[qt_numbers];
		arr[qt_numbers] = aux;

		comp_avl[i] = bst_search(avl, arr[qt_numbers]);
		comp_bst[i] = bst_search(bst, arr[qt_numbers]);

		if(DEBUG){
			printf("Numero sorteado: %d\n", arr[qt_numbers]);
			printf("Comparacoes na AVL: %d\n", comp_avl[i]);
			printf("Comparacoes na BST: %d\n", comp_bst[i]);
		}

		qt_numbers--;
	}

	qsort (comp_avl, n_st, sizeof(int), compare);
	qsort (comp_bst, n_st, sizeof(int), compare);
	
	if(write_r_file(comp_bst, comp_avl, n_st, DEFAULT_FILENAME)){
		printf("arquivo gerado com sucesso\n");
	}else{
		printf("falha ao gerar arquivo\n");
	}

	bst_free(bst);
	bst_free(avl);

	return 0;
}
