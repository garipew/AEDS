#ifndef BIN_TREE
#define BIN_TREE

#include "../linked_list/lista.h"

typedef struct no {
	void* dado;
	int idx;
	struct no* esq;
	struct no* dir;
} No;

No* criar_no(void*, int);
Item* inserir_nivel(Item*, No*);
No* inserir_bst(No*, No*);
int minimo(No*, No*);
int maximo(No*, No*);
Item* heapfy(Item*, No*, int(*)(No*, No*));
Item* full_heapfy(Item*, int(*)(No*, No*));
Item* remover_heap(Item*, int(*)(No*, No*));
Item* encontrar_No(Item*, No*);
void escrever_arvore(No*);
void apagar_arvore(No*);
#endif
