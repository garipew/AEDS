#include "grafo.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define panic(msg) \
	fprintf(stderr, msg); \
	exit(1)

Grafo* criar_grafo(int vertices){
	Grafo* g = malloc(sizeof(*g));
	if(!g){
		panic("malloc fail\n");
	}
	g->adj = malloc(vertices * sizeof(*g->adj));
	for(int i = 0; i < vertices; i++){
		g->adj[i] = malloc(vertices * sizeof(*g->adj[i]));
		if(!g->adj[i]){
			panic("malloc fail\n");
		}
		memset(g->adj[i], 0, vertices*sizeof(*g->adj[i]));
	}
	g->vertices = vertices;
	g->arestas = 0;
	return g;
}

void inserir_aresta(Grafo* g, int dst, int src, int peso){
	if(dst >= g->vertices || src >= g->vertices){
		return;
	}
	g->adj[src][dst] = peso;
	g->arestas++;
}

void inserir_aresta_nd(Grafo* g, int dst, int src, int peso){
	if(dst >= g->vertices || src >= g->vertices){
		return;
	}
	g->adj[src][dst] = peso;
	g->adj[dst][src] = peso;
	g->arestas++;
}

void apagar_aresta(Grafo* g, int dst, int src){
	g->adj[src][dst] = 0;
	g->arestas = g->arestas > 0 ? --g->arestas : 0;
}

void apagar_aresta_nd(Grafo* g, int dst, int src){
	g->adj[src][dst] = 0;
	g->adj[dst][src] = 0;
	g->arestas = g->arestas > 0 ? --g->arestas : 0;
}

void print_grafo(Grafo* g){
	printf("  ");
	for(int k = 0; k < g->vertices; k++){
		printf("%d ", k);
	}
	printf("\n");
	for(int i = 0; i < g->vertices; i++){
		for(int j = 0; j < g->vertices; j++){
			if(j == 0){
				printf("%d ", i);
			}
			printf("%d ", g->adj[i][j]);
		}
		printf("\n");
	}
}

void apagar_grafo(Grafo* g){
	if(g){
		if(g->adj){
			for(int i = 0; i < g->vertices; i++){
				if(g->adj[i]){
					free(g->adj[i]);
				}
			}
			free(g->adj);
		}
		free(g);
	}
}

int is_adjacent(Grafo* g, int dst, int src){
	return g->adj[src][dst] > 0;
}

int* dijkstra(Grafo* g, int source){
	Heap* q = criar_heap((g->vertices*(g->vertices-1)));
	int *dist = malloc(sizeof(*dist)*(g->vertices));
	for(int i = 0; i < g->vertices; i++){
		dist[i] = INT_MAX;
	}
	Pair shortest = {0};
	dist[source] = 0;
	inserir_heap(q, source, 0);
	while(q->count > 0){
		shortest = remover_heap(q);
		if(shortest.vertex < 0){
			// heap vazia
			break;
		}
		if(dist[shortest.vertex] > shortest.distance){
			dist[shortest.vertex] = shortest.distance;
		}
		for(int i = 0; i < g->vertices; i++){
			// dist[i] == INT_MAX é uma otimização de memoria,
			// não necessaria para a lógica do algoritmo
			if(is_adjacent(g, i, shortest.vertex) && dist[i] == INT_MAX){
				inserir_heap(q, i, dist[shortest.vertex]+g->adj[shortest.vertex][i]);
			}
		}
	}
	apagar_heap(q);
	return dist;
}
