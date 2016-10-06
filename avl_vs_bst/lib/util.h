#include <stdio.h>
#include <errno.h>
#include <string.h>

/* simples bubble sort para ordenar os arrays */
void bubble(int arr[], int size);

/* função para escrever o arquivo R; utiliza o template como base */
int write_r_file(int comp_bst[], int comp_avl[], int size, char* filename);


void bubble(int arr[], int size){
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size-1; j++){
			if(arr[j] > arr[j+1]){
				int aux = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = aux;
			}
		}
	}
}

int write_r_file(int comp_bst[], int comp_avl[], int size, char* filename){
	int i;
	FILE *template, *dest;

	template = fopen("gen_template_r", "r");

	dest = fopen(filename, "w+a");
	
	

	if(template == NULL){
		printf("%s\n", strerror(errno));	
		return 0;
	}
	if(dest == NULL){ 
		printf("%s\n", strerror(errno));	
		return 0;
	}

	fprintf(dest, "bst<-c(");
	for(i = 0; i < size; i++){
		fprintf(dest, "%d", comp_bst[i]);
		if(i != size-1) fprintf(dest, ", ");
	}
	fprintf(dest, ")\n");

	fprintf(dest, "avl<-c(");
	for(i = 0; i < size; i++){
		fprintf(dest, "%d", comp_avl[i]);
		if(i != size-1) fprintf(dest, ", ");
	}
	fprintf(dest, ")\n");

	char byte;

	while((byte = fgetc(template)) != EOF){
		fwrite(&byte, sizeof(char), 1, dest);
	}
	
	fclose(template);
	fclose(dest);
	printf("%s\n", strerror(errno));
	return 1;
}
	
