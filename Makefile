#Wersja kompilatora
CC=gcc

#Flagi kompilatora
CFLAGS= -c -Wall

all: prog

prog: main.o bstree.o command.o input.o invert.o list.o potega.o wyznacznik.o
	$(CC) -o prog main.o bstree.o command.o input.o invert.o list.o potega.o wyznacznik.o

bstree.o: bstree.c bstree.h
	$(CC) $(CFLAGS) -o bstree.o bstree.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -o command.o command.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -o input.o input.c

invert.o: invert.c invert.h
	$(CC) $(CFLAGS) -o invert.o invert.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -o list.o list.c

potega.o: potega.c potega.h
	$(CC) $(CFLAGS) -o potega.o potega.c

wyznacznik.o: wyznacznik.c wyznacznik.h
	$(CC) $(CFLAGS) -o  wyznacznik.o wyznacznik.c

main.o: main.c
	$(CC) $(CFLAGS) -o main.o main.c

clean:
	rm -rf *.o prog

