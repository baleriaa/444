pc: pc.c
	gcc -Wall -Wextra -Werror -o $@ $^ -lpthread

pc.zip:
	rm -f $@
	zip $@ Makefile pc.c
