#include "arvore_binaria.h"
#include "../linked_list/lista.h"
#include <stdlib.h>
#include <stdio.h>


No* criar_no(void* dado, int idx){
	No* no = malloc(sizeof(*no));
	no->dado = dado;
	no->idx = idx;
	no->esq = NULL;
	no->dir = NULL;
	
	return no;
}


No* inserir_nivel(No* head, No* novo, No* anterior){
	if(head == NULL){
		return novo;
	}
	No* inicio = head;
	Item* fila = criar_item(inicio, 0);
	Item* fila_atual = fila;
	No* no_atual;

	while(fila_atual != NULL){
		no_atual = (No*)fila_atual->conteudo;
		if(no_atual->esq != NULL){
			fila = concat_item(fila, criar_item(no_atual->esq, 0));
		} else{
			no_atual->esq = novo;
			anterior = no_atual;
			fila = apagar_lista(fila);
			return inicio;
		}
		if(no_atual->dir != NULL){
			fila = concat_item(fila, criar_item(no_atual->dir, 0));
		} else{
			no_atual->dir = novo;
			anterior = no_atual;
			fila = apagar_lista(fila);
			return inicio;
		}
		fila_atual = fila_atual->prox;
	}
	fila = apagar_lista(fila);
	return inicio;
}


No* encontrar_pai(No* head, No* no){
	if(head == NULL){
		return NULL;
	}
	if(head == no){
		return NULL;
	}
	int i = 0;
	Item* fila = criar_item(head, i++);
	Item* fila_atual = fila;
	No* no_atual;

	while(fila_atual != NULL){
		no_atual = (No*)fila_atual->conteudo;
		if(no_atual->esq == no){
			fila = apagar_lista(fila);
			return no_atual;
		} else if(no_atual->esq != NULL){
			fila = concat_item(fila, criar_item(no_atual->esq, i++));
		}
		if(no_atual->dir == no){
			fila = apagar_lista(fila);
			return no_atual;
		} else if(no_atual->dir != NULL) {
			fila = concat_item(fila, criar_item(no_atual->dir, i++));
		}
		fila_atual = fila_atual->prox;
	}

	fila = apagar_lista(fila);
	return NULL;
}


No* inserir_bst(No* no, No* raiz){	
	if(no->idx == raiz->idx){
		return raiz;
	}
	if(no->idx < raiz->idx){
		if(raiz->esq == NULL){
			raiz->esq = no;
			return raiz;
		}
		return inserir_bst(no, raiz->esq);
	}
	if(no->idx > raiz->idx){
		if(raiz->dir == NULL){
			raiz->dir = no;
			return raiz;
		} 
		return inserir_bst(no, raiz->dir);
	}
}


No* trocar_pai(No* head, No* pai, No* filho){
	if(head == NULL || pai == NULL || filho == NULL){
		return head;	
	}

	No* inicio = head;
	No* pai_anterior = encontrar_pai(inicio, pai);
	No* pai_esq = pai->esq;
	No* pai_dir = pai->dir;

	if(pai_anterior != NULL){
		pai_anterior->esq = pai_anterior->esq == pai ? filho : pai_anterior->esq;
		pai_anterior->dir = pai_anterior->dir == pai ? filho : pai_anterior->dir;
	} else{
		inicio = filho;
	}

	pai->esq = filho->esq;
	pai->dir = filho->dir;
	filho->esq = pai_esq == filho ? pai : pai_esq;
	filho->dir = pai_dir == filho ? pai : pai_dir;

	return inicio;
}


int minimo(No* a, No* b){
	return (a != NULL && b != NULL) ? a->idx < b->idx : 0;
}


int maximo(No* a, No* b){
	return (a != NULL && b != NULL) ? a->idx > b->idx : 0;
}


No* inserir_heap(No* head, No* novo, int(*comp)(No*, No*)){
	No* anterior = NULL;
	No* inicio = inserir_nivel(head, novo, anterior);
	No* nova_raiz;

	anterior = encontrar_pai(inicio, novo);

	while(comp(novo, anterior)){
		anterior = encontrar_pai(inicio, novo);
		nova_raiz = trocar_pai(inicio, anterior, novo);
		inicio = nova_raiz == NULL ? inicio : nova_raiz;
	}

	return inicio;
}


void pre_order(No* raiz){
	if(raiz == NULL){
		return;
	}
	printf("%d ", raiz->idx);	
	pre_order(raiz->esq);
	pre_order(raiz->dir);
}


void in_order(No* raiz){
	if(raiz == NULL){
		return;
	}
	in_order(raiz->esq);
	printf("%d ", raiz->idx);	
	in_order(raiz->dir);
}


void pos_order(No* raiz){
	if(raiz == NULL){
		return;
	}
	pos_order(raiz->esq);
	pos_order(raiz->dir);
	printf("%d ", raiz->idx);	
}


void escrever_arvore(No* raiz){
	printf("pre: ");
	pre_order(raiz);
	printf("\n");
	printf("in: ");
	in_order(raiz);
	printf("\n");
	printf("pos: ");
	pos_order(raiz);
	printf("\n");
}


No* trocar_nos(No* head, No* a, No* b){
	if(head == NULL || a == NULL || b == NULL){
		return head;	
	}

	No* inicio = head;
	No* a_anterior = encontrar_pai(inicio, a);
	No* b_anterior = encontrar_pai(inicio, b);
	No* a_esq = a->esq;
	No* a_dir = a->dir;

	if(a_anterior != NULL){
		a_anterior->esq = a_anterior->esq == a ? b : a_anterior->esq;
		a_anterior->dir = a_anterior->dir == a ? b : a_anterior->dir;
	} else{
		inicio = b;
	}

	if(b_anterior != NULL){
		b_anterior->esq = b_anterior->esq == b ? a : b_anterior->esq;
		b_anterior->dir = b_anterior->dir == b ? a : b_anterior->dir;
	} else{
		inicio = a;
	}

	a->esq = b->esq == a ? b : b->esq;
	a->dir = b->dir == a ? b : b->dir;
	b->esq = a_esq == b ? a : a_esq;
	b->dir = a_dir == b ? a : a_dir;

	return inicio;
}


No* heapfy(No* head, int(*comp)(No*, No*)){
	if(head == NULL){
		return head;
	}

	No* inicio = head;
	No* atual = inicio;
	No* escolhido = inicio;
	if(inicio->esq == NULL && inicio->dir == NULL){
		return inicio;
	}

	atual->esq = heapfy(atual->esq, comp);
	atual->dir = heapfy(atual->dir, comp);
	if(comp(atual->esq, escolhido)){
		escolhido = atual->esq;
	}
		
	if(comp(atual->dir, escolhido)){
		escolhido = atual->dir;
	}

	while(escolhido != atual){
		inicio = trocar_nos(inicio, atual, escolhido);
		escolhido = atual;
		if(comp(atual->esq, escolhido)){
			escolhido = atual->esq;
		}
		
		if(comp(atual->dir, escolhido)){
			escolhido = atual->dir;
		}
	}

	return inicio;
}


No* encontrar_ultimo(No* head){
	if(head == NULL){
		return head;
	}
	No* inicio = head;
	Item* fila = criar_item(inicio, 0);
	Item* fila_atual = fila;
	No* no_atual;

	while(fila_atual != NULL){
		no_atual = (No*)fila_atual->conteudo;
		if(no_atual->esq != NULL){
			fila = concat_item(fila, criar_item(no_atual->esq, 0));
		} 

		if(no_atual->dir != NULL){
			fila = concat_item(fila, criar_item(no_atual->dir, 0));
		}
		fila_atual = fila_atual->prox;
	}

	fila = apagar_lista(fila);
	return no_atual;
}


No* remover_heap(No* head){
	if(head == NULL){
		return head;
	}
	No* inicio = head;
	No* removido = inicio;

	// Encontra o ultimo elemento da heap
	No* ultimo = encontrar_ultimo(inicio);	
	No* pai_removido = NULL;

	// Troca ultimo elemento com a raiz
	inicio = trocar_nos(inicio, inicio, ultimo);

	// Corta ligações entre removido e a arvore
	pai_removido = encontrar_pai(inicio, removido);
	if(pai_removido != NULL){
		pai_removido->esq = pai_removido->esq == removido ? NULL : pai_removido->esq;
		pai_removido->dir = pai_removido->dir == removido ? NULL : pai_removido->dir;
	}
	// Apaga o removido
	if(inicio == removido){
		apagar_arvore(removido);
		return NULL;
	}
	apagar_arvore(removido);

	// Heapfy (praying)
	inicio = heapfy(inicio, minimo);

	return inicio;
}


void apagar_arvore(No* raiz){
	if(raiz == NULL){
		return;
	}
	apagar_arvore(raiz->esq);
	apagar_arvore(raiz->dir);
	free(raiz);
}
