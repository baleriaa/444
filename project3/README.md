# Project 3: Producers and Consumers

## Building

Command Line:

* `make` to build. An executable called `pc` will be produced.
* 4 arguments are required. First is the number of producers, second is the number of consumers, third is the number of items, and fourth is the buffer size.

## Files

* `pc.c` The main code that runs the program
* `Makefile` The makefile that builds the program
* `eventbuf.c` Buffer code
* `sem_open_temp.c` Semaphore code

## Data
* `eventbuf` Holds ints that represent events
* `items` trscks the number of events in the `event_buffer`
* `mutex` gives access to event_buffer
* `spaces` number of available spaces in `event_buffer`

## Functions
* `producer()`: Produces events
* `consumer()`: Consumes events
* `main()`: Runs the program.
  * `eventbuf_create()`: Creates the buffer
  * `sem_open_temp()`: Creates a semaphore

## Notes

