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

## Notes

