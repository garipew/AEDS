#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo{
	int vertices;
	int arestas;
	int* adj;
}	Grafo;

Grafo* criar_grafo(int);
void inserir_aresta(Grafo*, int, int, int);
void inserir_aresta_nd(Grafo*, int, int, int);
void apagar_grafo(Grafo*);
void print_grafo(Grafo*);
void apagar_aresta(Grafo*, int, int);
void apagar_aresta_nd(Grafo*, int, int);
int* dijkstra(Grafo*, int);
#endif
