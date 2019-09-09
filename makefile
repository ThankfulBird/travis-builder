CC=gcc
CFLAGS = -I. -Wall -ftest-coverage -fprofile-arcs
DEPS   = ./lib/travis.h
OBJ    = ./test/travis.test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test-library.out: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lm -lncurses -Os

clean :
	rm  *.o  *.asm  *.lst *.sym *.rel *.s *.gc* -f *.info