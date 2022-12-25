#include "bin_heap.h"
#include "huffman_node.h"
#include "code.h"

int main(int argc, char const *argv[]) {
	const int BUF_SIZE = 100;
	const int ALPHABET_SIZE = 256;

	//uchar buf[BUF_SIZE];
	FILE* file = fopen(argv[1], "rb");
	uchar chbuf = 0;
	uchar last_bits = 8;
	//code_t char_code = {0, 8};
	//fread_code(file, &char_code, &chbuf, &last_bits);
	//print_code(&char_code);
	/*for (last_bits; last_bits > 0; last_bits--)
	{
		printf("Is one: %d, on last_bits = %u\n", is_one(chbuf, last_bits-1), last_bits);
	}*/
	//return 0; 

	bool is_read = false, is_right = false;
	uchar count = 0;
	huffman_node_t* parent = create_huffman();
	huffman_node_t* child;
	size_t eof = fread(&chbuf, 1, sizeof(uchar), file);
	while (eof > 0) {
		printf("eof %u\n", eof);
		//code_t chcode = {0, 8};
		//fread_code(file, &chcode, &chbuf, &last_bits);
		//print_code(&chcode);
		for (last_bits=7; last_bits >= 0; last_bits--)
		{
			if (last_bits > 7) {
				eof = fread(&chbuf, 1, sizeof(uchar), file);
				code_t bufcode = {chbuf, 8};
				//printf("Buf code when last bits > 7 - ");
				//print_code(&bufcode);
				last_bits = 7;
			}

			if (is_one(chbuf, last_bits)) {
				count++;
				child = create_huffman();
				if (is_right) {
					parent->right_child = child;
				} else {
					parent->left_child = child;
				}
				parent = child;
			} else {
				if (count == 0) {
					eof = 0; // to exit from main while loop
					break;
				}
				// 0 here read uchar after
				child = create_huffman();
				code_t chcode = {0, 8};
				eof = fread_code(file, &chcode, &chbuf, &last_bits);
				child->ch = chcode.code;
				//printf("Char code in bits: ");
				//print_code(&chcode);
				printf("Char code: %u; char: %c; count: %u; last bits: %u\n", chcode.code, chcode.code, count, last_bits);
				count = 0;
				if (is_right) {
					parent->right_child = child;
					is_right = false;
				} else {
					parent->left_child = child;
					is_right = true;
				}
			}
		}
	}
	fclose(file);

	return EXIT_SUCCESS;
}
