#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Hash* criar_hash(){
	Hash* h = malloc(sizeof(*h));
	if(!h){
		return h;
	}
	h->keys = malloc(sizeof(*h->keys)*HASH_LIMIT);
	if(!h->keys){
		free(h);
		h = NULL;
	}
	memset(h->keys, 0, sizeof(*h->keys)*HASH_LIMIT);
	return h;
}


unsigned hash(const char* str){
	unsigned hkey = 0;
	for(; *str ; str++){
		hkey = (((hkey<<5)-hkey)+*str)%HASH_LIMIT;
	}
	return hkey;
}


Item* lookup(Hash* h, const char* str){
	Lista* l = h->keys[hash(str)]; 
	if(!l){
		return NULL;
	}
	Item* np = l->primeiro->prox;
	for(; np != NULL; np = np->prox){
		if(strcmp(np->conteudo, str) == 0){
			return np;
		}
	} 
	return np;
}


int install(Hash* h, const char* str){
	if(*str == '\0'){
		return 0;
	}
	unsigned hashkey = hash(str);
	if(!h->keys[hashkey]){
		h->keys[hashkey] = criar_lista();
	}
	Item* exists;
	if(!(exists = lookup(h, str))){
		concat_item(h->keys[hashkey], criar_item((void*)str, 1));		
	} else{
		exists->idx++;
		return 0;
	}
	return 1;
}


void write_keys(Lista* head){
	if(head == NULL || head->primeiro == NULL){
		return;
	}
	Item* i = head->primeiro->prox;
	printf("{");
	while(i != NULL){
		printf("%s: %d%s", (char*)i->conteudo, i->idx, i->prox == NULL ? "}\n" : ", ");
		i = i->prox;
	}
}


void write_hash(Hash* h){
	if(!h || !h->keys){
		return;
	}
	for(int i = 0; i < HASH_LIMIT; i++){
		if(!h->keys[i]){
			continue;
		}
		write_keys(h->keys[i]);
	}
}


void cleanup(Hash* h){
	if(!h){
		return;
	}
	Lista** l = h->keys;
	if(l!=NULL){
		for(int i = 0; i < HASH_LIMIT; i++){
			if(!l[i]){
				continue;
			}
			apagar_lista(l[i]);	
		}
		free(l);
	}
	free(h);
}
