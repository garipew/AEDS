#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct heap{
	int* data;
	size_t len;
	int next;
} Heap;


Heap* criar_heapy(size_t);
void inserir_heapy(Heap*, int);
int min_heap(int, int);
int max_heap(int, int);
void heapyfy(Heap*, int, int(*)(int, int));
void full_heapyfy(Heap*, int (*)(int, int));
int remover_raiz(Heap*);
void apagar_heapy(Heap*);
void escrever_heapy(Heap*);

#endif
