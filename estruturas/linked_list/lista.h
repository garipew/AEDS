#ifndef LINKED_LIST
#define LINKED_LIST


typedef struct item{
	void* conteudo;
	int idx;
	struct item* prox;
} Item;


Item* criar_item(void*, int);
Item* concat_item(Item*, Item*);
Item* remover_item(Item*, int);
Item* remover_primeiro(Item*);
Item* remover_ultimo(Item*);
Item* encontrar_anterior(Item*, int);
Item* criar_fila(Item*);
void escrever_lista(Item*);
Item* encontrar_menor(Item*);
Item* apagar_lista(Item*);
#endif
