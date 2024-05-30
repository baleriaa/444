#include <stdio.h>
#include "inode.h"
#include "dir.h"
#include <stdlib.h>

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