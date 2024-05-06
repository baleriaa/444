CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean

all: testfs

testfs: testfs.o image.o block.o
	$(CC) $(CFLAGS) -o $@ $^

testfs.o: testfs.c image.h block.h
	$(CC) $(CFLAGS) -c $< -o $@

image.o: image.c image.h
	$(CC) $(CFLAGS) -c $< -o $@

block.o: block.c block.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o testfs