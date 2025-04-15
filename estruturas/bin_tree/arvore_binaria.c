#include "arvore_binaria.h"
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


Item* inserir_nivel(Lista* head, No* novo){
	if(head == NULL){
		return NULL;
	}
	Item* item_atual = head->primeiro->prox;
	if(item_atual == NULL){
		concat_item(head, criar_item(novo, novo->idx));
		return head->primeiro->prox;
	}
	No* no_atual;
	while(item_atual != NULL){
		no_atual = item_atual->conteudo;
		if(no_atual->esq == NULL){
			no_atual->esq = novo;	
			concat_item(head, criar_item(novo, novo->idx));
			return item_atual;
		}
		if(no_atual->dir == NULL){
			no_atual->dir = novo;	
			concat_item(head, criar_item(novo, novo->idx));
			return item_atual;
		}
		item_atual = item_atual->prox;
	}
	return NULL;
}


No* inserir_bst(No* no, No* raiz){	
	if(no == NULL){
		return raiz;
	}
	if(raiz == NULL){
		return no;
	}

	if(no->idx == raiz->idx){
		return raiz;
	}

	if(no->idx < raiz->idx){
		raiz->esq = inserir_bst(no, raiz->esq);
		return raiz;
	}

	if(no->idx > raiz->idx){
		raiz->dir = inserir_bst(no, raiz->dir);
		return raiz;
	}
}


int minimo(No* a, No* b){
	return (a != NULL && b != NULL) ? a->idx < b->idx : 0;
}


int maximo(No* a, No* b){
	return (a != NULL && b != NULL) ? a->idx > b->idx : 0;
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


int contar_nos(No* raiz){
	if(raiz == NULL){
		return 0;
	}
	int nos = 1;
	nos+=contar_nos(raiz->esq);
	nos+=contar_nos(raiz->dir);
	return nos;
}


No* juntar_nos(No* a, No* b){
	if(a == NULL){
		return b;
	} else if(b == NULL){
		return a;
	} 
	No* raiz = criar_no(NULL, a->idx+b->idx);
	raiz->esq = a;
	raiz->dir = b;
	return raiz;
}


void apagar_arvore(No* raiz){
	if(raiz == NULL){
		return;
	}
	apagar_arvore(raiz->esq);
	apagar_arvore(raiz->dir);
	free(raiz);
	raiz = NULL;
}


No* bin_search(No* raiz, int searched){
	if(raiz == NULL){
		return NULL;
	}
	if(searched < raiz->idx){
		return bin_search(raiz->esq, searched);
	}	
	if(searched == raiz->idx){
		return raiz;
	}	
	if(searched > raiz->idx){
		return bin_search(raiz->dir, searched);
	}	
}
