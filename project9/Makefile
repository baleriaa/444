.PHONY: all test clean pristine

CC = gcc
CFLAGS = -Wall -Wextra -Werror
TEST_FLAGS = -DCTEST_ENABLE

all: testfs

testfs: testfs.o image.o block.o inode.o free.o pack.o mkfs.o dir.o ls.o namei.o
	$(CC) $(CFLAGS) $(TEST_FLAGS) -o $@ $^

test: testfs
	./testfs

%.o: %.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c $< -o $@

clean:
	rm -f *.o testfs

pristine: clean
	rm -f *.a