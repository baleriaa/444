#include <stdio.h>
#include <pthread.h>

#define THREADS 2
#define PRINTED_NUMS 5

void *print_nums(void *arg) {

  for (int i = 0; i < PRINTED_NUMS; i++) {
    printf("%s: %i\n", (char*) arg, i);
  }
  
  pthread_exit(NULL);

  return NULL;

}

int main(void) {

  pthread_t thread[THREADS];
  char *thread1_name = "Thread 1";
  char *thread2_name = "Thread 2";

  printf("Launching threads\n");
  pthread_create(&thread[0], NULL, print_nums, thread1_name);
  pthread_create(&thread[1], NULL, print_nums, thread2_name);

  for (int i = 0; i < THREADS; i++) {
    pthread_join(thread[i], NULL);
  }

  printf("Threads complete!");

  return 0;
}