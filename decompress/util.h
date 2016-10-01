#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int remove_huff_extension(char *dest_file_name, char *source_file_name, int size);
int has_huff_extension();

int has_huff_extension(char *source_file_name, int size){
	char aux[5];
	int i, p;
	for(i = size-1, p = 0; i >= size-4; i--, p++){
		aux[p] = source_file_name[i];
	}
	aux[p] = '\0';

	if(strcmp(aux, "ffuh") != 0){
		return 0;
	}
	return 1;
}

int remove_huff_extension(char *dest_file_name, char *source_file_name, int size){
	int i;

	if(!has_huff_extension(source_file_name, size)) return 0;

	for(i = 0; i < size-5; i++){
		dest_file_name[i] = source_file_name[i];
	}
	dest_file_name[i] = '\0';

	return 1;
}

// verifica se o bit 1 está setado (definido) na posicao i
int is_bit_i_set(unsigned char c, int i){
	unsigned char mask = 1 << i;
	return mask & c;
}

// seta bit na posicao i
int set_bit(unsigned char c, int i){
	unsigned char mask = 1 << i;
	return mask | c;
}

//thanks to http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
void print_binary(int number){
    if (number) {
        print_binary(number >> 1);
        putc((number & 1) ? '1' : '0', stdout);
    }else{
	    printf("\n");
    }
}
