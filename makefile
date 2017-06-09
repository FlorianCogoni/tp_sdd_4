all : tp4

tp4 : hash.o main.o
	gcc -Wall -Wextra -ansi -pedantic -o tp4 hash.o main.o

hash.o : hash.c hash.h
	gcc -Wall -Wextra -ansi -pedantic -o hash.o -c hash.c

main.o : main.c hash.h
	gcc -Wall -Wextra -ansi -pedantic -o main.o -c main.c

clean :
	rm -rf *.o

mrproper : clean
	rm -rf tp4
