#include "encodingTree.h"
#include "lib/huffman.h"



int main(){

	countRep("teste.txt");
	DEBUG printFrequency(FreqCounter);

	Node* p_queue = createPriorityQueue();
	Node* huffman_tree = create_empty_tree();

	int i;
	for(i = 0; i < 256; i++){
		if(FreqCounter[i] > 0) {
			p_queue = insert(p_queue, i, FreqCounter[i]);
			DEBUG printf("Fila: ");
			DEBUG printPriorityQueue(p_queue);
		}
	}

	//ÁRVORE DE HUFFMAN
	huffman_tree = convert_list_to_tree(p_queue);

	printPriorityQueue(p_queue);

	DEBUG printf("\n");
	DEBUG printf("%d\n\n\n", huffman_tree->m_frequency);
	DEBUG printf("Pre Order:\n");
	DEBUG printPreOrder(huffman_tree);

	DEBUG printf("\nEnd of running.");

	printf("\n%d\n", size_huff_tree(huffman_tree));
	
	print_header("testandoheader.huff", huffman_tree);
	read_file_and_make_tree("testandoheader.huff");

	return 0;
}
