#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct heap{
	int* data;
	size_t len;
	int next;
} Heap;


Heap* criar_heap(size_t);
void inserir_heap(Heap*, int);
int min_heap(int, int);
int max_heap(int, int);
void heapfy(Heap*, int, int(*)(int, int));
void full_heapfy(Heap*, int (*)(int, int));
int remover_raiz(Heap*);
void apagar_heap(Heap*);
void escrever_heap(Heap*);

#endif
