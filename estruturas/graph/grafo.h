#ifndef GRAPH
#define GRAPH

#include "../linked_list/lista.h"

/* Vertice {
 *	struct* item conteudo; lista de arestas
 *	int idx; idx do vertice
 *	struct* item prox; grafo alcança todos os vertices
 *	}
 */ 

/* Aresta {
 *	struct* item conteudo; vertice destino
 *	int idx; peso
 *	struct* item prox; prosseguir na lista de arestas
 *	}
 */ 

typedef Item Vertice;
typedef Item Aresta;


Vertice* adicionar_aresta(Vertice*, int, int, int);
Vertice* remover_aresta(Vertice*, int, int); 
Vertice* remover_vertice(Vertice*, int);
Vertice* criar_vertice(Aresta*, int);
Vertice* concat_vertice(Vertice*, Vertice*);
void escrever_grafo(Vertice*);
Vertice* apagar_grafo(Vertice*);
#endif
