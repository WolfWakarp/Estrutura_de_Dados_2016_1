#include <stdio.h>

/* simples bubble sort para ordenar os arrays */
void bubble(int arr[], int size);

/* função para escrever o arquivo R; utiliza o template como base */
int write_r_file(int comp_bst[], int comp_avl[], int size);

void swap(int *a, int *b){
	int aux = *a;
	*a = *b;
	*b = aux;
}

void bubble(int arr[], int size){
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size-1; j++){
			if(arr[j] > arr[j+1]){
				swap(&arr[j], &arr[j+1]);
			}
		}
	}
}

int write_r_file(int comp_bst[], int comp_avl[], int size){
	int i;
	FILE *template, *dest;

	template = fopen("gen_template_r", "r");

	dest = fopen("avl_vs_bst.R", "w+a");

	if(template == NULL) return 0;
	if(dest == NULL) return 0;

	fprintf(dest, "bst<-c(");
	for(i = 0; i < size; i++){
		fprintf(dest, "%d", comp_bst[i]);
		if(i != size-1) fprintf(dest, ",");
	}
	fprintf(dest, ")\n");

	fprintf(dest, "avl<-c(");
	for(i = 0; i < size; i++){
		fprintf(dest, "%d", comp_avl[i]);
		if(i != size-1) fprintf(dest, ",");
	}
	fprintf(dest, ")\n");

	char byte;

	while((byte = fgetc(template)) != EOF){
		fwrite(&byte, sizeof(char), 1, dest);
	}

	fclose(template);
	fclose(dest);

	if (ferror(template)) return 0;
	return 1;
}
	
