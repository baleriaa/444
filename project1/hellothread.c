#include <stdio.h>
#include <pthread.h>

#define THREADS 2
#define PRINTED_NUMS 5

void *print_nums(void *arg) {

  (void) arg;

  int num_thread = *((int*) arg);

  for (int i = 0; i < PRINTED_NUMS; i++) {
    printf("Thread %i: %i\n", num_thread, i);
  }
  
  pthread_exit(NULL);

  return NULL;

}

int main(void) {

  pthread_t thread[THREADS];
  int num_thread[THREADS];

  printf("Launching threads\n");

  for (int i = 0; i < THREADS; i++) {
    num_thread[i] = i;
    pthread_create(&thread[i], NULL, print_nums, (void*) &num_thread[i]);
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_join(thread[i], NULL);
  }

  printf("Threads complete!");

  return 0;
}