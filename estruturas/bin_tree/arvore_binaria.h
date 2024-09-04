#ifndef BIN_TREE
#define BIN_TREE

typedef struct no {
	int idx;
	struct no* esq;
	struct no* dir;
} No;

No* criar_no(int);
No* inserir_nivel(No*, No*, No*);
No* inserir_bst(No*, No*);
int minimo(No*, No*);
No* inserir_heap(No*, No*, int(*)(No*, No*));
No* remover_heap(No*);
void escrever_arvore(No*);
void apagar_arvore(No*);
#endif
