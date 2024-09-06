#include "arvore_binaria.h"
#include "../../algoritmos/bin_tree/invert.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	Item* inicio = criar_item(criar_no(NULL, 0), 0);
	Item* prox = inicio;


	for(int i = 9; i > 0; i--){
		prox  = inserir_nivel(prox, criar_no(NULL, i));
	}

	inicio = full_heapfy(inicio, minimo);
	escrever_lista(inicio);
	while(inicio != NULL){
		inicio = remover_heap(inicio, minimo);
		escrever_lista(inicio);
	}

	return 0;
}
