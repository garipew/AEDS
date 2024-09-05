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
	Item* a_anterior = encontrar_anterior(inicio, a);
	Item* b_anterior = encontrar_anterior(inicio, b);
	Item* a_prox = a->prox;
	
	if(a_anterior != NULL){
		a_anterior->prox = a_anterior != b ? b : a->prox;
	} else {
		inicio = b;
	}

	if(b_anterior != NULL){
		b_anterior->prox = b_anterior != a ? a : b->prox;
	} else {
		inicio = a;
	}

	a->prox = b->prox == NULL ? b->prox : b->prox != a ? b->prox : b;
	b->prox = a_prox == NULL ? a_prox : a_prox != b ? a_prox : a;

	return inicio;
}


Item* insertion_sort(Item* head, int(*compara)(Item*, Item*)){
	if(head == NULL){
		return head;
	}
	
	Item *inicio = head;
	Item *fila = criar_fila(inicio);
	Item *j_anterior = encontrar_anterior(inicio, (Item*)fila->conteudo);
	Item *j = j_anterior == NULL ? inicio : j_anterior->prox;

	while(j != NULL){
		if(compara(j, j_anterior)){
			inicio = trocar_itens(inicio, j_anterior, j);
			j_anterior = encontrar_anterior(inicio, j);
			continue;
		} 	
		fila = remover_primeiro(fila);
		if(fila == NULL){
			break;
		}
		j_anterior = encontrar_anterior(inicio, (Item*)fila->conteudo);
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
		do{
			anterior = encontrar_anterior(inicio, selecionado);
			inicio = trocar_itens(inicio, anterior, selecionado);
		} while(anterior != atual);
		selecionado = selecionar_item(atual, compara);
		while(selecionado == atual){
		// selecionado esta na posicao correta
			atual = atual->prox;
			if(atual->prox == NULL){
				break;
			}
			selecionado = selecionar_item(atual, compara);
		}
	}

	return inicio;
}


Item* heap_sort(Item* head, int(*compara)(No*, No*)){
	if(head == NULL){
		return head;
	}	

	Item* inicio = head;
	Item* atual = inicio;
	No* heap = criar_no(atual, atual->idx);
	while(atual->prox != NULL){
		atual = atual->prox;
		heap = inserir_nivel(heap, criar_no(atual, atual->idx), NULL);
	}

	heap = heapfy(heap, compara);
	inicio = heap->dado;	
	atual = inicio;
	atual->prox = NULL;
	heap = remover_heap(heap, compara);
	while(heap != NULL){
		atual = heap->dado;
		atual->prox = NULL;
		inicio = concat_item(inicio, atual);
		heap = remover_heap(heap, compara);
	}

	return inicio;
}
