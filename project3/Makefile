CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: pc

pc: pc.o eventbuf.o sem_open_temp.o
	$(CC) $(CFLAGS) -o pc pc.o eventbuf.o sem_open_temp.o -lpthread

pc.o: pc.c
	$(CC) $(CFLAGS) -c pc.c

eventbuf.o: eventbuf.c
	$(CC) $(CFLAGS) -c eventbuf.c

sem_open_temp.o: sem_open_temp.c
	$(CC) $(CFLAGS) -c sem_open_temp.c

clean:
	rm -f *.o pc
