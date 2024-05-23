#include "inode.h"
#include "block.h"
#include "free.h"
#include <stdio.h>
#include "pack.h"

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

void read_inode(struct inode *in, int inode_num) {
  unsigned char block[BLOCK_SIZE] = {0};
  int block_num = inode_num / INODES_PER_BLOCK + INODE_FIRST_BLOCK;
  int block_offset = inode_num % INODES_PER_BLOCK;
  int block_offset_bytes = block_offset * INODE_SIZE;
  
  bread(block_num, block);

  in->size = read_u32(block +block_offset_bytes);
  in->owner_id = read_u16(block + block_offset_bytes + 4);
  in->permissions = read_u8(block + block_offset_bytes + 6);
  in->flags = read_u8(block + block_offset_bytes + 7);
  in->link_count = read_u8(block + block_offset_bytes + 8);

  for (int i = 0; i < INODE_PTR_COUNT; i++) {
    in->block_ptr[i] = read_u16(block + block_offset_bytes + 9 + i * 2);
  }
}

void write_inode(struct inode *in) {
  unsigned char block[BLOCK_SIZE] = {0};
  int block_num = in->inode_num / INODES_PER_BLOCK + INODE_FIRST_BLOCK;
  int block_offset = in->inode_num % INODES_PER_BLOCK;
  int block_offset_bytes = block_offset * INODE_SIZE;

  bread(block_num, block);

  write_u32(block + block_offset_bytes, in->size);
  write_u16(block + block_offset_bytes + 4, in->owner_id);
  write_u8(block + block_offset_bytes + 6, in->permissions);
  write_u8(block + block_offset_bytes + 7, in->flags);
  write_u8(block + block_offset_bytes + 8, in->link_count);

  for (int i = 0; i < INODE_PTR_COUNT; i++) {
    write_u16(block + block_offset_bytes + 9 + i * 2, in->block_ptr[i]);
  }
  bwrite(block_num, block);
}

struct inode *iget(int inode_num) {
  struct inode *in = incore_find(inode_num);
  
  if (in != NULL) {
    in->ref_count++;
    return in;
  } else {
    in = incore_find_free();
    if (in == NULL) {
      return NULL;
    }
    in->ref_count = 1;
    in->inode_num = inode_num;
    read_inode(in, inode_num);
    return in;
  }
}

void iput(struct inode *in) {
  if(in->ref_count == 0){
    return;
  } 
  in->ref_count--;
  if (in->ref_count == 0) {
    write_inode(in);
  }
}