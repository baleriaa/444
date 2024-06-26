#include "ctest.h"
#include "image.h"
#include "block.h"
#include <stdio.h>
#include <string.h>
#include "free.h"
#include "inode.h"


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
  unsigned char block[50] = {0};  

  set_free(block, 5, 1); 
  CTEST_ASSERT(find_free(block) == 0, "First free bit shoulf be 0 after setting bit 5");

  set_free(block, 0, 1);
  CTEST_ASSERT(find_free(block) == 1, "First free bit should be 1 after setting bit 0");
}

void test_alloc(void) {
  unsigned char block[BLOCK_SIZE] = {0};
  bwrite(2, block);
  int alloc_block = alloc();
  CTEST_ASSERT(alloc_block != -1, "Ensures that block is allocated");
}

void test_ialloc(void) {
  incore_free_all();
  unsigned char block[BLOCK_SIZE] = {0};

  bwrite(1, block);
  printf("test_ialloc: Calling ialloc()\n");

  struct inode *in = ialloc();
  printf("test_ialloc: ialloc() returned %p\n", (void *)in);

  CTEST_ASSERT(in != NULL, "Ensures that inode is allocated");
  CTEST_ASSERT(in->size == 0, "Ensures that size is set to 0");
  CTEST_ASSERT(in->owner_id == 0, "Ensures that owner_id is set to 0");
  CTEST_ASSERT(in->permissions == 0, "Ensures that permissions is set to 0");
  CTEST_ASSERT(in->flags == 0, "Ensures that flags is set to 0");
}

void test_incore_find_free(void) {
  struct inode *inode = incore_find_free();
  CTEST_ASSERT(inode != NULL, "Ensures that incore_find_free returns a free inode");
}

void test_incore_find(void) {
  struct inode *inode = incore_find_free();
  inode->ref_count = 1;
  inode->inode_num = 1;
  struct inode *found_inode = incore_find(1);
  CTEST_ASSERT(found_inode != NULL, "Ensures that incore_find returns an inode");
}

void test_incore_free_all(void) {
  struct inode *inode = incore_find_free();
  inode->ref_count = 1;
  incore_free_all();
  CTEST_ASSERT(inode->ref_count == 0, "Ensures that incore_free_all sets ref_count to 0");
}

void test_read_and_write_inode(void) {
  struct inode *inode = incore_find_free();
  inode->size = 10;
  inode->owner_id = 1;
  inode->permissions = 1;
  inode->flags = 1;
  inode->link_count = 1;
  inode->block_ptr[0] = 1;
  inode->ref_count = 1;
  inode->inode_num = 1;

  write_inode(inode);

  struct inode *read_inode = incore_find(1);
  CTEST_ASSERT(read_inode->size == 10, "Ensures that size is written and read correctly");
  CTEST_ASSERT(read_inode->owner_id == 1, "Ensures that owner_id is written and read correctly");
  CTEST_ASSERT(read_inode->permissions == 1, "Ensures that permissions is written and read correctly");
  CTEST_ASSERT(read_inode->flags == 1, "Ensures that flags is written and read correctly");
  CTEST_ASSERT(read_inode->link_count == 1, "Ensures that link_count is written and read correctly");
  CTEST_ASSERT(read_inode->block_ptr[0] == 1, "Ensures that block_ptr is written and read correctly");
  CTEST_ASSERT(read_inode->ref_count == 1, "Ensures that ref_count is written and read correctly");
  CTEST_ASSERT(read_inode->inode_num == 1, "Ensures that inode_num is written and read correctly");
}

void test_iget(void) {
  incore_free_all();
  struct inode *inode = iget(1);
  CTEST_ASSERT(inode != NULL, "Ensures that iget returns an inode.");
  CTEST_ASSERT(inode->inode_num == 1, "Ensures that iget returns the correct inode.");
  CTEST_ASSERT(inode->ref_count == 1, "Ensures that iget sets ref_count to 1.");
}

void test_iput(void) {
  incore_free_all();
  struct inode *inode = iget(1);
  iput(inode);
  CTEST_ASSERT(inode->ref_count == 0, "Ensures that iput sets ref_count to 0 when decremented.");
}

int main(void) {
  CTEST_VERBOSE(1);

  test_image_open_and_close();
  test_bread_and_bwrite();
  test_set_and_free_find_free();
  test_ialloc();
  test_alloc();
  test_incore_find_free();
  test_incore_find();
  test_incore_free_all();
  test_read_and_write_inode();
  test_iget();
  test_iput();

  CTEST_RESULTS();
  
  CTEST_EXIT();

}

#else

int main(void) {
  printf("Running normally!\n");
}

#endif