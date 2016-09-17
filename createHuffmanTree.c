#include "createHuffmanTree.h"

MinHeap* CreateHeap(uc data[], int freq[]){
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->size = 0;
    int i;
    for(i = 0; i < MAX; i++){
        if(freq[i] != 0){
            heap->data[i] = newNode(data[i], freq[i]);
        }
    }
    int n = heap->size - 1;
    for(i = (n - 1)/2; i >= 0; i--){
        Heapify(heap, i);
    }
    return heap;
}

void Heapify(MinHeap* heap, int index){
    int sml = index;
    int left = 2*sml + 1;
    int right = left + 1;
    if(left < heap->size && heap->data[left]->freq <= heap->data[sml]->freq){
        sml = left;
    }
    if(right < heap->size && heap->data[right]->freq <= heap->data[sml]->freq){
        sml = right;
    }
    if(sml != index){
        SwapNodes(&heap->data[sml], &heap->data[index]);
        Heapify(heap, sml);
    }
}

void SwapNodes(MinHeapNode** a, MinHeapNode** b){
    MinHeapNode* aux = *a;
    *a = *b;
    *b = aux;
}

MinHeapNode* GetNode(MinHeap* heap){
    MinHeapNode* aux = heap->data[0];
    heap->data[0] = heap->data[heap->size-- - 1];
    Heapify(heap, 0);
    return aux;
}

void AddNode(MinHeap* heap, MinHeapNode* node){
    int i = ++heap->size - 1
    while(i && node->freq < heap->data[(i - 1)/2]){
        heap->data[i] = heap->data[(i - 1)/2];
        i = (i - 1)/2;
    }
    heap->data[i] = node;
}

MinHeapNode* HuffmanTree(uc data[], int freq){
    MinHeapNode *left, *right, *aux;
    MinHeap* heap = CreateHeap(data, freq);
    while(heap->size > 1){
        left = GetNode(heap);
        right = GetNode(heap);
        aux = newNode('*', left->freq + right->freq);
        AddNode(heap, aux);
    }
    aux = GetNode(heap);
    return aux;
}

void PrintHuffmanTree(MinHeapNode* node){
    if(node){
        PrintHuffmanTree(node->left);
        printf("%c", node->chct);
        PrintHuffmanTree(node->right);
    }
}
