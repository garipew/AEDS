#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>


Vertice* adicionar_aresta(Vertice* head, int origem, int destino, int peso){
	if(head == NULL){
		return head;
	}
	Vertice* v_origem = head;
	while(v_origem->idx != origem){
		v_origem = v_origem->prox;
		if(v_origem == NULL){
			v_origem = criar_item(NULL, origem);
			head = concat_item(head, v_origem);
			break;
		}
	}	
	Vertice* v_destino = head;
	while(v_destino->idx != destino){
		v_destino = v_destino->prox;
		if(v_destino == NULL){
			v_destino = criar_item(NULL, destino);
			head = concat_item(head, v_destino);
			break;
		}
	}	
	v_origem->conteudo = (void*)concat_item((Aresta*)v_origem->conteudo, criar_item(v_destino, peso));
	return head;
}


Vertice* remover_aresta(Vertice* head, int origem, int destino){
	// Percorre vertices em busca da origem
	if(head == NULL){
		return head;
	}
	Vertice* v_origem = head;
	while(v_origem->idx != origem){
		if(v_origem == NULL){
			return head;
		}
		v_origem = v_origem->prox;
	}	

	// Percorre adjacentes da origem em busca do destino
	if(v_origem->conteudo == NULL){
		return head;
	}
	Aresta* adjacentes = (Aresta*)v_origem->conteudo;
	while(((Vertice*)adjacentes->prox->conteudo)->idx != destino){
		adjacentes = adjacentes->prox;
		if(adjacentes == NULL){
			return head;
		}
	}
	// Remove a aresta que liga origem à destino (apenas na adjacencia de origem)
	Aresta* removida = adjacentes->prox;
	adjacentes->prox = adjacentes->prox->prox;
	free(removida);
	
	return head;
}


void escrever_grafo(Vertice* head){
	Vertice* atual = head;
	Aresta* adjacente;
	while(atual != NULL){
		printf("%d: ", atual->idx);
		adjacente = (Aresta*)atual->conteudo;
		while(adjacente != NULL){
			printf("%d %d | ", ((Vertice*)adjacente->conteudo)->idx, adjacente->idx);
			adjacente = adjacente->prox;
		}
		printf("\n");
		atual = atual->prox;
	}
}


Vertice* apagar_grafo(Vertice* head){
	Vertice* atual = head;
	printf("Apagando listas de adjacencia...\n");
	while(atual != NULL){
		atual->conteudo = (void*)apagar_lista((Item*)atual->conteudo);
		atual = atual->prox;
	}
	printf("Apagando vertices...\n");
	head = apagar_lista((Item*)head);
	return NULL;
}
