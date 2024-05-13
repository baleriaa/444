#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// These will be initialized in main() from the command line.
int seat_count;
int broker_count;
int transaction_count;
int *seat_taken;  // Array of seats
int seat_taken_count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int is_free(int n) {
    return !seat_taken[n];
}

int reserve_seat(int n)
{
    pthread_mutex_lock(&lock);

    if (is_free(n)) {
        seat_taken[n] = 1;
        seat_taken_count++;
        pthread_mutex_unlock(&lock);
        return 0;
    } else {
        pthread_mutex_unlock(&lock);
        return -1;
    }
}

int free_seat(int n)
{
    // Attempt to free (unreserve) seat number n
    // If the seat is already free, return -1
        // Otherwise mark the seat as free and return 0
    //
    // This function should also decrement seat_taken_count if the seat
    pthread_mutex_lock(&lock);

    if (is_free(n)) {
        pthread_mutex_unlock(&lock);
        return -1;
    } else {
        seat_taken[n] = 0;
        seat_taken_count--;
        pthread_mutex_unlock(&lock);
        return 0;
    }
}

int verify_seat_count(void) {
    // This function counts all the taken seats in the seat_taken[]
    // array.
    //
    
    // It then compares the count with the seat_count global variable.
    //
    // It returns true if they are the same, false otherwise
    //
    // You MAY modify this function, but the intended functionality must
    // still work properly.
    pthread_mutex_lock(&lock);

    int count = 0;
    // Count all the taken seats
    for (int i = 0; i < seat_count; i++)
        if (seat_taken[i])
            count++;

    // Return true if it's the same as seat_taken_count
    int result = count == seat_taken_count;  // counting and  comparison is done while lock is held
    pthread_mutex_unlock(&lock);
    return result;
}

// ------------------- DO NOT MODIFY PAST THIS LINE -------------------


void *seat_broker(void *arg)
{
    int *id = arg;
// Broker reserves or frees seat
    for (int i = 0; i < transaction_count; i++) {
        int seat = rand() % seat_count;
        if (rand() & 1) {
            // buy a random seat
            reserve_seat(seat);

        } else {
            // sell a random seat
            free_seat(seat);
        }
// checks seat count and prints error message
        if (!verify_seat_count()) {
            printf("Broker %d: the seat count seems to be off! " \
                   "I quit!\n", *id);
            return NULL;
        }
    }

    printf("Broker %d: That all seemed to work very well.\n", *id);

    return NULL;
}

int main(int argc, char *argv[])
{
    // Parse command line
    if (argc != 4) {
        fprintf(stderr, "usage: reservations seat_count broker_count xaction_count\n");
        exit(1);
    }

    seat_count = atoi(argv[1]);
    broker_count = atoi(argv[2]);
    transaction_count = atoi(argv[3]);

    // Allocate the seat-taken array
    // memory allocated for array of size: seat_count
    // each element of the array is either 0 or 1
    seat_taken = calloc(seat_count, sizeof *seat_taken);

    // Allocate thread handle array for all brokers
    // memory allocated for array of size: broker_count
    // each element of the array is a pthread_t
    pthread_t *thread = calloc(broker_count, sizeof *thread);

    // Allocate thread ID array for all brokers
    // memory allocated for array of size: broker_count
    // each element of the array is an id of type int
    int *thread_id = calloc(broker_count, sizeof *thread_id);

    srand(time(NULL) + getpid());
    
    // Launch all brokers
    // for each broker, create a thread and call seat_broker function
    for (int i = 0; i < broker_count; i++) {
        thread_id[i] = i;
        pthread_create(thread + i, NULL, seat_broker, thread_id + i);
    }

    // Wait for all brokers to complete
    // for each broker, wait for the thread to complete
    for (int i = 0; i < broker_count; i++)
        pthread_join(thread[i], NULL);
}

