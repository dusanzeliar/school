 # Makefile
 # Riesenie IJC-DU1, priklad a) b), 23.3.2014
 # Autor: Dusan Zeliar,xzelia00, FIT
 # Přeloženo: gcc 4.6.4


# prekladac jazyka C
CC=gcc
#Parametre prekladaca

CFLAGS=-std=c99 -Wall -Wextra -pedantic -O2 -lm

all: prvocisla prvocisla-inline steg-decode

#Zavislosti prvocisla
prvocisla: prvocisla.o error.o
	$(CC) prvocisla.o error.o -lm -o $@
prvocisla.o: prvocisla.c eratosthenes.c bit-array.h
	$(CC) $(CFLAGS) -c prvocisla.c -o $@

#Zavislosti prvocisla-inline
prvocisla-inline: prvocisla-inline.o error.o
	$(CC) prvocisla-inline.o error.o -lm -o $@
prvocisla-inline.o: prvocisla.c eratosthenes.c bit-array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c prvocisla.c -o $@

#Zavislosti steg-decode
steg-decode: steg-decode.o error.o ppm.o
	$(CC) steg-decode.o error.o ppm.o -lm -o $@
steg-decode.o: steg-decode.c eratosthenes.c ppm.h bit-array.h
	$(CC) $(CFLAGS) -c steg-decode.c -o $@
ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c -o $@

#Zavislosti error a bit-array
bit-array.h: error.o
error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o $@



