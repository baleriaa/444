#include "inode.h"
#include "block.h"
#include "free.h"

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

