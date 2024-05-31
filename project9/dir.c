#include <stdio.h>
#include "inode.h"
#include "dir.h"
#include <stdlib.h>
#include "pack.h"
#include "block.h"
#include <string.h>

struct directory *directory_open(int inode_num) {
  struct inode *inode = iget(inode_num);
  if (!inode) {
    return NULL;
  }

  struct directory *dir = malloc(sizeof(struct directory));
  dir->inode = inode;
  dir->offset = 0;  

  return dir;
}

void directory_close(struct directory *dir) {
  iput(dir->inode);
  free(dir);
}

int directory_get(struct directory *dir, struct directory_entry *ent) {
  if (dir->offset >= dir->inode->size) {
    return -1;
  }

  int data_block_index = dir->offset / BLOCK_SIZE;
  int offset = dir->offset % BLOCK_SIZE;
  unsigned char block[BLOCK_SIZE];

  int data_block_num = dir->inode->block_ptr[data_block_index];
  bread(data_block_num, block);

  unsigned char *dir_start = block + offset;
  ent->inode_num = read_u16(dir_start);
  strncpy(ent->name, (char *)(dir_start + 2), 15);
  ent->name[15] = '\0';

  dir->offset += 32;
  
  return 0;
}