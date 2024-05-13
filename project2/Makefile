reservations: reservations.c
	gcc -Wall -Wextra -Werror -o $@ $^ -lpthread

reservations.zip:
	rm -f $@
	zip $@ Makefile reservations.c
