#include "sort.h"
#include <stdlib.h>


int comparar(Item* a, Item* b){
	return a->idx > b->idx;
}


Item* trocar_itens(Item* head, Item* a, Item* b){
	if(a == NULL || head == NULL || b == NULL){
		return head;
	}
	Item* a_anterior = encontrar_anterior(head, a->idx);
	Item* b_anterior = encontrar_anterior(head, b->idx);
	Item* a_prox = a->prox;

	if(a_anterior != NULL){
		a_anterior->prox = b;
	}
	if(b_anterior != NULL){
		b_anterior->prox = a;
	}
	a->prox = b->prox;
	b->prox = a_prox;

	return head;
}


Item* insertion_sort(Item* head, Item* novo, int(*compara)(Item*, Item*)){
	if(head == NULL){
		return head;
	}

	Item* atual = head;
	if(compara(atual, novo)){
		novo->prox = atual;
		return novo;
	}

	while(atual->prox != NULL){
		if(compara(atual->prox, novo)){
			novo->prox = atual->prox;
			atual->prox = novo;
			return head;
		}
		atual = atual->prox;
	}		
	concat_item(atual, novo);
	return head;
}
