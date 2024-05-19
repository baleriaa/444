#include "inode.h"
#include "block.h"
#include "free.h"
#include <stdio.h>

static struct inode incore[MAX_SYS_OPEN_FILES] = {0};

int ialloc(void) {
  unsigned char block[BLOCK_SIZE];
  
  bread(1, block);
  int free_inode = find_free(block);

  if (free_inode == -1) {
    return -1;
  }

  set_free(block, free_inode, 1);
  bwrite(1, block);

  return free_inode;
}

struct inode *incore_find_free(void) {
  for (int i = 0; i < MAX_SYS_OPEN_FILES; i++) {
    if (incore[i].ref_count == 0) {
      return &incore[i];
    }
  } 
  return NULL;
}


struct inode *incore_find(unsigned int inode_num) {
  for (int i = 0; i < MAX_SYS_OPEN_FILES; i++) {
   if (incore[i].ref_count != 0 && incore[i].inode_num == inode_num) {
      return &incore[i];
    }
  }
  return NULL;
 
}

void incore_free_all(void) {
  for (int i = 0; i < MAX_SYS_OPEN_FILES; i++) {
    incore[i].ref_count = 0;
  }
}