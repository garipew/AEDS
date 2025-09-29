#include "grafo.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define panic(msg) \
	fprintf(stderr, msg); \
	exit(1)

#define get_block_size(struct_ptr, buff_type, n) \
	sizeof(*struct_ptr)+((n)*sizeof(buff_type))+_Alignof(buff_type)-1

#define get_aligned_offset(struct_ptr, buff_type) \
	((sizeof(*struct_ptr)+_Alignof(buff_type)-1) & ~(_Alignof(buff_type)-1))

Grafo* criar_grafo(int vertices){
	Grafo* g;
	g = calloc(1, get_block_size(g, int, vertices*vertices));
	if(!g){
		panic("calloc fail");
	}
	g->vertices = vertices;
	g->adj = (void*)((char*)g+get_aligned_offset(g, int));
	return g;
}

void inserir_aresta(Grafo* g, int dst, int src, int peso){
	if(dst >= g->vertices || src >= g->vertices){
		return;
	}
	g->adj[src + dst*g->vertices] = peso;
	g->arestas++;
}

void inserir_aresta_nd(Grafo* g, int dst, int src, int peso){
	if(dst >= g->vertices || src >= g->vertices){
		return;
	}
	g->adj[src + dst*g->vertices] = peso;
	g->adj[dst+src*g->vertices] = peso;
	g->arestas++;
}

void apagar_aresta(Grafo* g, int dst, int src){
	g->adj[src + dst*g->vertices] = 0;
	g->arestas = g->arestas > 0 ? --g->arestas : 0;
}

void apagar_aresta_nd(Grafo* g, int dst, int src){
	g->adj[src + dst*g->vertices] = 0;
	g->adj[dst+src*g->vertices] = 0;
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
			printf("%d ", g->adj[i + j*g->vertices]);
		}
		printf("\n");
	}
}

void apagar_grafo(Grafo* g){
	if(g){
		free(g);
	}
}

int is_adjacent(Grafo* g, int dst, int src){
	return g->adj[src + dst*g->vertices] > 0;
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
				inserir_heap(q, i, dist[shortest.vertex]+g->adj[shortest.vertex+i*g->vertices]);
			}
		}
	}
	apagar_heap(q);
	return dist;
}
