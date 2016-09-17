#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#typedef unsigned char uc
#define MAX 256

typedef struct minHeapNode{
    uc chct;
    int freq;
    MinHeapNode *left, *right;
}MinHeapNode;

typedef struct minHeap{
    int size;
    MinHeapNode* data[MAX];
}MinHeap;

MinHeap* CreateHeap(uc data[], int freq[]);
void Heapify(MinHeap* heap, int index);
void SwapNodes(MinHeapNode** a, MinHeapNode** b)
MinHeapNode* GetNode(MinHeap* heap);
void AddNode(MinHeap* heap, MinHeapNode* node);
MinHeapNode* HuffmanTree(uc data[], int freq);



