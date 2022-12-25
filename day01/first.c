#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	int *addr = &n;
	(*addr)++;
	printf("%d", n);
	return 0;
}