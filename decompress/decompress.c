#include "decompress.h"

Node* create(char value, Node* left, Node* right){
	Node* new_node = (Node*) malloc(sizeof(Node));
	new_node->m_data = value;
	new_node->m_left = left;
	new_node->m_right = right;
	return new_node;
}

Node* rebuild_tree(char* s, int* pos){
	if(s[*pos] == '*'){
		*pos = *pos+1;
		Node* left = rebuild_tree(s, pos);
		*pos = *pos+1;
		return create('*', left, rebuild_tree(s, pos));
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

	//para tirar o lixo, o lixo vai ficar 0
	first_byte = first_byte << 3;
	//botando os bytes da arvore para o lugar de antes
	first_byte = first_byte >> 3;

	/*
	depois do shift 8 integer promotion:
	0000 1000 0000 0000
	0000 0000 1100 1100
	depois do ou:
	0000 1000 1100 1100
	*/
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

	int i, j, pos;

	fseek(source_file, 0, SEEK_END);

	//pega a quantidade de bytes do arquivo
	int total_bytes = ftell(source_file);
	DEBUG printf("%d\n", total_bytes);

	int size_tree = get_tree_size(source_file);
	int size_trash = get_trash_size(source_file);

	//vai armazenar a arvore
	char s[size_tree+1];

	//comeca no 2 pois eu ja li os dois primeiros bytes
	//agora eu quero ler a arvore
	for(i = 2, pos = 0; i < size_tree+2; i++, pos++){
		fseek(source_file, i, SEEK_SET);
		s[pos] = getc(source_file);
	}
	s[pos] = '\0'; //pra finalizar a string
	pos = 0;

	Node* root_huff = rebuild_tree(&s, &pos);

	DEBUG printf("\n");
	DEBUG print_huff_tree(root_huff);
	DEBUG printf("\n");

	DEBUG printf("Quantidade de bytes escritos: %ld\n", total_bytes);
	DEBUG printf("Tamanho da arvore: %d\n", size_tree);
	DEBUG printf("Trash size: %d\n", size_trash);

	//o tamanho da arvore + 2; ele agora vai comecar a ler o texto codificado
	fseek(source_file, size_tree + 2, SEEK_SET);
	unsigned int bit_cur = 0; //bit atual
	Node* root_aux = root_huff;

	DEBUG printf("%d\n", (total_bytes - (size_tree + 2)));
	//comecando a ir de bit em bit buscando uma folha na arvore
	//ate (o total de bytes) - (o que eu ja li)) - (o byte de lixo)
	for(i = 0; i < (total_bytes - (size_tree + 2)) - 1; i++){
		bit_cur = getc(source_file);
		for(j = 7; j >= 0; j--){
			if(is_bit_i_set(bit_cur, j)){
				root_aux = root_aux->m_right;
			} else{
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
