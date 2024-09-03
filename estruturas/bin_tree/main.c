#include "arvore_binaria.h"
#include "../../../algoritmos/bin_tree/C/invert.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	No* raiz = novo_no(6);

	for(int i = 0; i < 10; i++){
		inserir_no(novo_no(i), raiz);
	}

	escrever_arvore(raiz);
	inverter_arvore(raiz);
	printf("\nInvertendo arvore...\n\n");
	escrever_arvore(raiz);
	inverter_arvore(raiz);
	printf("\nRevertendo arvore...\n\n");
	escrever_arvore(raiz);
	apagar_arvore(raiz);

	return 0;
}
