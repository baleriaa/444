# Project 1: Multithreading

## Building

Command Line:

* `make` to build. An executable called `reservations` will be produced.
* 3 arguments are required. First is the number of seats, then brokers, then transactions.

## Files

* `reservations.c` The main code that runs the reservation system simulation. 

## Data

* `seat_taken`: An array of booleans that indicate whether a seat is taken or not. 
* `seat_taken_count`: A counter that keeps track of the number of taken seats.

## Functions

* `is_free()`: Checks if a seat is free.
* `reserve_seat()`: Reserves a seat if it's free.
* `free_seat()`: Frees a seat if it's not free
* `verify_seat_count()`: Checks to make sure that the count of seats taken is correct.
* `*seat_broker()`: Used for reserving or freeinf seats.
* `main()`: Runs the reservation system simulation.

## Notes

