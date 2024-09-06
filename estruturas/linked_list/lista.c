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
	Item* fila = concat_item(NULL, criar_item(atual, atual->idx));
	atual = atual->prox;
	while(atual != NULL){
		fila = concat_item(fila, criar_item(atual, atual->idx));
		atual = atual->prox;	
	}
	return fila;
}


Item* criar_copia(Item* head){
	if(head == NULL){
		return head;
	}
	Item* atual = head;
	Item* cp = criar_item(atual->conteudo, atual->idx);
	atual = atual->prox;
	while(atual != NULL){
		cp = concat_item(cp, criar_item(atual->conteudo, atual->idx));
		atual = atual->prox;
	}
	return cp;
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


Item* encontrar_ultimo_item(Item* head){
	Item* atual = head;
	while(atual->prox != NULL){
		atual = atual->prox;
	}
	return atual;
}


void escrever_lista(Item* head){
	Item* i = head;
	while(i != NULL){
		printf("%d ", i->idx);
		i = i->prox;
	}
	printf("\n");
}


/* encontrar_anterior(Item*, Item*)
 * Retorna o item que aponta ao item passado como argumento,
 * caso exista
 */
Item* encontrar_anterior(Item* head, Item* buscado){
	if(head == NULL){
		return head;
	}
	Item* anterior = head;
	if(anterior == buscado){
		return NULL;
	}	
	while(anterior->prox != NULL){
		if(anterior->prox == buscado){
			return anterior;
		}
		anterior = anterior->prox;
	}
	return NULL;
}


Item* encontrar_menor(Item* head){
	if(head == NULL){
		return head;
	}
	Item* atual = head;
	Item* menor = atual;
	while(atual->prox != NULL){
		atual = atual->prox;
		if(atual->idx < menor->idx){
			menor = atual;
		}
	}
	return menor;
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


void* remover_ultimo(Item* head){
	if(head == NULL){
		return NULL;
	}
	Item* atual = head;
	void* conteudo;
	if(atual->prox == NULL){
		conteudo = atual->conteudo;
		free(atual);
		return conteudo;	
	}
	while(atual->prox->prox != NULL){
		atual = atual->prox;
	}
	conteudo = atual->prox->conteudo;
	free(atual->prox);
	atual->prox = NULL;
	return conteudo;	
}


Item* apagar_lista(Item* head){
	while(head != NULL){
		head = remover_primeiro(head);
	}
	return NULL;
}
