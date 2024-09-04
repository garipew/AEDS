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
	Item* anterior;
	while(anterior->prox->idx != idx){
		anterior = anterior->prox;
		if(anterior == NULL){
			return head->idx == idx ? head : NULL;
		}
	}
	return anterior;
}


Item* remover_primeiro(Item* head){
	if(head == NULL){
		return head;
	}
	Item* removido = head;
	head = head->prox;
	free(removido);
	return head;	
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
