#include <string.h>
#include "compress/rep_table.h"
#include "compress/compress.h"
#include "decompress/decompress.h"
#include "decompress/util.h"
#include <sys/stat.h>
#include <time.h>

int main(int argc, char* args[]){
	clock_t start, end;
	float time_taken;
	if(argc < 3){
		printf("uso: %s [c]omprimir|[d]escomprimir nome_arquivo [arquivo_saida]\n", args[0]);
		exit(1);
	}

	char *source_file_name = args[2];
	char *dest_file_name;

	//pra pegar o tamanho do arquivo
	struct stat st;
	//se for igual a 0 significa que ele não conseguiu abrir o arquivo
	if (stat(source_file_name, &st) != 0) {
		printf("Incapaz de ler. (Arquivo inexistente ou não tem permissão para ler)\n");
		return EXIT_FAILURE;
	}

	//se for < 1 eh 0, significa que o arquivo é vazio
	if(st.st_size < 1){
        printf("Arquivo vazio\n");
        exit(1);
 	}

	if(args[1][0] != 'c' && args[1][0] != 'd'){
		printf("parametro incorreto. c para comprimir e d para descomprimir\n");
		printf("uso: %s [c]omprimir|[d]escomprimir nome_arquivo [arquivo_saida]\n", args[0]);
		exit(1);
	}

	if(argc == 4 && args[1][0] == 'c'){
		dest_file_name = args[3];
		if(!has_huff_extension(dest_file_name, strlen(dest_file_name))){
			printf("arquivo de destino precisa ter extensao .huff\n");
			exit(0);
		}
	} else if(argc == 4 && args[1][0] == 'd'){
		dest_file_name = args[3];
	} else if(args[1][0] == 'd'){
		dest_file_name = (char *) malloc(sizeof(char *) * strlen(args[2]));
		if(!remove_huff_extension(dest_file_name, source_file_name, strlen(args[2]))){
			printf("arquivo fornecido nao possui extensao .huff\n");
			exit(1);
		}
	} else if(args[1][0] == 'c'){
		dest_file_name = (char *) malloc(sizeof(char *) * (strlen(args[2])+5));
		strcpy(dest_file_name, source_file_name);
		//para botar o .huff no final
		dest_file_name[strlen(source_file_name)] = '.';
		dest_file_name[strlen(source_file_name)+1] = 'h';
		dest_file_name[strlen(source_file_name)+2] = 'u';
		dest_file_name[strlen(source_file_name)+3] = 'f';
		dest_file_name[strlen(source_file_name)+4] = 'f';
		dest_file_name[strlen(source_file_name)+5] = '\0';
	}

	printf("%s\n", dest_file_name);

	if(args[1][0] == 'c'){
		start = clock();
		count_rep(source_file_name);

		//Fila de prioridade que vai gerar a árvore de huffman
		Node* p_queue = create_priority_queue();
		//Arvore de huffman
		Node* huffman_tree = create_empty_tree();
		//Tabela de huffman, que guarda a cod de cada char
		Huff_table* huffman_table = create_huff_table();

		int i;
		//Inserindo todos os elementos que aparecem pelo menos uma vez na fila de prioridade
		for(i = 0; i < 256; i++){
			if(freq_counter[i] > 0) {
				p_queue = insert(p_queue, i, freq_counter[i]);
			}
		}

		//ARVORE DE HUFFMAN
		huffman_tree = convert_list_to_tree(p_queue);

		printf("\nTree size: %d\n", size_huff_tree(huffman_tree));

		unsigned char bit_string[256];
		build_representations(huffman_tree, bit_string, -1, '0', huffman_table);
		DEBUG print_all_reps(huffman_table);

		compress(dest_file_name, huffman_table, huffman_tree, source_file_name);
		end = clock();
		time_taken = ((float) (end - start)) / CLOCKS_PER_SEC;
		printf("\n\nCompression finished :)\n\nTime for compression: %.3f s", time_taken);
	}
	else{
		start = clock();
		decompress(source_file_name, dest_file_name);
		end = clock();
		time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\n\nDecompression finished :)\n\nTime for decompression: %.3f s", time_taken);
	}

	return 0;
}
