#ifndef BIN_TREE
#define BIN_TREE

#include "../linked_list/lista.h"
#include <stddef.h>

typedef struct no {
	void* dado;
	int idx;
	struct no* esq;
	struct no* dir;
} No;

No* criar_no(void*, int);
Item* inserir_nivel(Lista*, No*);
No* juntar_nos(No*, No*);

int contar_nos(No*);
void escrever_arvore(No*);

No* inserir_bst(No*, No*);
No* bin_search(No*, int);

int minimo(No*, No*);
int maximo(No*, No*);

void apagar_arvore(No*);
#endif
