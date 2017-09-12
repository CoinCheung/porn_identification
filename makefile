CC = clang
OBJs = ./build/cserver.o
FLAGS = -c -g -Wall

cserver: cserver.o
	$(CC) $(OBJs) -o cserver

cserver.o: cserver.c
	$(CC) $(FLAGS) cserver.c -o ./build/cserver.o

clean:
	rm ./build/*.o cserver test_run

test: test_c.c
	$(CC) -g -Wall test_c.c -o test_run
