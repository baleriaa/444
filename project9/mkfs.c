#include "mkfs.h"
#include "inode.h"
#include "block.h"
#include "pack.h"
#include <string.h>
#include <stdio.h>

void mkfs(void) {
  unsigned char inode_bitmap[BLOCK_SIZE] = {0};
  bwrite(1, inode_bitmap);

  struct inode *root_inode = ialloc();

  unsigned int root_inode_num = root_inode->inode_num;

  int root_block = alloc();

  root_inode->flags = 2;
  root_inode->size = 64;
  root_inode->block_ptr[0] = root_block;

  unsigned char block[BLOCK_SIZE];

  write_u16(block, root_inode_num);
  strcpy((char *)block + 2, ".");

  write_u16(block + 32, root_inode_num);
  strcpy((char *)block + 34, "..");

  bwrite(root_block, block);

  iput(root_inode);
}