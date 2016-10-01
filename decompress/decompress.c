#include "decompress.h"

Node* make_tree(char* s, int* pos){
	if(s[*pos] == '*'){
		*pos = *pos+1;
		Node* left = make_tree(s, pos);
		*pos = *pos+1;
		return create('*', left, make_tree(s, pos));
	}else if(s[*pos] == '\\'){
		*pos = *pos + 1;
		return create(s[*pos], NULL, NULL);
	}

	return create(s[*pos], NULL, NULL);
}

int get_tree_size(FILE* file){
	fseek(file, 0, SEEK_SET);

	unsigned char first_byte = getc(file);
	unsigned char second_byte = getc(file);

	first_byte = first_byte << 3;
	first_byte = first_byte >> 3;

	int size = (first_byte << 8) | second_byte;

	return size;
}

int get_trash_size(FILE* file){
	fseek(file, 0, SEEK_SET);
	unsigned char first_byte = getc(file);

	return first_byte >> 5;
}

void decompress(char* source_file_name, char* dest_file_name){

	FILE* source_file = fopen(source_file_name, "rb");
	FILE* dest_file = fopen(dest_file_name, "wb+");

	if(source_file == NULL){
		printf("Erro ao abrir arquivo %s para leitura\n", source_file_name);
		return ;
	}

	if(dest_file == NULL){
		printf("Erro ao abrir arquivo %s para escrita\n", dest_file_name);
		return ;
	}

	int ch, i, j, pos;

	fseek(source_file, 0, SEEK_END);

	int total_bytes = ftell(source_file);
	DEBUG printf("%d\n", total_bytes);
	int size_tree = get_tree_size(source_file);
	int size_trash = get_trash_size(source_file);

	char s[size_tree+1];

	for(i = 2, pos = 0; i < size_tree+2; i++, pos++){
		fseek(source_file, i, SEEK_SET);
		s[pos] = getc(source_file);
	}
	s[pos] = '\0';
	pos = 0;

	Node* root_huff = make_tree(&s, &pos);

	printf("\n"); print_huff_tree(root_huff);
	printf("\n");
	printf("Quantidade de bytes escritos: %ld\n", total_bytes);
	printf("Tamanho da arvore: %d\n", size_tree);
	printf("Trash size: %d\n", size_trash);

	fseek(source_file, size_tree+2, SEEK_SET);

	unsigned int bit_cur = 0;
	Node* root_aux = root_huff;

	printf("%d\n", (total_bytes-(size_tree+2)));
	//comecando a ir de bit em bit buscando uma folha na arvore
	for(i = 0; i < (total_bytes-(size_tree+2))-1; i++){
		bit_cur = getc(source_file);
		for(j = 7; j >= 0; j--){
			if(is_bit_i_set(bit_cur, j)){
				root_aux = root_aux->m_right;
			}else{
				root_aux = root_aux->m_left;
			}
			if(is_leaf(root_aux)){
				fprintf(dest_file, "%c", root_aux->m_data);
				root_aux = root_huff;
			}
		}
	}

	//ultimo byte (trabalhado com o lixo)
	bit_cur = getc(source_file);
	for(j = 7; j >= size_trash; j--){
		if(is_bit_i_set(bit_cur, j)){
			root_aux = root_aux->m_right;
		}else{
			root_aux = root_aux->m_left;
		}
		if(is_leaf(root_aux)){
			fprintf(dest_file, "%c", root_aux->m_data);
			root_aux = root_huff;
		}
	}

	fclose(dest_file);
	fclose(source_file);
}
