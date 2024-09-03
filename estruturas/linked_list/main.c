#include "lista.h"
#include <stdlib.h>


int main(){
	Item* head = criar_item(NULL);
	for(int i = 0; i < 10; i++){
		concat_item(head, criar_item(NULL));	
	}

	head = apagar_lista(head);
	return 0;
}
