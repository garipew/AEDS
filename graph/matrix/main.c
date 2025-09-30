#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

Grafo* read_input();

int main(int argc, char** argv){
	srand(time(NULL));
	Grafo* g = read_input();
//	print_grafo(g);
	int source = rand()%g->vertices;
	if(argc > 1){
		source = atoi(argv[1]);
	}
	int* dist = dijkstra(g, source);

	printf("As distancias, partindo de %d:\n", source);
	for(int i = 0; i < g->vertices; i++){
		printf("%d ", dist[i]);
	}
	printf("\n");
	free(dist);
	free(g);
	return 0;
}

Grafo* read_input(){
	char buffer[200];
	int v1, v2, w;
	fgets(buffer, 200, stdin);
	int vertices, arestas;
	sscanf(buffer, "%d %d", &vertices, &arestas);
//	printf("Criando um grafo com %d v e %d a\n", vertices, arestas);
	Grafo* g = criar_grafo(vertices);
	for(int i = 0; i < arestas; i++){
		if(!fgets(buffer, 200, stdin)){
			break;
		}
		sscanf(buffer, "%d %d %d", &v1, &v2, &w);
		inserir_aresta_nd(g, v1, v2, w);
	}	
//	printf("Grafo criado\n");
	return g;
}
