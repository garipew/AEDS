#ifndef LINKED_LIST
#define LINKED_LIST


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
#endif
