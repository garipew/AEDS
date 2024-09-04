#include "lista.h"
#include "../../algoritmos/linked_list/sort.h"
#include <stdlib.h>


int main(){
	Item* head = criar_item(NULL, 10);
	Item* ultimo;
	for(int i = 9; i > 0; i--){
		ultimo = criar_item(NULL, i);
		head = concat_item(head, ultimo);
	}

	escrever_lista(head);
	head = insertion_sort(head, comparar);
	head = apagar_lista(head);
	return 0;
}
