#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

typedef struct heap_t heap_t;

struct heap_t {
	size_t size;
	size_t max_size;
	int* arr;
};

// i - child
// (i-1)/2 - parent
// left = 2*i + 1
// right = 2*i + 2

heap_t* heap_create(int value, size_t max_size) {
	heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
	heap->size = 1;
	heap->max_size = 1 << max_size;
	heap->arr = (int*) calloc(heap->max_size, sizeof(int));
	heap->arr[0] = value;
	return heap;
}

void heap_add(heap_t* heap, int value) {
	if (heap->size == heap->max_size) {
		heap->arr = (int*)realloc(heap->arr, heap->max_size << 1);
	}
	int child_index = heap->size;
	heap->arr[child_index] = value;
	heap->size++;

	int parent_index = (child_index-1)/2;
	while (child_index > 0 && heap->arr[parent_index] > heap->arr[child_index]) {
		swap(&heap->arr[parent_index], &heap->arr[child_index]);
		child_index = parent_index;
		parent_index = (child_index-1)/2;
	}
}

int heap_extract_min(heap_t* heap) {
	int ret_value = heap->arr[0];
	int i = 0;
	heap->arr[0] = heap->arr[heap->size-1];
	while (2*i + 1 < heap->size) {
		if (2*i + 2 >= heap->size) {
			swap(&heap->arr[i], &heap->arr[2*i + 1]);
			break;
		} else {
			int l = 2*i+1, r = 2*i+2;
			if (heap->arr[l] < heap->arr[r]) {
				swap(&heap->arr[i], &heap->arr[l]);
				i = l;
			} else {
				swap(&heap->arr[i], &heap->arr[r]);
				i = r;
			}
		}
	}
	heap->size--;
	return ret_value;
}

void print_heap(heap_t* heap) {
	for (int i = 0; i < heap->size; i++) {
		printf("%d ", heap->arr[i]);
	}
	printf("\n");
}

heap_t* heap_init_from_arr(int* arr, size_t arr_size) {
	heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
	heap->size = 1;
	heap->max_size = arr_size;
	heap->arr = (int*) calloc(arr_size, sizeof(int));
	heap->arr[0] = arr[0];
	for (int i = 1; i < arr_size; i++) {
		heap_add(heap, arr[i]);
	}
	return heap;
}

int* sort_array(int* arr, size_t arr_size) {
	heap_t* heap = heap_init_from_arr(arr, arr_size);
	int* new_arr = calloc(arr_size, sizeof(int));
	for (int i = 0; i < arr_size; i++) {
		new_arr[i] = heap_extract_min(heap);
	}
	return new_arr;
}

int* read_array(int* size) {
	scanf("%d", size);
	int* arr = calloc(*size, sizeof(int));
	for (int i = 0; i < *size; i++) {
		scanf("%d", &arr[i]);
	}
	return arr;
}

void print_array(int* arr, size_t arr_size) {
	for (int i = 0; i < arr_size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void main() {
	heap_t* h = heap_create(2, 2);
	heap_add(h, 3);
	heap_add(h, 1);
	heap_add(h, 4);
	print_heap(h);
	printf("%d\n", heap_extract_min(h));
	print_heap(h);
	printf("%d\n", h->size);
	int N;
	int* arr = read_array(&N);
	int* sorted = sort_array(arr, N);
	print_array(sorted, N);
}