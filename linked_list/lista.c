#include "lista.h"
#include <stdlib.h>
#include <stdio.h>


Lista* criar_lista(){
	Lista* l = malloc(sizeof(*l));
	l->primeiro = criar_item(NULL, -1);
	l->ultimo = l->primeiro;
	l->qtd = 0;
	return l;
}


Lista* criar_fila(Lista* head){
	Item* atual = head->primeiro->prox;
	Lista* fila = criar_lista();
	concat_item(fila, criar_item(atual, atual->idx));
	atual = atual->prox;
	while(atual != NULL){
		concat_item(fila, criar_item(atual, atual->idx));
		atual = atual->prox;	
	}
	return fila;
}


Item* criar_item(void* conteudo, int idx){
	Item* novo = malloc(sizeof(*novo));
	novo->conteudo = conteudo;
	novo->idx = idx;
	novo->prox = NULL;
	novo->ant = NULL;

	return novo;
}


Lista* criar_copia(Lista* head){
	if(head == NULL){
		return head;
	}
	Item* atual = head->primeiro->prox;
	Lista* cp = criar_lista();
	concat_item(cp, criar_item(atual->conteudo, atual->idx));
	atual = atual->prox;
	while(atual != NULL){
		concat_item(cp, criar_item(atual->conteudo, atual->idx));
		atual = atual->prox;
	}
	return cp;
}


Item* copiar_item(Lista* l, int idx){
	Item* atual = l->primeiro->prox;
	Item* copia = NULL;
	while((atual->prox != NULL) && (atual->idx != idx)){
		atual = atual->prox;
	}
	if(atual->idx == idx){
		copia = criar_item(atual->conteudo, idx);
	}
	return copia;
}


/* void concat_item(Lista*, Item*);
 * Adiciona item no fim da lista
 */
void concat_item(Lista* head, Item* novo){
	if(head == NULL){
		return;
	}
	if(head->ultimo == head->primeiro){
		head->primeiro->prox = novo;
	}
	Item* ultimo = head->ultimo;
	ultimo->prox = novo;
	head->ultimo = novo;
	novo->ant = ultimo;
	head->qtd++;
}


/* void concat_lista(Lista*, Item*)
 * Adiciona item no inicio da lista
*/
void concat_lista(Lista* head, Item* novo){
	if(head == NULL){
		return;
	}	
	Item* primeiro = head->primeiro;

	novo->prox = primeiro->prox;
	novo->prox->ant = novo;

	primeiro->prox = novo;
	novo->ant = primeiro;
	head->qtd++;
}


void escrever_lista(Lista* head){
	if(head == NULL || head->primeiro == NULL){
		return;
	}
	Item* i = head->primeiro->prox;
	while(i != NULL){
		printf("%d ", i->idx);
		i = i->prox;
	}
	printf("\n");
}


void* remover_item(Lista* head, Item* item){
	if(head == NULL){
		return NULL;
	}		
	Item* atual = head->primeiro;
	void* conteudo;
	while(atual->prox != item){
		atual = atual->prox;	
		if(atual == NULL){
			return NULL;
		}
	}
	Item* removido = atual->prox;
	conteudo = removido->conteudo;
	atual->prox = removido->prox;
	removido->prox->ant = atual;
	free(removido);
	head->qtd--;

	return conteudo;
}


void* remover_primeiro(Lista* head){
	if(head == NULL || head->primeiro == NULL){
		return head;
	}
	Item* removido = head->primeiro->prox == NULL ? head->primeiro : head->primeiro->prox;
	void* conteudo = removido->conteudo;
	head->primeiro->prox = removido->prox;
	if(removido != head->ultimo){
		removido->prox->ant = head->primeiro;
	} else{
		head->ultimo = head->primeiro;
		head->primeiro->prox = NULL;
	}
	free(removido);
	head->qtd--;
	return conteudo;	
}


void* remover_ultimo(Lista* head){
	if(head == NULL){
		return NULL;
	}

	Item* ultimo = head->ultimo;
	if(ultimo == NULL){
		return NULL;
	}
	void* conteudo = ultimo->conteudo;
	if(ultimo == head->primeiro){
		head->primeiro = NULL;
	} else{
		ultimo->ant->prox = NULL;
	}
	head->ultimo = ultimo->ant;
	free(ultimo);
	head->qtd--;
	return conteudo;	
}


void apagar_lista(Lista* head){
	if(head == NULL){
		return;
	}
	void* conteudo;
	if(head->primeiro!=NULL){
		while(head->primeiro->prox != NULL){
			conteudo = remover_ultimo(head);
			if(conteudo){
				free(conteudo);
			}
		}
		free(head->primeiro);
	}
	free(head);
}

int comparar_max(Item* a, Item* b){
	return (a != NULL) && (b != NULL)? a->idx > b->idx : 0;
}

int comparar_min(Item* a, Item* b){
	return (a != NULL) && (b != NULL)? a->idx < b->idx : 0;
}


/* void tornar_anterior(Lista* head, Item* a, Item* b)
 * Move a para antes de b
 * Mais eficiente que trocar a com anterior recursivamente ate trocar com b
 */
void tornar_anterior(Lista* head, Item* a, Item* b){
	if(a == NULL || head == NULL || head->primeiro == NULL || b == NULL){
		return;
	}
	if(a == b || b->ant == a){
		return;
	}
	if(a == head->primeiro || b == head->primeiro){
		return;
	}

	if(a == head->ultimo){
		head->ultimo = a->ant;
	} else{
		a->prox->ant = a->ant;
	}

	a->ant->prox = a->prox;

	b->ant->prox = a;
	a->ant = b->ant;
	b->ant = a;
	a->prox = b;
	
	return;
}


void trocar_itens(Lista* head, Item* a, Item* b){
	if(a == NULL || head == NULL || head->primeiro == NULL || b == NULL){
		return;
	}
	
	Item* a_prox = a->prox;
	Item* a_ant = a->ant;
	Item* b_prox = b->prox;
	Item* b_ant = b->ant;
	
	if(a == head->ultimo){
		head->ultimo = b;
	} else if(b == head->ultimo){
		head->ultimo = a;
	}

	/* a e b */
	a->prox = b->prox != a ? b->prox : b;
	a->ant = b->ant != a ? b->ant : b;
	b->prox = a_prox != b ? a_prox : a;
	b->ant = a_ant != b ? a_ant : a;

	/* vizinhos de a e b */
	a_ant->prox = a_ant != b ? b : a_prox;
	b_ant->prox = b_ant != a ? a : b_prox;
	if(a_prox != NULL){
		a_prox->ant = a_prox != b ? b : a_ant;
	}
	if(b_prox != NULL){
		b_prox->ant = b_prox != a ? a: b_ant;
	}
}


void insertion_sort(Lista* head, int(*compara)(Item*, Item*)){
	if(head == NULL || head->primeiro == NULL){
		return;
	}
	
	Lista *fila = criar_fila(head);
	Item *primeiro_fila = remover_primeiro(fila);

	Item *i = primeiro_fila;
	Item *j = i->ant;

	while(j != NULL){
		if(compara(i, j == head->primeiro ? NULL : j)){
			j = j->ant;
			continue;
		} 	
		
		if(j->prox != i){
			tornar_anterior(head, i, j->prox);
		}
		if(fila->primeiro == fila->ultimo){
			break;
		}
		primeiro_fila = remover_primeiro(fila);
		i = primeiro_fila;
		j = i->ant;
	}
	apagar_lista(fila);
}


Item* selecionar_item(Item* head, int(*compara)(Item*, Item*)){
	if(head == NULL){
		return head;
	}
	Item* selecionado = head;
	Item* atual = head;
	while(atual != NULL){
		if(compara(atual, selecionado)){
			selecionado = atual;
		}
		atual = atual->prox;
	}
	return selecionado;
}


void selection_sort(Lista* head, int(*compara)(Item*, Item*)){
	if(head == NULL){
		return;
	}
	Item* atual = head->primeiro->prox;
	Item* selecionado = selecionar_item(atual, compara);
	
	while(atual->prox != NULL){
		tornar_anterior(head, selecionado, atual);
		selecionado = selecionar_item(atual, compara);
		if(atual->prox == NULL){
			break;
		}
		while(selecionado == atual){
		// selecionado esta na posicao correta
			atual = atual->prox;
			if(atual->prox == NULL){
				break;
			}
			selecionado = selecionar_item(atual, compara);
		}
	}
}


void heap_sort(Lista* head, int(*compara)(No*, No*)){
	if(head == NULL){
		return;
	}	

	Item* atual = head->primeiro->prox;
	Lista* heap = criar_lista();
	concat_item(heap, criar_item(criar_no(atual, atual->idx), atual->idx));
	while(atual->prox != NULL){
		atual = atual->prox;
		inserir_nivel(heap, criar_no(atual, atual->idx));
	}

	full_heapfy(heap, compara);

	No* no_atual = heap->primeiro->prox->conteudo;
	atual = no_atual->dado; 
	atual->prox = NULL;
	atual->ant = head->primeiro;
	head->primeiro->prox = atual;
	remover_heap(heap, compara);
	while(heap->primeiro != heap->ultimo){
		no_atual = heap->primeiro->prox->conteudo;
		if(no_atual == NULL){
			break;
		}
		((Item*)no_atual->dado)->ant = atual;
		atual->prox = no_atual->dado;
		atual = atual->prox;
		atual->prox = NULL;
		head->ultimo = atual;
		remover_heap(heap, compara);
	}
	apagar_lista(heap);
}


void heapy_sort(Lista* head, int(*comp)(Item*, Item*)){
	Item* atual = head->primeiro->prox;	
	Heap* heap = criar_heapy(head->qtd);
	inserir_heapy(heap, atual);
	while(atual->prox != NULL){
		atual=atual->prox;
		inserir_heapy(heap, atual);
	}
	full_heapyfy(heap, comp);
	atual = head->primeiro;
	while(heap->next > 0){
		atual->prox = remover_raiz(heap);
		atual->prox->ant = atual;
		atual = atual->prox;
		atual->prox = NULL;
		full_heapyfy(heap, comp);
	}
	apagar_heapy(heap);
}
