#include "queue_and_tree.h"
#include "rep_table.h"

extern int freq_counter[256];

//conta a quantidade de repetição de cada caractere
//RECEBE o nome do arquivo para abrir e contar
void count_rep(char *fileName);

//RECEBE: a arvore RETORNA o tamanho da árvore
int size_huff_tree(Node* huff);

// REBECE o arquivo destino e a raiz da arvore
// percorre a arvore em pre-order e vai imprimindo no arquivo
void print_tree_header(FILE* file, Node* huff);

//RECEBE a árvore e a quantidade atual de escapes. É chamada pela primeira vez com escapes = 0
//RETORNA a quantidade de escapes adicionados
//conta a quantidade de caracteres de escape (para incrementar o tamanho da árvore)
int count_escapes(Node* huff, int escapes);

// imprime o lixo no header do huffman
void print_trash_header(unsigned int size, FILE* file);

// RECEBE o arquivo de destino .huff e a raiz da arvore de huffman
int print_header(FILE* file, Node* huff);

/* RECEBE a huff_table, o arquivo destino .huff,
 * o tamanho da árvore e o arquivo de entrada
 * RETORNA o tamanho do lixo
 */
int write_file_codification(Huff_table *ht, FILE *file, int size_tree, FILE *source_file);

// RECEBE o nome do arquivo destino, a tabela de huffman,
// a arvore de huffman e o nome do arquivo de entrada
void compress(char *dest_file_name, Huff_table *huff_table, Node* huffman_tree, char* source_file_name);
