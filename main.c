#include "priorityQueue.h"

int main(){

	countRep("arquivo.txt");
	printFrequency(FreqCounter);

	Node* p_queue = createPriorityQueue();

	int i;
	for(i = 0; i < 256; i++){
		if(FreqCounter[i] > 0) {
			p_queue = insert(p_queue, i, FreqCounter[i]);
			printf("Fila: ");
			printPriorityQueue(p_queue);
		}
	}

	//printf("Priority Queue:\n");
	//printPriorityQueue(p_queue);

	printf("\nEnd of running.");
	return 0;
}
