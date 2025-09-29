dijkstra: grafo.o heap.o main.c
	gcc -o dijkstra grafo.o heap.o main.c

grafo.o: grafo.c grafo.h
	gcc -c grafo.c

heap.o: heap.c heap.h
	gcc -c heap.c

clean:
	rm -rf *.o dijkstra
