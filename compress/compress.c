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

void print_trash_header(unsigned int size, FILE* file){
	fseek(file, 0, SEEK_SET);

	unsigned char first_byte = getc(file);
	
	unsigned char w = 0;

	w =  (first_byte | (size << 5));

	fseek(file, 0, SEEK_SET);
	fprintf(file, "%c", w);
}

int print_header(FILE* file, Node* huff){
	if(file == NULL){
		printf("Erro ao abrir arquivo.\n");
		return -1;
	}
	unsigned int size_tree = count_escapes(huff, 0) + size_huff_tree(huff);

	//Note que:
	//Se considerarmos o lixo com tamanho 0 e a arvore totalmente preenchida em binario, teremos
	//0001 1111 1111 1111
	//que corresponde a 8191 em decimal, assim precisamos garantir que o tamanho da arvore nao ultrapassara este valor.
	if(size_tree > 8191){
		printf("Erro: numero de nos maior que o suportado pelo huffman\n");
		return -1;
	}

	//posteriormente será colocado o trash_size
	unsigned char trash_size = 0;

	//dividindo o size_tree em dois bytes
	//como sei que o máximo será 13bits (8191 em decimal)
	//posso utitlizar operações shift para pegar os 8 bit de cada lado
	unsigned char first_byte = (size_tree >> 8);
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

int write_file_codification(Huff_table *ht, FILE *file, int size_tree, FILE *source_file){
	int i;
	//file_string é a variável global que armazena o arquivo lido
	int bit_index = 7;
	unsigned char bit = 0;
	unsigned int aux;
	List *temp = NULL;
	while((aux = getc(source_file)) != EOF){
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
	if(bit_index <= 7){
		fprintf(file, "%c", bit);
	}
	bit_index++;
	return bit_index;
}

void compress(char *dest_file_name, Huff_table *huff_table, Node* huffman_tree, char* source_file_name){
	FILE* dest_file = fopen(dest_file_name, "wb+");
	FILE* source_file = fopen(source_file_name, "rb");
	if(dest_file == NULL){
		printf("Erro ao abrir arquivo de destino para escrita\n");
		return;
	}
	printf("\n");
	print_header(dest_file, huffman_tree);
	print_huff_tree(huffman_tree);
	unsigned int size_trash = write_file_codification(huff_table, dest_file, size_huff_tree(huffman_tree), source_file);

	print_trash_header(size_trash, dest_file);
}
