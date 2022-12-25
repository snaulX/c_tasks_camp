#ifndef BIN_HEAP_H
#define BIN_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include "huffman_node.h"

void swap(int* a, int* b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void swap_nodes(huffman_node_t* a, huffman_node_t* b) {
	//printf("'%c' '%c' -> ", a->ch, b->ch);
	huffman_node_t tmp = *a;
	*a = *b;
	*b = tmp;
	//printf("'%c' '%c'\n", a->ch, b->ch);
}

typedef struct heap_t heap_t;

struct heap_t {
	size_t size;
	size_t max_size;
	huffman_node_t* arr;
};

// i - child
// (i-1)/2 - parent
// left = 2*i + 1
// right = 2*i + 2

void heap_add(heap_t* heap, huffman_node_t value) {
	if (heap->size == heap->max_size) {
		heap->arr = (huffman_node_t*)realloc(heap->arr, heap->max_size << 1);
	}
	int child_index = heap->size;
	heap->arr[child_index] = value;
	heap->size++;

	int parent_index = (child_index-1)/2;
	while (child_index > 0 && heap->arr[parent_index].count > heap->arr[child_index].count) {
		swap_nodes(&heap->arr[parent_index], &heap->arr[child_index]);
		child_index = parent_index;
		parent_index = (child_index-1)/2;
	}
}

heap_t* heap_init(huffman_node_t* arr, size_t count) {
	heap_t* heap = (heap_t*) malloc(sizeof(heap_t));
	heap->max_size = count;
	heap->size = 1;
	heap->arr = (huffman_node_t*) calloc(count, sizeof(huffman_node_t));
	heap->arr[0] = arr[0];
	for (int i = 1; i < count; ++i)
	{
		if (arr[i].ch == '\0') continue;
		heap_add(heap, arr[i]);
	}
	return heap;
}

huffman_node_t heap_extract_min(heap_t* heap) {
	huffman_node_t ret_value = heap->arr[0];
	int i = 0;
	heap->arr[0] = heap->arr[heap->size-1];
	while (2*i + 1 < heap->size) {
		if (2*i + 2 >= heap->size) {
			swap_nodes(&heap->arr[i], &heap->arr[2*i + 1]);
			break;
		} else {
			int l = 2*i+1, r = 2*i+2;
			if (heap->arr[l].count < heap->arr[r].count) {
				swap_nodes(&heap->arr[i], &heap->arr[l]);
				i = l;
			} else {
				swap_nodes(&heap->arr[i], &heap->arr[r]);
				i = r;
			}
		}
	}
	heap->size--;
	return ret_value;
}

void print_heap(heap_t* heap) {
	printf("Count: %d; ", heap->size);
	for (int i = 0; i < heap->size; ++i)
	{
		uchar ch = heap->arr[i].ch;
		/*if (ch == '\0') {
			break;
		}*/
		printf("{'%c' %d} ", ch, heap->arr[i].count);
	}
	printf("\n");
}

#endif // BIN_HEAP_H