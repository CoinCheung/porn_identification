CC = gcc
FLAGS = -c -g -Wall
LIBS = -lpthread
_OBJs = cserver.o imgpro.o

ODIR = ./build
OBJs = $(patsubst %.o,$(ODIR)/%.o,$(_OBJs))


cserver: $(OBJs)
	$(CC) $^ $(LIBS) -o $@

$(ODIR)/%.o: %.c %.h
	$(CC) $(FLAGS) $< -o $@



clean:
	rm *.o $(ODIR)/*.o cserver test_c

test: test_c.c
	$(CC) -g -Wall -ansi test_c.c -o test_c
