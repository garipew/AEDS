#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stddef.h>
#include "../linked_list/sort.h"

No** encontrar_alfabeto(const unsigned char*, size_t);
void in_to_tree(const unsigned char*, size_t);
void huffman_coding(const unsigned char*, size_t);
void huffman_decoding(const unsigned char*, size_t);
#endif
