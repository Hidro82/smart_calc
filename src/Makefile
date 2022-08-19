CC = gcc
#ERRFLAGS = -Wall -Werror -Wextra
#ASAN = -fsanitize=address
FLAGC = -c
FLAGO = -o

all: clean test

test:
	$(CC) $(ASAN) $(ERRFLAGS) *.c -lm `pkg-config --cflags --libs gtk+-3.0`
	./a.out

clean:
	rm -rf a.out *.o *.a