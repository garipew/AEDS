#include "sort.h"
#include <stdlib.h>
#include <stdio.h>


int comparar(Item* a, Item* b){
	return (a != NULL) && (b != NULL)? a->idx > b->idx : 0;
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
		if(compara(j_anterior, j)){
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


Item* selection_sort(Item* head, int(*compara)(Item*, Item*)){
	if(head == NULL){
		return head;
	}
	Item* inicio = head;
	Item* atual = inicio;
	Item* anterior;
	Item* menor = encontrar_menor(atual);
	
	while(atual->prox != NULL){
		inicio = mover_antes(inicio, menor, atual);
		menor = encontrar_menor(atual);
	}

	return inicio;
}


