#include "lista.h"
#include <stdlib.h>
#include <stdio.h>


Item* criar_item(void* conteudo, int idx){
	Item* novo = malloc(sizeof(*novo));
	novo->conteudo = conteudo;
	novo->idx = idx;
	novo->prox = NULL;

	return novo;
}


Item* criar_fila(Item* head){
	Item* atual = head;
	Item* fila = concat_item(NULL, criar_item(NULL, atual->idx));
	atual = atual->prox;
	while(atual != NULL){
		fila = concat_item(fila, criar_item(NULL, atual->idx));
		atual = atual->prox;	
	}
	return fila;
}


/* Item* concat_item(Item*, Item*);
 * Recebe dois itens e adiciona o segundo no fim da
 * sequencia de prox do primeiro
 */
Item* concat_item(Item* head, Item* novo){
	if(head == NULL){
		return novo;
	}
	Item* atual = head;
	while(atual->prox != NULL){
		atual = atual->prox;
	}
	atual->prox = novo;

	return head;	
}


void escrever_lista(Item* head){
	Item* i = head;
	while(i != NULL){
		printf("%d ", i->idx);
		i = i->prox;
	}
	printf("\n");
}


/* encontrar_anterior(Item*, int)
 * Retorna o item que aponta ao item com o idx solicitado,
 * caso exista
 */
Item* encontrar_anterior(Item* head, int idx){
	if(head == NULL){
		return head;
	}
	Item* anterior = head;
	if(anterior->idx == idx){
		return NULL;
	}	
	while(anterior->prox->idx != idx){
		anterior = anterior->prox;
		if(anterior == NULL){
			return NULL;
		}
	}
	return anterior;
}


Item* remover_item(Item* head, int idx){
	if(head == NULL){
		return head;
	}		
	Item* atual = head;
	while(atual->prox->idx != idx){
		atual = atual->prox;	
		if(atual == NULL){
			return head;
		}
	}
	Item* removido = atual->prox;
	atual->prox = atual->prox->prox;
	free(removido);

	return head;
}


Item* remover_primeiro(Item* head){
	if(head == NULL){
		return head;
	}
	Item* removido = head;
	Item* inicio = removido->prox;
	free(removido);
	return inicio;	
}


Item* remover_ultimo(Item* head){
	if(head == NULL){
		return head;
	}
	Item* atual = head;
	if(atual->prox == NULL){
		free(head);
		return NULL;	
	}
	while(atual->prox->prox != NULL){
		atual = atual->prox;
	}
	free(atual->prox);
	atual->prox = NULL;
	return head;	
}


Item* apagar_lista(Item* head){
	while(head != NULL){
		escrever_lista(head);
		head = remover_primeiro(head);
	}
	return NULL;
}
