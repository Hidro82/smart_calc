CC = gcc
# ERRFLAGS = -Wall -Werror -Wextra
ASAN = -fsanitize=address
FLAGC = -c
FLAGO = -o

all: clean test

test:
	$(CC) $(ASAN) $(ERRFLAGS) *.c -lm
	./a.out

clean:
	rm -rf a.out *.o *.a