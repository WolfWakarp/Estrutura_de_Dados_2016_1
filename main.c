#include <string.h>
#include "rep_table.h"
#include "lib/huffman.h"
#include "lib/util.h"

int main(int argc, char* args[]){

	/*if(argc < 3){
		printf("uso: %s [c]omprimir|[d]escomprimir nome_arquivo [arquivo_saida]\n", args[0]);
		exit(1);
	}*/

	//char *source_file_name = args[2];
	//char *dest_file_name;

	/*if(args[1][0] != 'c' && args[1][0] != 'd'){
		printf("parametro incorreto\n");
		printf("uso: %s [c]omprimir|[d]escomprimir nome_arquivo [arquivo_saida]\n", args[0]);
		exit(1);
	}*/

	/*if(argc == 4){
		dest_file_name = args[3];
	}else{
		dest_file_name = (char *) malloc(sizeof(char *) * strlen(args[2]));
		if(!remove_huff_extension(dest_file_name, source_file_name, strlen(args[2]))){
			printf("arquivo fornecido nao possui extensao .huff\n");
			exit(1);
		}
	}*/

	//if(args[1] == 'c'){

		//count_rep(source_file_name);
		//store_string(source_file_name);
		count_rep("teste.txt");
		store_string("teste.txt");

		DEBUG printf("Quantidade de elementos no arquivo: %d\n", strlen(file_string));
		DEBUG printf("Arquivo: %s\n", file_string);

		DEBUG printFrequency(FreqCounter);

		Node* p_queue = create_priority_queue();
		Node* huffman_tree = create_empty_tree();

		int i;
		for(i = 0; i < 256; i++){
			if(FreqCounter[i] > 0) {
				p_queue = insert(p_queue, i, FreqCounter[i]);
				DEBUG printf("Fila: ");
				DEBUG print_priority_queue(p_queue);
			}
		}

		//ARVORE DE HUFFMAN
		huffman_tree = convert_list_to_tree(p_queue);

		print_priority_queue(p_queue);

		DEBUG printf("\n");
		DEBUG printf("%d\n\n\n", huffman_tree->m_frequency);
		DEBUG printf("Pre Order:\n");
		DEBUG print_pre_order(huffman_tree);

		printf("\nTree size: %d\n", size_huff_tree(huffman_tree));
		Huff_table* huffman_table = create_huff_table();

		unsigned char bit_string[100];
		build_representations(huffman_tree, bit_string, -1, 0, huffman_table);
		print_all_reps(huffman_table);

		DEBUG printf("\nEnd of running.");
	return 0;
}
