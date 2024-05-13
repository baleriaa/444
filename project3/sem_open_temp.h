#include <semaphore.h>
#ifndef SEM_OPEN_TEMP_H
#define SEM_OPEN_TEMP_H

sem_t *sem_open_temp(const char *name, int value);

#endif