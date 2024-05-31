#include <string.h>
#include "inode.h"
#include "namei.h"

#define ROOT_INODE_NUM 0

struct inode *namei(char *path) {
  if (strcmp(path, "/") == 0) {
    return iget(ROOT_INODE_NUM);
  }
  return NULL;
}