#include <stdio.h>
#include <pthread.h>

#define THREADS 2
#define PRINTED_NUMS 5

void *print_nums(void *arg) {

  (void) arg;

  for (int i = 0; i < PRINTED_NUMS; i++) {
    printf("Thread %s: %i\n", (char *) arg, i);
  }
  
  return NULL;

}

int main(void) {

  pthread_t thread[THREADS];

  printf("Launching threads\n");

  for (int i = 0; i < THREADS; i++) {
    pthread_create(thread, NULL, print_nums, (void*) thread[i]);
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_join(thread[i], NULL);
  }

  printf("Threads complete!");

  return 0;
}