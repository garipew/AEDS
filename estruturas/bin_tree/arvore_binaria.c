#include "arvore_binaria.h"
#include "../../algoritmos/linked_list/sort.h"
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


/*
No* encontrar_ultimo(No* head, Item* fila, int salvar){
	if(head == NULL){
		return head;
	}
	No* inicio = head;
	concat_item(fila, criar_item(inicio, inicio->idx));
	Item* fila_atual = fila->prox;
	No* no_atual;

	while(fila_atual != NULL){
		no_atual = (No*)fila_atual->conteudo;
		if(no_atual->esq != NULL){
			concat_item(fila, criar_item(no_atual->esq, no_atual->esq->idx));
		} 

		if(no_atual->dir != NULL){
			concat_item(fila, criar_item(no_atual->dir, no_atual->dir->idx));
		}
		fila_atual = fila_atual->prox;
	}

	if(!salvar){
		fila = apagar_lista(fila);
	}
	return no_atual;
}
*/


No* encontrar_pai(Item* head, No* no){
	if(head == NULL){
		return NULL;
	}
	if(head->conteudo == no){
		return NULL;
	}
	Item* atual = head;
	No* no_atual;
	while(atual != NULL){
		no_atual = atual->conteudo;
		if(no_atual == NULL){
			atual = atual->prox;
			continue;
		}
		if(no_atual->esq == no || no_atual->dir == no){
			return no_atual;	
		}
		atual = atual->prox;
	}
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


/*
Item* trocar_pai(Item* head, No* pai, No* filho){
	if(head == NULL || pai == NULL || filho == NULL){
		return head;	
	}

	Item* inicio = head;
	No* pai_anterior = encontrar_pai(inicio, pai);
	No* pai_esq = pai->esq;
	No* pai_dir = pai->dir;

	if(pai_anterior != NULL){
		pai_anterior->esq = pai_anterior->esq == pai ? filho : pai_anterior->esq;
		pai_anterior->dir = pai_anterior->dir == pai ? filho : pai_anterior->dir;
	} 

	pai->esq = filho->esq;
	pai->dir = filho->dir;
	filho->esq = pai_esq == filho ? pai : pai_esq;
	filho->dir = pai_dir == filho ? pai : pai_dir;

	inicio = trocar_itens(inicio, encontrar_No(inicio, pai), encontrar_No(inicio, filho));
	return inicio;
}



No* inserir_heap(No* head, No* novo, int(*comp)(No*, No*)){
	No* inicio = inserir_nivel(head, novo);
	Item* pilha = criar_item(NULL, -1);
	No* atual = encontrar_ultimo(head, pilha, 1);

	pilha = remover_primeiro(pilha);

	while(pilha != NULL){
		atual = (No*)remover_ultimo(pilha);
		if(atual == NULL){
			break;
		}
		inicio = heapfy(inicio, atual, comp);
	}

	return inicio;
}
*/


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


Item* encontrar_No(Lista* head, No* buscado){
	Item* atual = head->primeiro->prox;
	No* no_atual;
	while(atual != NULL){
		no_atual = (No*)atual->conteudo;	
		if(no_atual == buscado){
			return atual;
		}
		atual = atual->prox;
	}
	return NULL;
}


No* encontrar_pai_lista(Lista* head, Item* no){
	Item* atual = no;
	No* no_atual;
	while(atual != head->primeiro){
		no_atual = atual->conteudo;
		if(no_atual->esq == no->conteudo || no_atual->dir == no->conteudo){
			return no_atual;
		}
		atual = atual->ant;
	}
	return NULL;
}


void trocar_nos(Lista* head, No* a, No* b){
	if(head == NULL || a == NULL || b == NULL){
		return;	
	}

	Item* item_a = encontrar_No(head, a);
	Item* item_b = encontrar_No(head, b);

	No* a_anterior = encontrar_pai_lista(head, item_a);
	No* b_anterior = encontrar_pai_lista(head, item_b);

	No* a_esq = a->esq;
	No* a_dir = a->dir;

	if(a_anterior != NULL){
		a_anterior->esq = a_anterior->esq == a ? b : a_anterior->esq;
		a_anterior->dir = a_anterior->dir == a ? b : a_anterior->dir;
	} 

	if(b_anterior != NULL){
		b_anterior->esq = b_anterior->esq == b ? a : b_anterior->esq;
		b_anterior->dir = b_anterior->dir == b ? a : b_anterior->dir;
	}

	a->esq = b->esq == a ? b : b->esq;
	a->dir = b->dir == a ? b : b->dir;
	b->esq = a_esq == b ? a : a_esq;
	b->dir = a_dir == b ? a : a_dir;
	
	trocar_itens(head, item_a, item_b);
}


void full_heapfy(Lista* head, int(*compara)(No*, No*)){
	Lista* pilha = criar_copia(head);
	No* atual;
	while(pilha->primeiro!=pilha->ultimo){
		atual = remover_ultimo(pilha);
		if(atual == NULL){
			break;
		}
		heapfy(head, atual, compara);
	}
	apagar_lista(pilha);
}


void heapfy(Lista* head, No* atual, int(*comp)(No*, No*)){
	if(head == NULL || atual == NULL){
		return;
	}

	No* escolhido = atual;
	if(atual->esq == NULL && atual->dir == NULL){
		return;
	}

	if(comp(atual->esq, escolhido)){
		escolhido = atual->esq;
	}
		
	if(comp(atual->dir, escolhido)){
		escolhido = atual->dir;
	}

	if(escolhido != atual){
		trocar_nos(head, atual, escolhido);
		heapfy(head, atual, comp);
	}

}


void remover_heap(Lista* head, int(*compara)(No*, No*)){
	if(head == NULL){
		return;
	}

	Item* r = head->primeiro->prox;
	No* removido = r->conteudo;
	No* atual = NULL;

	// Encontra o ultimo elemento da heap
	No* ultimo = head->ultimo->conteudo;
	No* pai_removido = NULL;

	// Troca ultimo elemento com a raiz
	trocar_nos(head, removido, ultimo);

	// Corta ligações entre removido e a arvore
	pai_removido = encontrar_pai_lista(head, r);
	if(pai_removido != NULL){
		pai_removido->esq = pai_removido->esq == removido ? NULL : pai_removido->esq;
		pai_removido->dir = pai_removido->dir == removido ? NULL : pai_removido->dir;
	}
	// Apaga o removido
	if(head->primeiro->prox->conteudo == removido){
		apagar_arvore(removido);
		remover_ultimo(head);
		return;
	}
	apagar_arvore(removido);
	remover_ultimo(head);
	
	// Heapfy (praying)
	heapfy(head, head->primeiro->prox->conteudo, compara);

}


void apagar_arvore(No* raiz){
	if(raiz == NULL){
		return;
	}
	apagar_arvore(raiz->esq);
	apagar_arvore(raiz->dir);
	free(raiz);
}
