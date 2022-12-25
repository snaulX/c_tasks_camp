#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct huffman_node_t huffman_node_t;

struct huffman_node_t {
	uchar ch;
	int count;
	huffman_node_t* left_child;
	huffman_node_t* right_child;
};

huffman_node_t* create_huffman() {
	huffman_node_t* node = (huffman_node_t*) malloc(sizeof(huffman_node_t));
	node->ch = '\0';
	node->count = 0;
	node->left_child = NULL;
	node->right_child = NULL;
	return node;
}

void print_huffman(huffman_node_t* node) {
	printf("{'%c' %d}\n", node->ch, node->count);
	huffman_node_t* left = node->left_child;
	huffman_node_t* right = node->right_child;
	if (left) {
		printf("left ");
		print_huffman(left);
		printf(" ");
	} else {
		return;
	}
	if (right) {
		printf("right ");
		print_huffman(right);
		printf(" ");
	} else {
		return;
	}
}

void print_huffman_node(huffman_node_t* node) {
	printf("{'%c' %d}\n", node->ch, node->count);
}

huffman_node_t* huffman_copy(huffman_node_t node) {
	huffman_node_t* new_node = (huffman_node_t*) malloc(sizeof(huffman_node_t));
	*new_node = node;
	return new_node;
}

typedef struct {
	size_t count;
	huffman_node_t* data;
} map_nodes_t;

map_nodes_t* create_nodes(size_t count) {
	map_nodes_t* nodes = (map_nodes_t*) malloc(sizeof(map_nodes_t));
	nodes->count = count;
	nodes->data = (huffman_node_t*) calloc(count, sizeof(huffman_node_t));
	for (int i = 0; i < count; ++i)
	{
		huffman_node_t* node = &nodes->data[i];
		node->ch = '\0';
		node->count = 0;
		node->left_child = NULL;
		node->right_child = NULL;
	}
	return nodes;
}

void inc_node(map_nodes_t* nodes, uchar key) {
	for (int i = 0; i < nodes->count; ++i)
	{
		uchar ch = nodes->data[i].ch;
		if (key == '\0') return;
		if (ch == '\0') {
			huffman_node_t* node = &nodes->data[i];
			node->ch = key;
			node->count = 1;
			node->left_child = NULL;
			node->right_child = NULL;
			return;
		}
		if (ch == key) {
			nodes->data[i].count++;
			return;
		}
	}
	printf("'inc_node' not working well\n");
}

void print_nodes(map_nodes_t* nodes) {
	for (int i = 0; i < nodes->count; ++i)
	{
		uchar ch = nodes->data[i].ch;
		if (ch == '\0') {
			break;
		}
		printf("{'%c' %d} ", ch, nodes->data[i].count);
	}
	printf("\n");
}

#endif // HUFFMAN_NODE_H