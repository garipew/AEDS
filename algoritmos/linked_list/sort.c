#include "sort.h"
#include <stdlib.h>
#include <stdio.h>


int comparar_max(Item* a, Item* b){
	return (a != NULL) && (b != NULL)? a->idx > b->idx : 0;
}


int comparar_min(Item* a, Item* b){
	return (a != NULL) && (b != NULL)? a->idx < b->idx : 0;
}


Item* trocar_itens(Item* head, Item* a, Item* b){
	if(a == NULL || head == NULL || b == NULL){
		return head;
	}
	Item* inicio = head;
	Item* a_anterior = encontrar_anterior(inicio, a->idx);
	Item* b_anterior = encontrar_anterior(inicio, b->idx);
	Item* a_prox = a->prox;
	
	if(a_anterior != NULL){
		a_anterior->prox = a_anterior->idx != b->idx ? b : a->prox;
	} else {
		inicio = b;
	}

	if(b_anterior != NULL){
		b_anterior->prox = b_anterior->idx != a->idx ? a : b->prox;
	} else {
		inicio = a;
	}

	a->prox = b->prox == NULL ? b->prox : b->prox->idx != a->idx ? b->prox : b;
	b->prox = a_prox == NULL ? a_prox : a_prox->idx != b->idx ? a_prox : a;

	return inicio;
}


Item* mover_antes(Item* head, Item* a, Item* b){
	if(a == NULL || head == NULL || b == NULL){
		return head;
	}
	Item* inicio = head;
	Item* a_anterior = encontrar_anterior(inicio, a->idx);
	Item* b_anterior = encontrar_anterior(inicio, b->idx);

	if(a_anterior != NULL){
		a_anterior->prox = a->prox;
	} else {
		inicio = a->prox;
	}
	
	if(b_anterior != NULL){
		b_anterior->prox = a;
	} else {
		inicio = a;
	}

	a->prox = b;

	return inicio;
}


Item* insertion_sort(Item* head, int(*compara)(Item*, Item*)){
	if(head == NULL){
		return head;
	}
	
	Item *inicio = head;
	Item *fila = criar_fila(inicio);
	Item *j_anterior = encontrar_anterior(inicio, fila->idx);
	Item *j = j_anterior == NULL ? inicio : j_anterior->prox;

	while(j != NULL){
		if(compara(j, j_anterior)){
			inicio = trocar_itens(inicio, j_anterior, j);
			j_anterior = encontrar_anterior(inicio, j->idx);
			continue;
		} 	
		fila = remover_primeiro(fila);
		if(fila == NULL){
			break;
		}
		j_anterior = encontrar_anterior(inicio, fila->idx);
		j = j_anterior == NULL ? inicio : j_anterior->prox;
	}

	return inicio;
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


Item* selection_sort(Item* head, int(*compara)(Item*, Item*)){
	if(head == NULL){
		return head;
	}
	Item* inicio = head;
	Item* atual = inicio;
	Item* anterior;
	Item* selecionado = selecionar_item(atual, compara);
	
	while(atual->prox != NULL){
		inicio = mover_antes(inicio, selecionado, atual);
		selecionado = selecionar_item(atual, compara);
	}

	return inicio;
}


Item* heap_sort(Item* head, int(*compara)(No*, No*)){
	if(head == NULL){
		return head;
	}	

	Item* inicio = head;
	Item* atual = inicio;
	No* heap = inserir_heap(NULL, criar_no(atual, atual->idx), minimo);
	while(atual->prox != NULL){
		atual = atual->prox;
		heap = inserir_heap(heap, criar_no(atual, atual->idx), minimo);
	}

	inicio = heap->dado;	
	atual = inicio;
	atual->prox = NULL;
	heap = remover_heap(heap);
	while(heap != NULL){
		atual = heap->dado;
		atual->prox = NULL;
		inicio = concat_item(inicio, atual);
		heap = remover_heap(heap);
	}

	return inicio;
}
