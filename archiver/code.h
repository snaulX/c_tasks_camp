#ifndef CODE_H
#define CODE_H
#include <stdbool.h>
#include "huffman_node.h"

typedef struct {
	uchar code;
	uchar size;
} code_t;

bool is_one(uchar chbuf, uchar index) {
	uchar one_numb = 1 << index;
	return (one_numb & chbuf) == one_numb;
}

void print_code(code_t* code) {
	for (int i = code->size-1; i >= 0; --i)
	{
		printf("%c", is_one(code->code, i) ? '1' : '0');
	}
	printf("\n");
}

void fwrite_code(FILE* fp, code_t* code, uchar* chbuf, uchar* last_bits) {
	uchar sz = code->size;
	if (sz > *last_bits) {
		if (*last_bits > 0) {
			sz -= *last_bits;
			uchar fbits = code->code >> sz;
			*chbuf |= fbits;
		}
		fwrite(chbuf, sizeof(uchar), 1, fp);
		*last_bits = 8 - sz;
		*chbuf = code->code << *last_bits;
	} else {
		*last_bits -= sz;
		*chbuf |= (code->code << *last_bits);
	}
}

size_t fread_code(FILE* fp, code_t* code, uchar* chbuf, uchar* last_bits) {
	size_t ret_value = 1;
	uchar sz = code->size;
	if (sz > *last_bits) {
		if (*last_bits > 0) {
			sz -= *last_bits;
			uchar fbits = *chbuf << sz;
			code->code |= fbits;
		}
		ret_value = fread(chbuf, 1, sizeof(uchar), fp);
		*last_bits = 8 - sz;
		code->code |= *chbuf >> *last_bits;
	} else {
		*last_bits -= sz;
		code->code = (*chbuf << *last_bits);
	}
	return ret_value;
}

typedef struct {
	uchar count;
	uchar* chs;
	code_t* codes;
	uchar i;
} code_list_t;

code_list_t* init_code_list(uchar length) {
	code_list_t* clist = (code_list_t*) malloc(sizeof(code_list_t));
	clist->count = length;
	clist->chs = (uchar*)calloc(length, sizeof(uchar));
	clist->codes = (code_t*)calloc(length, sizeof(code_t));
	clist->i = 0;
	return clist;
}

code_t* get_code(code_list_t* clist, uchar ch) {
	for (int i = 0; i < clist->i; i++) {
		if (clist->chs[i] == ch) {
			return &clist->codes[i];
		}
	}
	return NULL;
}

void set_code(huffman_node_t* root, code_t cur_code, code_list_t* clist) {
	huffman_node_t* left = root->left_child;
	huffman_node_t* right = root->right_child;
	if (root->ch != '\0') {
		int i = clist->i;
		clist->chs[i] = root->ch;
		clist->codes[i] = cur_code;
		clist->i++;
	} 
	if (left) {
		uchar left_code = cur_code.code << 1;
		left_code |= 1;
		code_t new_code = {left_code, cur_code.size+1};
		set_code(left, new_code, clist);
	} else {
		return;
	}
	if (right) {
		uchar right_code = cur_code.code << 1;
		right_code |= 0;
		code_t new_code = {right_code, cur_code.size+1};
		set_code(right, new_code, clist);
	} else {
		return;
	}
}

#endif // CODE_H