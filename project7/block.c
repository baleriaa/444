#include "image.h"
#include "block.h"
#include <unistd.h>
#include <fcntl.h>
#include "free.h"

unsigned char *bread(int block_num, unsigned char *block) {
  int fd = image_fd;
  int offset = block_num * BLOCK_SIZE;

  lseek(fd, offset, SEEK_SET);
  read(fd, block, BLOCK_SIZE);

  return block;
  }

void bwrite(int block_num, unsigned char *block) {
  int fd = image_fd;
  int offset = block_num * BLOCK_SIZE;

  lseek(fd, offset, SEEK_SET);
  write(fd, block, BLOCK_SIZE);
}

int alloc(void) {
  unsigned char block[BLOCK_SIZE];

  bread(2, block);
  int free_block = find_free(block);

  if (free_block == -1) {
    return -1;
  }

  set_free(block, free_block, 1);
  bwrite(2, block);

  return free_block;
}