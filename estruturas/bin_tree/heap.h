#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include "../linked_list/lista.h"

typedef struct heap{
	Item** data;
	size_t len;
	int next;
} Heap;


Heap* criar_heapy(size_t);
void inserir_heapy(Heap*, Item*);
void heapyfy(Heap*, int, int(*)(Item*, Item*));
void full_heapyfy(Heap*, int (*)(Item*, Item*));
Item* remover_raiz(Heap*);
void apagar_heapy(Heap*);
void escrever_heapy(Heap*);

#endif
