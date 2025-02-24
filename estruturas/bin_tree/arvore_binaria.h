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
No* inserir_bst(No*, No*);
int minimo(No*, No*);
int maximo(No*, No*);
void heapfy(Lista*, No*, int(*)(No*, No*));
void full_heapfy(Lista*, int(*)(No*, No*));
void remover_heap(Lista*, int(*)(No*, No*));
Item* encontrar_No(Lista*, No*);
void trocar_nos(Lista*, No*, No*);
void escrever_arvore(No*);
void apagar_arvore(No*);
int contar_nos(No*);
No* encontrar_menor_arvore(No*, No*);
No* juntar_nos(No*, No*);
void apagar_arvore_full(No*);
No* encontrar_maior_arvore(No** array, size_t array_len);
#endif
