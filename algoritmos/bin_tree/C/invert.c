#include "invert.h"
#include <stdlib.h>


void inverter_lados(No* raiz){
	if(raiz == NULL){
		return;
	}
	
	No* esq_anterior = raiz->esq;
	raiz->esq = raiz->dir;
	raiz->dir = esq_anterior;
}


void inverter_arvore(No* raiz){
	if(raiz == NULL){
		return;
	}
	inverter_lados(raiz);	
	inverter_arvore(raiz->esq);
	inverter_arvore(raiz->dir);
}
