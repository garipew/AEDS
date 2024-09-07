#include "lista.h"
#include <stdlib.h>
#include <stdio.h>


Lista* criar_lista(){
	Lista* l = malloc(sizeof(*l));
	l->primeiro = criar_item(NULL, -1);
	l->ultimo = l->primeiro;
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
	return conteudo;	
}


void apagar_lista(Lista* head){
	if(head == NULL){
		return;
	}
	while(head->primeiro->prox != NULL){
		remover_ultimo(head);
	}
	if(head->primeiro!=NULL){
		free(head->primeiro);
	}
	free(head);
}
