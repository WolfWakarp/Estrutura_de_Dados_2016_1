/*#include "queue_Heap.h"

struct min_heap {
	int size;
	Node *element[260];
};

min_heap* create_heap()
{
	min_heap *new_heap = (min_heap*) malloc(sizeof(min_heap));
	new_heap->size = 0;
	int i;
	for(i=0;i<260;i++)
	{
		new_heap->element[i]=NULL;
	}
	return new_heap;
}

void enqueue(min_heap *heap, int frequency, unsigned char character)
{
	if (heap->size >= 260)
	{
		printf("Heap is full!\n");
		return;
	}
	else
	{
		heap->element[++heap->size]->m_frequency = frequency;
		heap->element[++heap->size]->m_data = character;
		heap->element[++heap->size]->m_left = NULL;
		heap->element[++heap->size]->m_right = NULL;
		int key_index = heap->size;
		int parent_index = key_index/2;
		//Node *aux = NULL;
		while (parent_index >= 1 && heap->element[key_index]->m_frequency
				< heap->element[parent_index]->m_frequency)
		{
			//aqui é a troca dos valores
			aux = heap->element[key_index];
			heap->element[key_index] = heap->element[parent_index];
			heap->[parent_index] = aux;
			SWAP(heap->element[key_index], heap->element[parent_index]);
			key_index = parent_index;
			parent_index = key_index/2;
		}
	}
}

void min_heapify(min_heap *heap, int i) {
    int smallest;
    int left_index = get_left_index(i);
    int right_index = get_right_index(i);
    if(left_index < heap->size &&
    		heap->element[left_index]->m_frequency < heap->element[i]->m_frequency){
        smallest = left_index;
    }
    else{
    	smallest = i;
    }
    if(right_index <= heap->size &&
    		heap->element[right_index]->m_frequency < heap->element[smallest]->m_frequency){
    	smallest = right_index;
    }

    if(smallest != i){
    	SWAP(heap->element[i], heap->element[smallest]);
    	min_heapify(heap, smallest);
    }
}

Node* dequeue(min_heap *heap){
	Node *temp = heap->element[1];
	heap->element[1] = heap->element[heap->size];
	free(heap->element[heap->size]);
	heap->size--;
	min_heapify(heap, 1);
	return temp;
}*/
