# Project 6: Continuing the File System, managing free blocks 

## Building

Command Line:

* `make` to build. An executable called `testfs` will be produced and tests will be run.
* `make test` to build and run tests.
* `make clean` to clean up object files.

## Files

* `image.c`: Opens or creates and closes files
* `block.c`: Reads and writes block of data into buffer
* `free.c`: Finds and sets free bits
* `testfs.c`: Tests for all functions
* `inode.c`: Allocates previosuly free inodes
* `Makefile`: Builds the project and runs tests

## Data

* `image_fd` file descriptor for the image file
* `BLOCK_SIZE` size of block in bytes

## Functions
* `open_image` opens or creates a file
* `close_image` closes a file
* `bread` reads a block of data
* `bwrite` writes a block of data
* `find_low_clear_bit` a function that finds the lowest clear (not-set, zero) bit in a byte:
* `find_free` find a 0 bit and return its index (i.e. the block number that corresponds to this bit).
* `set_free` set a specific bit to the value in set (0 or 1)
* `allooc` allocate a previously-free data block from the block map.
* `ialloc` allocate a previously-free inode in the inode map

## Notes

