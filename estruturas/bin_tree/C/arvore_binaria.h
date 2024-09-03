#ifndef BIN_TREE
#define BIN_TREE

typedef struct no {
	int idx;
	struct no* esq;
	struct no* dir;
} No;

No* novo_no(int);
No* inserir_no(No*, No*);
void escrever_arvore(No*);
void apagar_arvore(No*);
#endif
