all : client.out


VERSION = 0.3

CFLAGS = -Wall

client.out: client.o
	gcc -o client.out client.o

client.o: client.c client.h
	gcc $(CFLAGS) -o client.o -c client.c

clean :
	rm  client.o client.out
