#pragma once
#include "queue_and_tree.h"


//Node da lista que vai guardar cada bit
typedef struct list List;
struct list{
  unsigned char bit;
  List *Next;
};

//Vai guardar a lista de bits de cada caractere
typedef struct element Element;
struct element{
  List *first;
};

//Estrutura semelhante a uma hash que vai guardar um Element em cada posição,
//Sendo essa posição o numero em int do caractere na tabela ASCII
typedef struct huff_table Huff_table;
struct huff_table{
  Element* table[256];
};

//Vai definir cada table->[i] como NULL
Huff_table* create_huff_table();

/* INICIALMENTE CHAMADA NA MAIN COM a árvore, uma string vazia, o índice em -1 (flag),
 * um bit qualquer e a tabela de huffman vazia.
 * O QUE FAZ: Vai ler a árvore em pre-order. Sempre que for para a esquerda,
 * vai salvar 0 na bit_string e sempre que for para a direita, vai salvar 1 na bit_string.
 * RECEBE: TREE, que é a árvore que ele vai ler; BIT_STRING, que é a string em que ele vai armazenar os bits;
 * INDEX, que é para saber em qual posição da string ele vai guardar 0 ou 1; BIT, que é o bit passado;
 * e HT, que é a tabela de huffman.
 * APÓS O FIM DA FUNÇÃO, a tabela de huffman passada como parâmetro estará pronta.
 */
void build_representations(Node *tree, unsigned char *bit_string,
                          int index, unsigned char bit, Huff_table *ht);

/* CHAMADA NA build_representations
 * Insere no final da lista
 * RECEBE: FIRST, que é a cabeça da lista; e BIT, que é o char a ser inserido.
 * RETORNA: a cabeça da lista
 */
List* insert_in_list(List *first, unsigned char bit);

/* RECEBE: a tabela de huffman HT
 * Vê quais posições da tabela de huffman não estão nulos e imprime
 * seus caracteres e suas respectivas listas
 */
void print_all_reps(Huff_table *ht);

//RECEBE uma lista List* e imprime recursivamente
void print_linked_list(List *node);
