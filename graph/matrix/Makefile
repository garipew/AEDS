CC=gcc
CFLAGS=-Wall

dijkstra: grafo.o heap.o main.c
	$(CC) $(CFLAGS) -o dijkstra grafo.o heap.o main.c

grafo.o: grafo.c grafo.h
	$(CC) $(CFLAGS) -c grafo.c

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

clean:
	rm -rf *.o dijkstra
