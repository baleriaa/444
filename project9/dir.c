#include <stdio.h>
#include "inode.h"
#include "dir.h"
#include <stdlib.h>
#include "pack.h"
#include "block.h"
#include <string.h>
#include "namei.h"

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

char *get_dirname(const char *path, char *dirname)
{
strcpy(dirname, path);
char *p = strrchr(dirname, '/');
if (p == NULL) {
strcpy(dirname, ".");
return dirname;
}
if (p == dirname) // Last slash is the root /
*(p+1) = '\0';
else
*p = '\0'; // Last slash is not the root /
return dirname;
}
char *get_basename(const char *path, char *basename)
{
if (strcmp(path, "/") == 0) {
strcpy(basename, path);
return basename;
}
const char *p = strrchr(path, '/');
if (p == NULL)
p = path; // No slash in name, start at beginning
else
p++; // Start just after slash
strcpy(basename, p);
return basename;
}

int directory_make(char *path) {
  char dirname[256];
  get_dirname(path, dirname);

  char basename[256];
  get_basename(path, basename);

  struct inode *parent_inode = namei(dirname);
  if (parent_inode == NULL) {
    return -1;
  }

  struct inode *new_inode = ialloc();
  if (new_inode == NULL) {
    return -1;
  }

  unsigned int new_inode_num = new_inode->inode_num;

  int new_data_block = alloc();
  if (new_data_block == -1) {
    return -1;
  }

  unsigned char block[BLOCK_SIZE] = {0};

  write_u16(block, new_inode_num);
  strcpy((char *)(block + 2), ".");

  write_u16(block + 32, parent_inode->inode_num);
  strcpy((char *)(block + 34), "..");

  new_inode->flags = 2;
  new_inode->size = 64; 
  new_inode->block_ptr[0] = new_data_block;

  bwrite(new_data_block, block);

  unsigned int parent_size = parent_inode->size;
  unsigned int parent_index = parent_size / BLOCK_SIZE;
  unsigned int parent_offset = parent_size % BLOCK_SIZE;

  if (parent_size % BLOCK_SIZE == 0) {
    int new_block = alloc();
    if (new_block == -1) {
      return -1;
    }
    parent_inode->block_ptr[parent_index] = new_block;
    memset(block, 0, BLOCK_SIZE);
  } else {
    int parent_block = parent_inode->block_ptr[parent_index];
    bread(parent_block, block);
  }

  write_u16(block + parent_offset, new_inode_num);
  strncpy((char *)(block + parent_offset + 2), basename, 15);
  block[parent_offset + 17] = '\0';

  int parent_block = parent_inode->block_ptr[parent_index];
  bwrite(parent_block, block);

  parent_inode->size += 32;

  iput(new_inode);
  iput(parent_inode);

  return 0;
}