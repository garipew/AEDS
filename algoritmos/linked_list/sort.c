#include "sort.h"
#include <stdlib.h>
#include <stdio.h>


int comparar_max(Item* a, Item* b){
	return (a != NULL) && (b != NULL)? a->idx > b->idx : 0;
}


int comparar_min(Item* a, Item* b){
	return (a != NULL) && (b != NULL)? a->idx < b->idx : 0;
}


/* Item* tornar_anterior(Item* head, Item* a, Item* b)
 * Move a para antes de b
 * Mais eficiente que trocar a com anterior recursivamente ate trocar com b
 */
Item* tornar_anterior(Item* head, Item* a, Item* b){
	if(a == NULL || head == NULL || b == NULL){
		return head;
	}
	if(a == b){
		return head;
	}
	Item* inicio = head;
	Item* a_anterior = encontrar_anterior(inicio, a);
	Item* b_anterior = encontrar_anterior(inicio, b);
	
	if(a_anterior != NULL){
		a_anterior->prox = a->prox;
	} else {
		inicio = a->prox;
	}

	if(b_anterior != NULL){
		b_anterior->prox = b_anterior != a ? a : b;
	} else {
		inicio = a;
	}

	a->prox = b;
	return inicio;
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
			j_anterior = encontrar_anterior(inicio, j_anterior);
			continue;
		} 	
		if(j_anterior == NULL){
			inicio = tornar_anterior(inicio, j, inicio);
		} else{
			inicio = tornar_anterior(inicio, j, j_anterior->prox);
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
	Item* selecionado = selecionar_item(atual, compara);
	
	while(atual->prox != NULL){
		inicio = tornar_anterior(inicio, selecionado, atual);
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

	return inicio;
}


Item* heap_sort(Item* head, int(*compara)(No*, No*)){
	if(head == NULL){
		return head;
	}	

	Item* inicio = head;
	Item* atual = inicio;
	Item* inicio_heap = criar_item(criar_no(atual, atual->idx), atual->idx);
	Item* ultimo_heap = inicio_heap;
	Item* novo_heap = inicio_heap;
	while(atual->prox != NULL){
		atual = atual->prox;
		novo_heap = inserir_nivel(novo_heap, &ultimo_heap, criar_no(atual, atual->idx));
	}


	inicio_heap = full_heapfy(inicio_heap, compara);

	No* no_atual = inicio_heap->conteudo;
	inicio = no_atual->dado; 
	atual = inicio;
	atual->prox = NULL;
	inicio_heap = remover_heap(inicio_heap, compara);
	while(inicio_heap != NULL){
		no_atual = inicio_heap->conteudo;
		if(no_atual == NULL){
			break;
		}
		atual = no_atual->dado;
		atual->prox = NULL;
		inicio = concat_item(inicio, atual);
		inicio_heap = remover_heap(inicio_heap, compara);
	}
	return inicio;
}
