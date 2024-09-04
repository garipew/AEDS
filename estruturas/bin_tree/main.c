#include "arvore_binaria.h"
#include "../../algoritmos/bin_tree/invert.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	No* raiz = inserir_heap(NULL, criar_no(10), minimo);

	for(int i = 9; i > 0; i--){
		raiz = inserir_heap(raiz, criar_no(i), minimo);
	}

	escrever_arvore(raiz);

	printf("Removendo raiz...\n");
	raiz = remover_heap(raiz);
	escrever_arvore(raiz);

	printf("Removendo raiz...\n");
	raiz = remover_heap(raiz);
	escrever_arvore(raiz);

	apagar_arvore(raiz);

	return 0;
}
