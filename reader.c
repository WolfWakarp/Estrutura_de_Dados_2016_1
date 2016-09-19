#include "reader.h"

int FreqCounter[256] = {0};

void countRep(char *fileName){
	FILE *file = fopen(fileName, "r");

	int c; //auxiliar para guardar o caractere
	if(file == NULL) printf("Empty File!\n");
	else{
		while((c=fgetc(file))){
			    if(c == EOF) break; //encerrar caso o arquivo esteja no fim
			    FreqCounter[c]+=1; //caso contrário adiciona 1 para a contagem daquele caracetere
		}
	}
	fclose(file);
}

void printFrequency(int array[256]){
	int i;
	for(i=0; i < 256; i++){
		if(array[i] > 0) {
		      printf("char %c: %d times\n", i, array[i]);
		}
	}
}
