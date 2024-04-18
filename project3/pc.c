#include <pthread.h>
#include <semaphore.h>
#include "eventbuf.h"
#include "sem_open_temp.h"

// Create the event buffer
struct eventbuf *event_buffer;
int events;

void *producers(void *arg) {
    int *producer_number = arg;

// Wait to see if a producer has put anything in the buffer.
// Lock a mutex around the eventbuf.
// Check to see if the eventbuf is empty.
// If it is, we're done and it's time to exit our loop. Be sure to unlock the mutex first.
// Since the eventbuf wasn't empty, get an event from it.
// Print a message about the event being received. This should match the sample output, above.
// Unlock the mutex
// If we're not done, post to the semaphore indicating that there are now free spaces for producers to put events into
}

void *consumers(void *arg) {
    int *consumer_number = arg;

// Wait to see if a producer has put anything in the buffer.
// Lock a mutex around the eventbuf.
// Check to see if the eventbuf is empty.
// If it is, we're done and it's time to exit our loop. Be sure to unlock the mutex first.
// Since the eventbuf wasn't empty, get an event from it.
// Print a message about the event being received. This should match the sample output, above.
// Unlock the mutex
// If we're not done, post to the semaphore indicating that there are now free spaces for producers to put events into
}

// Parse the command line
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Error, 4 arguments required: producers, consumers, events, and outstanding events.");
    }

    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    events = atoi(argv[3]);
    int buffer_max = atoi(argv[4]);
    event_buffer = eventbuf_create();


}