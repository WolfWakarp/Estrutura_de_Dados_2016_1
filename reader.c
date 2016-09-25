#include "reader.h"

int FreqCounter[256] = {0};
unsigned char file_string[100000] = {0};

void count_rep(char *file_name){
	FILE *file = fopen(file_name, "rb");

	int c; //auxiliar para guardar o caractere
	if(file == NULL) printf("Empty File!\n");
	else{
		while((c=fgetc(file))){
			    if(c == EOF) break; //encerrar caso o arquivo esteja no fim
			    FreqCounter[c]+=1; //caso contr�rio adiciona 1 para a contagem daquele caracetere
		}
	}
	fclose(file);
}

void store_string(char *fileName){
	FILE *file = fopen(fileName, "r");

	int i = 0;
	int c;
	if(file == NULL) printf("Empty File!\n");
	else{
		while((c=fgetc(file))){
			    if(c == EOF) break; //encerrar caso o arquivo esteja no fim
					else{
						file_string[i] = c;
						i++;	
					}
		}
	}
	fclose(file);
}

void printFrequency(int array[256]){
	int i;
	for(i = 0; i < 256; i++){
		if(array[i] > 0) {
		      printf("char %c: %d times\n", i, array[i]);
		}
	}
}
