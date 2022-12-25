#include "bin_heap.h"
#include "huffman_node.h"
#include "code.h"

void create_dict_arr(FILE* fp, huffman_node_t* root, uchar count, uchar* chbuf, uchar* last_bits) {
	huffman_node_t* left = root->left_child;
	huffman_node_t* right = root->right_child;
	count++;
	if (left) {
		// has children and recursive call
		create_dict_arr(fp, left, count, chbuf, last_bits);
		create_dict_arr(fp, right, 0, chbuf, last_bits);
	} else {
		uchar ch = root->ch;
		if (ch == '\0') return;
		uchar code = 2; // 0b10
		for (int i = 1; i < count; ++i)
		{
			code |= (1 << i+1);
		}
		code_t bitcode = {code, count+1};
		code_t charcode = {ch, 8};
		//printf("Count: %u\n", count);
		//printf("Bitcode: ");
		//print_code(&bitcode);
		//printf("Char code: ");
		//print_code(&charcode);
		fwrite_code(fp, &bitcode, chbuf, last_bits);
		fwrite_code(fp, &charcode, chbuf, last_bits);
		/*bytes_read += */ //fwrite(&root->ch, 1, sizeof(uchar), fp);
	}
}

void write_archive(FILE* file, code_list_t* clist, uchar* buf, size_t buf_size, uchar* chbuf, uchar* last_bits) {
	for (int i = 0; i < buf_size; ++i)
	{
		code_t* code;
		if ((code = get_code(clist, buf[i])) != NULL) {
			/*uchar sz = code->size;
			if (sz > last_bits) {
				if (last_bits > 0) {
					sz -= last_bits;
					uchar fbits = code->code >> sz;
					chbuf |= fbits;
				}
				fwrite(&chbuf, sizeof(uchar), 1, file);
				last_bits = 8 - sz;
				chbuf = code->code << last_bits;
			} else {
				last_bits -= sz;
				chbuf |= (code->code << last_bits);
			}*/
			fwrite_code(file, code, chbuf, last_bits);
		}
	}
}

int main(int argc, char const *argv[]) {
	const int BUF_SIZE = 100;
	const int ALPHABET_SIZE = 256;

	// Read input file
	uchar buf[BUF_SIZE];
	FILE* file = fopen(argv[1], "rb");
	int bytes_read = fread(buf, sizeof(uchar), BUF_SIZE, file);
	fclose(file);
	printf("%s\n", buf);

	// Create map of nodes
	const int NODES_SIZE = ALPHABET_SIZE < bytes_read ? ALPHABET_SIZE : bytes_read;
	map_nodes_t* nodes = create_nodes(NODES_SIZE);
	for (int i = 0; i < bytes_read; ++i)
	{
		inc_node(nodes, buf[i]);
	}
	//print_nodes(nodes);

	// Create binary heap from nodes
	heap_t* heap = heap_init(nodes->data, nodes->count);
	//print_heap(heap);
	// Extract two mins and make big node with children (make new binary tree with big nodes)
	while (heap->size > 1) {
		huffman_node_t* node1 = huffman_copy(heap_extract_min(heap));
		huffman_node_t* node2 = huffman_copy(heap_extract_min(heap));
		//print_huffman_node(node1);
		//print_huffman_node(node2);
		huffman_node_t big_node = {'\0', node1->count + node2->count, node1, node2};
		heap_add(heap, big_node);
	}
	huffman_node_t* root = &heap->arr[0];
	print_huffman(root);

	// Create list of possible codes
	code_list_t* code_list = init_code_list(NODES_SIZE);
	code_t empty_code = {0, 0};
	set_code(root, empty_code, code_list); // Create dictionary with codes and chars
	for (int i = 0; i < code_list->i; i++) {
		//printf("{'%c' %u with size %u} with binary code ", code_list->chs[i], code_list->codes[i].code, code_list->codes[i].size);
		code_t chrcode = {code_list->chs[i], 8};
		//print_code(&chrcode);
	}

	file = fopen(argv[2], "wb");
	uchar chbuf = 0;
	uchar last_bits = 8;
	create_dict_arr(file, root, 0, &chbuf, &last_bits);
	code_t end_code = {0, 1};
	fwrite_code(file, &end_code, &chbuf, &last_bits);
	write_archive(file, code_list, buf, BUF_SIZE, &chbuf, &last_bits);
	if (last_bits < 8 && last_bits > 0) {
		fwrite(&chbuf, sizeof(uchar), 1, file);
	}
	fclose(file);

	free(code_list);
	free(root);
	free(heap);
	free(nodes);

	return EXIT_SUCCESS;
}