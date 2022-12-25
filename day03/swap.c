#include <stdio.h>
#include <stdlib.h>

void print_array(int* arr, size_t arr_size) {
	for (int i = 0; i < arr_size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void my_swap(int* a, int* b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void reverse_array(int* arr, size_t arr_size) {
	for (int i = 0; i < arr_size>>1; i++) {
		my_swap(&arr[i], &arr[arr_size-i-1]);
	}
}

typedef struct {
	int a;
	float b;
} MyStruct;

void main() {
	int n;
	scanf("%d", &n);
	int* arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	reverse_array(arr, n);
	print_array(arr, n);
	free(arr);
	/*MyStruct* ms = (MyStruct*)malloc(sizeof(MyStruct));
	ms->a = 4;
	ms->b = 10.5;
	int* a = (int*)ms;
	float* b = (float*)((char*)ms + sizeof(int));
	printf("%d %f", *a, *b);*/
}