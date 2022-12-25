#include <stdlib.h>
#include <stdio.h>

typedef struct node_t node_t;

struct node_t {
	int value;
	node_t* next;
};

node_t* new_list(int value) {
	node_t* l = (node_t*)malloc(sizeof(node_t));
	l->value = value;
	l->next = NULL;
	return l;
}

node_t* list_insert(node_t* l, int value) {
	node_t* prev_next = l->next;
	node_t* param = (node_t*) malloc(sizeof(node_t));
	param->value = value;
	param->next = prev_next;
	l->next = param;
	return param;
}

int list_remove(node_t* prev) {
	if (!prev || !prev->next) {
		printf("Item to remove not found\n");
		exit(EXIT_FAILURE);
	}
	node_t* to_remove = prev->next;
	prev->next = to_remove->next;
	int ret = to_remove->value;
	free(to_remove);
	return ret;
}

/// Reverses list and return new head
node_t* list_reverse(node_t* head) {
	if (!head) { // 'head' doesn't exists so return NULL
		return NULL;
	}
	node_t* prev = head;
	node_t* cur = head->next;
	if (!cur) { // 'head' hasn't 'next' so return 'head'
		return head;
	}
	head->next = NULL;
	while (cur->next) {
		node_t* _next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = _next;
	}
	cur->next = prev;
	return cur;
}

void print_list(node_t* l) {
	node_t* _next = l;
	while (_next) {
		printf("%d ", _next->value);
		_next = _next->next;
	}
	printf("\n");
}

void free_list(node_t* l) {
	node_t* cur = l;
	node_t* to_free = l;
	while (cur) {
		to_free = cur;
		cur = cur->next;
		free(to_free);
	}
}

void main() {
	node_t* head = new_list(1);
	node_t* second = list_insert(head, 2);
	list_insert(second, 4);
	node_t* three = list_insert(second, 3);
	print_list(head);
	printf("%d\n", list_remove(three)); // remove '4'
	print_list(head);
	node_t* new_head = list_reverse(head);
	print_list(new_head);
	free_list(head);
}