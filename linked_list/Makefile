order: lista.o arvore_binaria.o heap.o sort.o main.c
	gcc main.c lista.o arvore_binaria.o heap.o sort.o -o order

lista.o:
	gcc -c lista.c 

arvore_binaria.o:
	gcc -c ../bin_tree/arvore_binaria.c

heap.o:
	gcc -c ../bin_tree/heap.c

sort.o:
	gcc -c ../../algoritmos/linked_list/sort.c

clean:
	rm -rf *.o order
