#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	Vertice* head = criar_item(NULL, 0);

	for(int i = 1; i < 10; i++){
		head = concat_item(head, criar_item(NULL, i));	
	}

	head = adicionar_aresta(head, 0, 3, 1);
	head = adicionar_aresta(head, 9, 6, 4);
	head = adicionar_aresta(head, 9, 5, 4);
	head = adicionar_aresta(head, 10, 5, 4);
	head = adicionar_aresta(head, 30, 35, 4);
	escrever_grafo(head);
	printf("\nApagando...\n\n");
	head = apagar_grafo(head);

	return 0;
}
