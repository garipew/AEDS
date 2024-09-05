#include "lista.h"
#include "../../algoritmos/linked_list/sort.h"
#include <stdlib.h>


int main(){
	Item* head = criar_item(NULL, 10);
	for(int i = 9; i > 0; i--){
		head = concat_item(head, criar_item(NULL, i));
	}

	escrever_lista(head);
	head = heap_sort(head, minimo);
	escrever_lista(head);
	head = apagar_lista(head);
	return 0;
}
