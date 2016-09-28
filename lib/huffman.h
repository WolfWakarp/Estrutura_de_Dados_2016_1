#pragma once
#include <stdio.h>
#include "../encoding_tree.h"
#include "../rep_table.h"

// cria um nó na arvore
Node* create(char value, Node* left, Node* right);

// reconstroi a árvore de huffman
Node* make_tree(char* s, int* pos);

// verifica se o bit 1 está setado na posicao i
int is_bit_i_set(unsigned char c, int i);

// seta bit na posicao i
int set_bit(unsigned char c, int i);

// imprime a árvore no header do huffman
void print_tree_header(FILE* file, Node* huff);

// imprime o header do huffman
int print_header(FILE* file, Node* huff);

// pega o tamanho do lixo
int trash_size(FILE* file);

// pega o tamanho da árvore
int tree_size(FILE* file);

// imprime a àrvore de huffman
void print_huff_tree(Node* huff);

// descomprime o huffman
void decompress(char* source_file_name, char* dest_file_name);

//thanks to http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
void print_binary(int number)
{
    if (number) {
        print_binary(number >> 1);
        putc((number & 1) ? '1' : '0', stdout);
    }else{
	    printf("\n");
    }
}

Node* create(char value, Node* left, Node* right){
	Node* new_node = (Node*) malloc(sizeof(Node));
	new_node->m_data = value;
	new_node->m_left = left;
	new_node->m_right = right;
	return new_node;
}

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

int is_bit_i_set(unsigned char c, int i){
	unsigned char mask = 1 << i;
	return mask & c;
}

int set_bit(unsigned char c, int i){
	unsigned char mask = 1 << i;
	return mask | c;
}

int size_huff_tree(Node* huff){
	if(huff == NULL) return 0;
	return (size_huff_tree(huff->m_right)) + (size_huff_tree(huff->m_left)) + 1;
}


void print_tree_header(FILE* file, Node* huff){
	if(huff != NULL){
		fprintf(file, "%c", huff->m_data);
		print_tree_header(file, huff->m_left);
		print_tree_header(file, huff->m_right);
	}
}

int print_header(FILE* file, Node* huff){

	if(file == NULL){
		printf("Erro ao abrir arquivo.\n");
		return -1;
	}

	unsigned int size_tree = size_huff_tree(huff);

	if(size_tree > 8191){
		printf("Erro: numero de nos maior que o suportado pelo huffman\n");
		return -1;
	}

	//posteriormente será colocado o trash_size
	unsigned char trash_size = 0;

	//dividindo o size_tree em dois bytes
	//como sei que o máximo será 13bits (8191 em decimal)
	//posso utitlizar operações shift para pegar os 8 bit de cada lado
	unsigned char first_byte = (size_tree>>8);
	unsigned char second_byte = size_tree;

	//como o número máximo da trash será composto por 3 bits, desloco eles 5 vezes
	//para obter 5 espaços sobrando: exemplo
	// 0000 0101 << 5 = 1010 0000
	//assim quando é feita a operação OR, preenche os 5 ultimos com os 5 primeiros da size tree
	trash_size = trash_size << 5;

	first_byte = (first_byte | trash_size);

	fprintf(file, "%c", first_byte);
	fprintf(file, "%c", second_byte);

	print_tree_header(file, huff);


	return 1;
}


int tree_size(FILE* file){

	fseek(file, 0, SEEK_SET);

	unsigned char first_byte = getc(file);

	unsigned char second_byte = getc(file);

	first_byte = first_byte << 3;
	first_byte = first_byte >> 3;

	int size = (first_byte << 8) | second_byte;

	return size;
}

void print_huff_tree(Node* huff){
	if(huff != NULL){
		printf("%c", huff->m_data);
		print_huff_tree(huff->m_left);
		print_huff_tree(huff->m_right);
	}
}

int write_file_codification(Huff_table *ht, FILE *file, int size_tree){
	int i;
	//file_string é a variável global que armazena o arquivo lido
	int bit_index = 7;
	unsigned char bit = 0;
	List *temp = NULL;
	for(i = 0; i < strlen(file_string); i++){
		unsigned char aux = file_string[i];
		//Começa a partir do primeiro elemento da lista na huff_table na posição do char lido na string
		temp = ht->table[aux]->first;
		while(temp != NULL){
			if(bit_index == -1){
				fprintf(file, "%c", bit);
				bit = 0;
				bit_index = 7;
			}
			if(temp->bit == '1'){
				bit = set_bit(bit, bit_index);
			}
			bit_index--;
			temp = temp->Next;
		}
	}
	if(bit_index < 7){
		fprintf(file, "%c", bit);
	}
	return bit_index;
}


int trash_size(FILE* file){

	fseek(file, 0, SEEK_SET);

	unsigned char first_byte = getc(file);

	return first_byte >> 5;
}

void print_trash_header(unsigned int size, FILE* file){
	fseek(file, 0, SEEK_SET);

	unsigned char first_byte = getc(file);

	print_binary(first_byte);
	unsigned char w = 0;

	w =  (first_byte | (size << 5));

	fseek(file, 0, SEEK_SET);
	fprintf(file, "%c", w);
}

void compress(char *dest_file_name, Huff_table *huff_table, Node* huffman_tree){
	FILE* dest_file = fopen(dest_file_name, "wb+");
	if(dest_file == NULL){
		printf("Erro ao abrir arquivo de destino para escrita\n");
		return;
	}
	printf("\n");
	print_header(dest_file, huffman_tree);
	print_huff_tree(huffman_tree);
	unsigned int size_trash = write_file_codification(huff_table, dest_file, size_huff_tree(huffman_tree));
	
	print_trash_header(size_trash, dest_file);
}

void decompress(char* source_file_name, char* dest_file_name){

	FILE* source_file = fopen(source_file_name, "r");
	FILE* dest_file = fopen(dest_file_name, "w+");

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
	int size_tree = tree_size(source_file);
	int size_trash = trash_size(source_file);

	char s[size_tree+1];

	for(i = 2, pos = 0; i < size_tree+2; i++, pos++){
		fseek(source_file, i, SEEK_SET);
		s[pos] = fgetc(source_file);
	}
	s[pos] = '\0';
	pos = 0;

	Node* root_huff = make_tree(&s, &pos);

	printf("\n"); print_huff_tree(root_huff);
	printf("\n"); 
	DEBUG printf("Quantidade de bytes escritos: %ld\n", total_bytes);
	printf("Tamanho da arvore: %d\n", size_tree);
	printf("Trash size: %d\n", size_trash);

	fseek(source_file, size_tree+2, SEEK_SET);

	unsigned int bit_cur = 0;
	Node* root_aux = root_huff;
	//comecando a ir de bit em bit buscando uma folha na arvore
	for(i = 0; i < (total_bytes-(size_tree+2))-1; i++){
		bit_cur = fgetc(source_file);
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
	bit_cur = fgetc(source_file);
	for(j = 7; j >= trash_size; j--){
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
