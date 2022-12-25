#include <stdlib.h>
#include <stdio.h>

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
	int N;
	scanf("%d", &N);
	int slice_begins[N], slice_ends[N];
	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		slice_begins[i] = x;
		slice_ends[i] = y;
	}
	for (int i = 0; i < N; i++) {
		printf("%d %d; ", slice_begins[i], slice_ends[i]);
	}

	/*int n1, n2;
	int* arr1 = read_array(&n1);
	int* arr2 = read_array(&n2);

	int max_n = n1 > n2 ? n1 : n2;

	int result[n1 + n2];
	int k = 0, m = 0, i = 0;
	while (k < n1 && m < n2) {
		if (arr1[k] > arr2[m]) {
			result[i++] = arr2[m++];
		} else {
			result[i++] = arr1[k++];
		}
	}
	if (k == n1) {
		for (; m < n2; m++) {
			result[i++] = arr2[m];
		}
	} else if (m == n2) {
		for (; k < n1; k++) {
			result[i++] = arr1[k];
		}
	}

	print_array(result, n1 + n2);*/
}