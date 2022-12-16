all:
	gcc -Wall -c common.c
	gcc -Wall -lpthread equipment.c common.o -o equipment
	gcc -Wall -lpthread server.c common.o -o server

clean:
	rm common.o equipment server
