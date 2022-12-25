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

int bin_search(int* arr, int arr_size, int x) {
	int l = -1, r = arr_size;
	while (r-l > 1) {
		int mid = (l+r)/2;
		if (x > arr[mid]) {
			l = mid;
		} else if (x < arr[mid]) {
			r = mid;
		} else {
			return mid;
		}
	}
	return -1;
}

void main() {
	int N;
	int* arr = read_array(&N);
	int to_find;
	scanf("%d", &to_find);
	printf("%d\n", bin_search(arr, N, to_find));
}