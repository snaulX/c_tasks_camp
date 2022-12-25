#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void print_array(int* arr, size_t arr_size) {
	for (int i = 0; i < arr_size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void insert(int* arr, int value, int index, size_t arr_size) {
	for (int i = arr_size - 1; i > index; i--) {
		arr[i] = arr[i - 1];
	}
	arr[index] = value;
}

int find_max(int* arr, size_t arr_size) {
	int _max = arr[0];
	for (int i = 1; i < arr_size; i++) {
		if (arr[i] > _max) {
			_max = arr[i];
		}
	}
	return _max;
}

void print_two_maxes(int* arr, size_t arr_size) {
	int _max1 = arr[0], _max2 = arr[0];
	for (int i = 1; i < arr_size; i++) {
		if (arr[i] > _max1) {
			_max2 = _max1;
			_max1 = arr[i];
		} else if (arr[i] > _max2) {
			_max2 = arr[i];
		}
	}
	printf("%d %d\n", _max1, _max2);
}

long long find_max_product(int* arr, size_t arr_size) {
	int min1 = arr[0], min2 = arr[0], max1 = arr[0], max2 = arr[0];
	for (int i = 1; i < arr_size; i++) {
		int elem = arr[i];
		if (elem > max1) {
			max2 = max1;
			max1 = elem;
		} else if (elem > max2) {
			max2 = elem;
		} else if (elem < min1) {
			min2 = min1;
			min1 = elem;
		} else if (elem < min2) {
			min2 = elem;
		}
	}
	long long minCheck = -1, maxCheck = -1;
	if (max1 * max2 > min1 * min2) {
		return max1 * max2;
	} else {
		return min1 * min2;
	}
}

int main()
{
	int N;
	scanf("%d\n", &N);
	int arr[N];
	for (int i = 0; i < N; i++) {
		int a;
		scanf("%d\n", &a);
		arr[i] = a;
	}
	print_array(arr, N);
	printf("%d\n", find_max(arr, N));
	printf("%ld\n", find_max_product(arr, N));
	print_two_maxes(arr, N);
	insert(arr, 3, 6, N);
	print_array(arr, N);
	return EXIT_SUCCESS;
}