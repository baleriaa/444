#include "ctest.h"
#include "image.h"
#include "block.h"
#include <stdio.h>
#include <string.h>

#ifdef CTEST_ENABLE

void test_image_open_and_close(void) {
  int fd = image_open("test.md", 0);
  CTEST_ASSERT(fd != -1, "open file with no truncate");

  CTEST_ASSERT(image_close() == 0, "close file");

  fd = image_open("test.md", 1);
  CTEST_ASSERT(fd != -1, "open file with truncate");
}


void test_bread_and_bwrite(void) {
  char *test_file = "test.md";
  char *test_text = "test";
  unsigned char write_block[BLOCK_SIZE] = {0};
  unsigned char read_block[BLOCK_SIZE] = {0};
  size_t length = strlen(test_text) + 1;

  memcpy(write_block, test_text, length);
  
  image_open(test_file, 1);
  bwrite(0, write_block);
  bread(0, read_block);

  CTEST_ASSERT(memcmp(write_block, read_block, BLOCK_SIZE) == 0, "testing equivalence of read and write blocks");
}

void test_set_and_free_find_free(void) {
  // TODO
  // 
}

void test_ialloc_and_alloc(void) {
  // TODO
  // 
}

int main(void) {
  CTEST_VERBOSE(1);

  test_image_open_and_close();
  test_bread_and_bwrite();
  test_set_and_free_find_free();
  test_ialloc_and_alloc();

  CTEST_RESULTS();
  
  CTEST_EXIT();

}

#else

int main(void) {
  printf("Running normally!\n");
}

#endif