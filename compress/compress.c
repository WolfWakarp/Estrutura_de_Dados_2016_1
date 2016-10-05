#include "compress.h"

int freq_counter[256] = {0};

void count_rep(char *file_name){
	FILE *file = fopen(file_name, "rb");

	unsigned int c; //auxiliar para guardar o caractere
	if(file == NULL) printf("Empty File!\n");
	else {
		while((c=getc(file)) != EOF){
			    freq_counter[c]++; //adiciona 1 para a contagem daquele caracetere
		}
	}
	fclose(file);
}

int size_huff_tree(Node* huff){
	if(huff == NULL) return 0;
	//chama recursivamente os filhos incrementando a cada recursão
	return (size_huff_tree(huff->m_right)) + (size_huff_tree(huff->m_left)) + 1;
}

void print_tree_header(FILE* file, Node* huff){
  if(huff != NULL){
    if((huff->m_data == '*' || huff->m_data == '\\') && is_leaf(huff)){
      fprintf(file, "\\%c", huff->m_data);
    } else {
      fprintf(file, "%c", huff->m_data);
    }
		print_tree_header(file, huff->m_left);
		print_tree_header(file, huff->m_right);
	}
}

int count_escapes(Node* huff, int escapes){
  if(huff != NULL){
    if((huff->m_data == '*' || huff->m_data == '\\') && is_leaf(huff)){
      ++escapes;
    }
		escapes = count_escapes(huff->m_left, escapes);
		escapes = count_escapes(huff->m_right, escapes);
	}
  return escapes;
}

void print_trash_header(unsigned int trash_size, FILE* file){
	//volta pra pos do byte 0 no arquivo
	fseek(file, 0, SEEK_SET); //SEEK_SET faz comecar do inicio do arquivo

	unsigned char first_byte = getc(file);
	unsigned char new_first_byte = 0;

	new_first_byte = (first_byte | (trash_size << 5));

	fseek(file, 0, SEEK_SET);
	fprintf(file, "%c", new_first_byte);
}

int print_header(FILE* dest_file, Node* huff){
	if(dest_file == NULL){
		printf("Erro ao abrir arquivo.\n");
		return -1;
	}
	//o tamanho da árvore será o tamanho lido + a quantidade de escapes
	unsigned int size_tree = count_escapes(huff, 0) + size_huff_tree(huff);

	//Note que:
	//Se considerarmos o lixo com tamanho 0 e a arvore totalmente preenchida em binario, teremos
	//0001 1111 1111 1111
	//que corresponde a 8191 em decimal, assim precisamos garantir que o tamanho da arvore nao ultrapassara este valor.
	if(size_tree > 8191){
		printf("Erro: numero de nos maior que o suportado pelo huffman\n");
		return -1;
	}

	//o trash_size so sera atualizado posteriormente

	//dividindo o tree_size em dois bytes
	//como sei que o máximo será 13bits (8191 em decimal)
	//posso utitlizar operações shift para pegar os 8 bit de cada lado
	unsigned char first_byte = (size_tree >> 8);
	unsigned char second_byte = size_tree;

	fprintf(dest_file, "%c", first_byte);
	fprintf(dest_file, "%c", second_byte);

	print_tree_header(dest_file, huff);

	return 1;
}

int write_file_codification(Huff_table *ht, FILE *file, int size_tree, FILE *source_file){
	int bit_index = 7;
	unsigned char byte = 0;
	unsigned int aux;
	List *temp = NULL;

	while((aux = getc(source_file)) != EOF){
		//Começa a partir do primeiro elemento da lista na huff_table na posição do char lido no arquivo
		temp = ht->table[aux]->first;
		while(temp != NULL){
			if(bit_index == -1){
				fprintf(file, "%c", byte);
				byte = 0;
				bit_index = 7;
			}
			if(temp->bit == '1'){
				byte = set_bit(byte, bit_index);
			}
			bit_index--;
			temp = temp->Next;
		}
	}

	if(bit_index <= 7){
		fprintf(file, "%c", byte);
	}
	bit_index++;
	//retorna o tamanho do lixo
	return bit_index;
}

void compress(char *dest_file_name, Huff_table *huff_table, Node* huffman_tree, char* source_file_name){
	FILE* dest_file = fopen(dest_file_name, "wb+");
	FILE* source_file = fopen(source_file_name, "rb");
	if(dest_file == NULL){
		printf("Erro ao abrir arquivo de destino para escrita.\n");
		return;
	}
	if(source_file == NULL){
		printf("Erro ao abrir arquivo de entrada para leitura.\n");
		return;
	}
	print_header(dest_file, huffman_tree);
	DEBUG print_huff_tree(huffman_tree);
	unsigned int size_trash = write_file_codification(huff_table,
													dest_file, size_huff_tree(huffman_tree), source_file);

	print_trash_header(size_trash, dest_file);
}
