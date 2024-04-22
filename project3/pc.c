#include <pthread.h>
#include <semaphore.h>
#include "eventbuf.h"
#include "sem_open_temp.h"
#include <stdio.h>
#include <stdlib.h>

struct eventbuf *event_buffer;
int events;
sem_t *items;
sem_t *mutex;
sem_t *spaces;

void *producer(void *arg) {
  int *producer_number = arg;

  for (int i = 0; i < events; i++) {
    int event_number = *producer_number * 100 + i;
    sem_wait(spaces);
    sem_wait(mutex);
    printf("P%d: adding event %d\n", *producer_number, event_number);
    eventbuf_add(event_buffer, event_number);
    sem_post(mutex);
    sem_post(items);
  }

  printf("P%d: exiting\n", *producer_number);
  return NULL;
}

void *consumer(void *arg) {
  int *id = arg;

  while (1) {
    sem_wait(items);
    sem_wait(mutex);
    if (eventbuf_empty(event_buffer)) {
      sem_post(mutex);
      sem_post(items);
      break;
    }

    int event = eventbuf_get(event_buffer);
    printf("C%d: got event %d\n", *id, event);
    sem_post(mutex);
    sem_post(spaces);
  }

  printf("C%d: exiting\n", *id);
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    printf("Error, 4 arguments required: producers, consumers, events, and outstanding events.");
    exit(1);
  }

  int producers_num = atoi(argv[1]);
  int consumers_num = atoi(argv[2]);
  events = atoi(argv[3]);
  int buffer_max = atoi(argv[4]);
  event_buffer = eventbuf_create(); 
  mutex = sem_open_temp("mutex", 1);
  items = sem_open_temp("items", 0);
  spaces = sem_open_temp("spaces", buffer_max);
  pthread_t producers[producers_num];
  pthread_t consumers[consumers_num];

  for (int i = 0; i < producers_num; i++) {
    int *producer_number = malloc(sizeof(int));
    *producer_number = i;
    pthread_create(&producers[i], NULL, producer, producer_number);
  }

  for (int i = 0; i < consumers_num; i++) {
    int *consumer_number = malloc(sizeof(int));
    *consumer_number = i;
    pthread_create(&consumers[i], NULL, consumer, consumer_number);
  }

  for (int i = 0; i < producers_num; i++) {
    pthread_join(producers[i], NULL);
  }

  for (int i = 0; i < buffer_max; i++) {
    sem_post(items);
  }

  for (int i = 0; i < consumers_num; i++) {
    pthread_join(consumers[i], NULL);
  }

  eventbuf_free(event_buffer);
  return 0;
}
