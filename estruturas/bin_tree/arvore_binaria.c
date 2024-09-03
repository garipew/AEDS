#include "arvore_binaria.h"
#include <stdlib.h>
#include <stdio.h>


No* novo_no(int idx){
	No* no = malloc(sizeof(*no));
	no->idx = idx;
	no->esq = NULL;
	no->dir = NULL;
	
	return no;
}


No* inserir_no(No* no, No* raiz){	
	if(no->idx == raiz->idx){
		return raiz;
	}
	if(no->idx < raiz->idx){
		if(raiz->esq == NULL){
			raiz->esq = no;
			return raiz;
		}
		return inserir_no(no, raiz->esq);
	}
	if(no->idx > raiz->idx){
		if(raiz->dir == NULL){
			raiz->dir = no;
			return raiz;
		} 
		return inserir_no(no, raiz->dir);
	}
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


void apagar_arvore(No* raiz){
	if(raiz == NULL){
		return;
	}
	apagar_arvore(raiz->esq);
	apagar_arvore(raiz->dir);
	free(raiz);
}
