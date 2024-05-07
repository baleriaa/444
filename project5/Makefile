.PHONY: all test clean pristine

all: testfs

libvvsfs.a: testfs.o image.o block.o
	ar rcs $@ $^

testfs: testfs.o image.o block.o libvvsfs.a
	gcc -Wall -Wextra -Werror -o $@ testfs.o image.o block.o -L. -lvvsfs

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

test: testfs
	./testfs

clean:
	rm -f *.o

pristine: clean
	rm -f testfs libvvsfs.a
