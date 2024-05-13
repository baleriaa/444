# Project 5: Starting the File System

## Building

Command Line:

* `make` to build. An executable called `testfs` will be produced.
* `make test` to build and run tests.
* `make clean` to clean up object files.

## Files

* `image.c`: Opens or creates and closes files
* `block.c`: Reads and writes block of data into buffer

## Data

* `image_fd` file deascriptor for the image file
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

