struct min_heap {
	int size;
	Node *data[260];
};
typedef struct min_heap min_heap;
min_heap* create_heap()
{
	min_heap *newmh = (min_heap*) malloc(sizeof(min_heap));
	newmh->size = 0;
	int i;
	for(i=0;i<260;i++)
	{
		newmh->data[i]=NULL;
	}
	return newmh;
}
void enqueue(min_heap *heap, Node *node)
{
	if (heap->size >= 260) 
	{
		printf("Heap is full!");
	}
	else
	{
		heap->data[++heap->size] = node;
		int key_index = heap->size;
		int dad_index = key_index/2;
		Node *aux = NULL;
		while (dad_index >= 1 && heap->data[key_index]->m_frequency < heap->data[dad_index]->m_frequency)
		{
			//aqui é a troca dos valores
			aux = heap->data[key_index];
			heap->data[key_index] = heap->data[dad_index];
			heap->[dad_index] = aux;
			key_index = dad_index;
			dad_index = key_index/2;
		}
	}
}
Node* create_aux_node()
{
	Node *newauxnode = (Node*) malloc(sizeof(Node));
	newauxnode->m_right = NULL;
	newauxnode->m_left = NULL;
	newauxnode->m_data = '*';
}
int get_parent_index(min_heap *heap, int i)
{
	return i/2;
}

int get_left_index(min_heap *heap, int i)
{
	return 2*i;
}

int get_right_index(min_heap *heap, int i)
{
	return 2*i + 1;
}

Node* get_node(min_heap *heap, int i)
{
	return heap->data[i];
}

void min_heapify(min_heap *heap, int i)
{
	Node *aux;
	int smallest;
	int left_index = get_left_index(heap, i);
	int right_index = get_right_index(heap, i);
	if(left_index <= heap->size && heap->data[left_index]->m_frequency <= heap->data[i]->m_frequency)
	{
		smallest = left_index;
	} 
	else
	{
		smallest = i;
	}
	if(right_index <= heap->size && heap->data[right_index]->m_frequency <= heap->data[smallest]->m_frequency)
	{
		smallest = right_index;
	}
	if(heap->data[i] != heap->data[smallest])
	{
		aux = heap->data[i];
		heap->data[i] = heap->data[smallest];
		heap->data[smallest] = aux;
		min_heapify(heap, smallest);
	}
	return;
}
Node* dequeue(min_heap *heap)
{
	Node *value = heap->data[1];
	heap->data[1] = heap->data[heap->size];
	heap->size--;
	min_heapify(heap, 1);
	return value;
}
Node* create_tree_freq(min_heap *min_heap)
{
	Node *aux, *left, *right;
	while(min_heap->size > 1) //logica pode estar errada.
	{
		left = dequeue(min_heap); ///pega com menor frequencia || dequeue(1)
		right = dequeue(min_heap); //min_heap->data[2]; // pega o quase menor frequencia dequeue(2)
		aux = create_aux_node(); // cria o no auxiliar
		aux->m_frequency = left->m_frequency + right->m_frequency; // soma das frequencias
		aux->m_left = left; // menor frequencia na esquerda
		aux->m_right = right; // quase maior frequencia na direita
		enqueue(min_heap, aux);
	}
	return min_heap->data[1];
}