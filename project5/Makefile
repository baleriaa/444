.PHONY: all test clean pristine

CC = gcc
CFLAGS = -Wall -Wextra -Werror
TEST_FLAGS = -DCTEST_ENABLE

all: testfs

testfs: testfs.o image.o block.o libvvsfs.a
	$(CC) $(CFLAGS) -o $@ $^ -L. -lvvsfs

libvvsfs.a: testfs.o image.o block.o
	ar rcs $@ $^

test: testfs_test
	./testfs_test

testfs_test: testfs_test.o image_test.o block_test.o libvvsfs_test.a
	$(CC) $(CFLAGS) $(TEST_FLAGS) -o $@ $^ -L. -lvvsfs_test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_test.o: %.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c $< -o $@

libvvsfs_test.a: testfs_test.o image_test.o block_test.o
	ar rcs $@ $^

clean:
	rm -f *.o

pristine:
	rm -f *.o *.a testfs testfs_test
