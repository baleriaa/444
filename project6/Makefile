.PHONY: all test clean pristine

CC = gcc
CFLAGS = -Wall -Wextra -Werror
TEST_FLAGS = -DCTEST_ENABLE

all: testfs

testfs: testfs.o image.o block.o inode.o free.o
	$(CC) $(CFLAGS) $(TEST_FLAGS) -o $@ $^
	./testfs

%.o: %.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c $< -o $@

clean:
	rm -f *.o testfs

pristine: clean
	rm -f *.a
