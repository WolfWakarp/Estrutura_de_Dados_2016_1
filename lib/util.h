#pragma once
#include <string.h>
#include <stdlib.h>

int remove_huff_extension(char *dest_file_name, char *source_file_name, int size);

int remove_huff_extension(char *dest_file_name, char *source_file_name, int size){
	int i, p;
	char aux[5];
	for(i = size-1, p = 0; i >= size-4; i--, p++){
		aux[p] = source_file_name[i];
	}
	aux[p] = '\0';
	printf("%s\n", aux);
	if(strcmp(aux, "ffuh") != 0){
		return 0;
	}

	for(i = 0; i < size-5; i++){
		dest_file_name[i] = source_file_name[i];
	}
	dest_file_name[i] = '\0';

	return 1;
}
