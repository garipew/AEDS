comp: main.c compression.o sort.o lista.o heap.o arvore_binaria.o
	gcc -o comp main.c compression.o sort.o lista.o heap.o arvore_binaria.o

debug: main.c compdebug.o sort.o lista.o heap.o arvore_binaria.o
	gcc -g3 -o comp main.c compression.o sort.o lista.o heap.o arvore_binaria.o

compression.o: compression.c compression.h
	gcc -c compression.c

compdebug.o: compression.c compression.h
	gcc -g3 -c compression.c

sort.o: ../linked_list/sort.c ../linked_list/sort.h
	gcc -c ../linked_list/sort.c

lista.o: ../../estruturas/linked_list/lista.c ../../estruturas/linked_list/lista.h
	gcc -c ../../estruturas/linked_list/lista.c

heap.o: ../../estruturas/bin_tree/heap.c ../../estruturas/bin_tree/heap.h
	gcc -c ../../estruturas/bin_tree/heap.c

arvore_binaria.o: ../../estruturas/bin_tree/arvore_binaria.c ../../estruturas/bin_tree/arvore_binaria.h
	gcc -c ../../estruturas/bin_tree/arvore_binaria.c

clean:
	rm -rf *.o comp
