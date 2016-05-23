CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic -lrt
LFLAGS = -lrt -lpthread

all : rivercrossing

rivercrossing : rivercrossing.c
	gcc $(CFLAGS) -o $@ rivercrossing.c $(LFLAGS)
	
