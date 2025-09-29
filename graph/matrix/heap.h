#ifndef HEAP_H
#define HEAP_H

typedef struct pair{
	int distance;
	int vertex;
} Pair;

typedef struct heap{
	Pair* nodes;
	int size;
	int count;
} Heap;

Heap* criar_heap(int); 
void inserir_heap(Heap*, int, int);
void heapfy(Heap*);
void apagar_heap(Heap*);
void print_heap(Heap*);
Pair remover_heap(Heap*);
#endif
