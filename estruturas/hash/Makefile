hash: hash.o lista.o main.c
	gcc -o hash main.c hash.o lista.o

hash.o: hash.c hash.h
	gcc -c hash.c

lista.o: ../linked_list/lista.c ../linked_list/lista.h
	gcc -c ../linked_list/lista.c

clean:
	rm -rf *.o hash
