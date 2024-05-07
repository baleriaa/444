#include "image.h"
#include "block.h"
#include <unistd.h>
#include <fcntl.h>

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