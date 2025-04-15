#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include "../linked_list/lista.h"

typedef struct heap{
	Item** data;
	size_t len;
	int next;
} Heap;


Heap* criar_heap(size_t);
void inserir_heap(Heap*, Item*);
void heapfy(Heap*, int, int(*)(Item*, Item*));
void full_heapfy(Heap*, int (*)(Item*, Item*));
Item* remover_raiz(Heap*);
void apagar_heap(Heap*);
void escrever_heap(Heap*);

#endif
