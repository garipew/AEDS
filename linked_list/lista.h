#ifndef LINKED_LIST
#define LINKED_LIST

#include "lista.h"
#include "../bin_tree/arvore_binaria.h"
#include "../bin_tree/heap.h"

typedef struct item{
	void* conteudo;
	int idx;
	struct item* prox;
	struct item* ant;
} Item;


typedef struct lista{
	struct item* primeiro;
	struct item* ultimo;
	int qtd;
} Lista;


Lista* criar_lista();
Lista* criar_fila(Lista*);
Item* criar_item(void*, int);
Lista* criar_copia(Lista*);
Item* copiar_item(Lista*, int);
void concat_item(Lista*, Item*);
void concat_lista(Lista*, Item*);
void escrever_lista(Lista*);
void* remover_item(Lista*, Item*);
void* remover_primeiro(Lista*);
void* remover_ultimo(Lista*);
void apagar_lista(Lista*);
int comparar_min(Item*, Item*);
int comparar_max(Item*, Item*);
void trocar_itens(Lista*, Item*, Item*);
void tornar_anterior(Lista*, Item*, Item*);
void insertion_sort(Lista*, int(*)(Item*, Item*));
void selection_sort(Lista*, int(*)(Item*, Item*));
void heap_sort(Lista*, int(*)(No*, No*));
void heapy_sort(Lista*, int(*)(Item*, Item*));

#endif
