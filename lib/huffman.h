#include <stdio.h>
#include "../encodingTree.h"


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
	if(s[*pos] != '*' && s[*pos] != '\\'){
		*pos = *pos + 1;
		return create(s[(*pos)-1], NULL, NULL);
	}else if(s[*pos] == '\\'){
		*pos = *pos + 1;
		return create(s[*pos], NULL, NULL);
	}
	*pos = *pos + 1;
	return create('*', make_tree(s, pos), make_tree(s, pos));
}

int set_bit(unsigned char c, int i){
	unsigned char mask = 1 << i;
	return mask | c;
}

int is_leaf(Node* binary_tree){
	return (binary_tree->m_left == NULL && binary_tree->m_right == NULL);
}

int is_on_tree(Node* huff, unsigned char ch){
	if(huff == NULL) return 0;
	if(huff->m_data == ch) return 1;
	return is_on_tree(huff->m_left, ch) || is_on_tree(huff->m_right, ch);
}

int size_on_huff(Node* binary_tree, unsigned char ch){
	if(binary_tree == NULL) return -1;
	if(binary_tree->m_data == ch && is_leaf(binary_tree)) return 0;
	if(binary_tree->m_left != NULL){
		if(binary_tree->m_right == NULL){
			return size_on_huff(binary_tree->m_left, ch) + 1;
		}
		if(is_on_tree(binary_tree->m_right, ch)){
			return size_on_huff(binary_tree->m_right, ch) + 1;
		}
		return size_on_huff(binary_tree->m_left, ch) + 1;
	}
	if(binary_tree->m_right != NULL){
		return size_on_huff(binary_tree->m_right, ch) + 1;
	}
}

int size_huff_tree(Node* huff){
	if(huff == NULL) return 0;
	return (size_huff_tree(huff->m_right)) + (size_huff_tree(huff->m_left)) + 1;
}

int rep_huffman(Node* binary_tree, unsigned char ch){

	unsigned char bit = 0; // 0000 0000
	int position = size_on_huff(binary_tree, ch);
	printf("quantidade %d\n", position);
	Node* current_node = binary_tree;
	//eu tentei fazer usando a posição
	//mas o binário começa da direita para a esquerda, então nao da certo, já que a arvore é vista de cima pra baixo
	//aí eu coloco um bit no final e dou um shift pra esquerda pra ele ser arrastado
	//exemplo:
	//digamos que o A seja 111
	//pecorremos a arvore para direita setamos 1 no 0, fica 0000 0001
	//e mandamos esse 1 pra esquerda: ficando 0000 0010
	//em seguida colocamos mais um 1 no zero, fica 0000 0011
	//mandamos pra esquerda ficando 0000 0110
	//e por fim chegamos no ultimo caminho, colocando mais um 
	//ficando 0000 0111
	//e nao mandamos mais pra esquerda pq se nao ia ficar errado a representação
	if(binary_tree != NULL){
		while(current_node != NULL && !is_leaf(current_node) && current_node->m_data != ch){
			if(is_on_tree(current_node->m_right, ch)){
				printf("esta %d %d\n", position, bit);
				bit = set_bit(bit, 0);
				printf("%d\n", bit);
				current_node = current_node->m_right;	
				if(current_node != NULL && !is_leaf(current_node) && current_node->m_data != ch) bit = bit << 1;
			}else{
				printf("aqui %d %d\n", position, bit);
				current_node = current_node->m_left;
				if(current_node != NULL && !is_leaf(current_node) && current_node->m_data != ch) bit = bit << 1;
			}
		}
		
	}
	printf("%d\n", bit);
	print_binary(bit);
	return bit;
}

void print_tree_header(FILE* file, Node* huff){
	if(huff != NULL){
		fprintf(file, "%c", huff->m_data);
		print_tree_header(file, huff->m_left);
		print_tree_header(file, huff->m_right);
	}
}

int print_header(char* file_name, Node* huff){

	FILE* file = fopen(file_name, "w");

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
	unsigned char trash_size = 5;	
	
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

	fclose(file);

	return 1;
}

int tree_size(FILE* file){

	fseek(file, 0, SEEK_SET);

	unsigned char first_byte = fgetc(file);
	unsigned char second_byte = fgetc(file);	

	first_byte = first_byte << 3;
	first_byte = first_byte >> 3;

	int size = (first_byte << 8) | second_byte; 

	return size;
}

void read_file_and_make_tree(char* file_name){

	FILE* file = fopen(file_name, "r");
	
	int ch, i, pos;

	fseek(file, 3, SEEK_SET);

	int tree = tree_size(file);

	char s[tree];

	for(i = 2, pos = 0; i < tree+2; i++, pos++){
		fseek(file, i, SEEK_SET);
		s[pos] = fgetc(file);
	}
	s[pos] = '\0';
	printf("%s\n", s);
	pos = 0;

	Node* huff = make_tree(s, &pos);

	printf("Quantidade de bytes escritos: %ld\n", ftell(file));
	printf("Tamanho da arvore: %d\n", tree_size(file));

	fclose(file);
}