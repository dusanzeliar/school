 # htab_remove.c
 # Riesenie IJC-DU2, priklad 2), 28.4.2014
 # Autor: Dusan Zeliar,xzelia00, FIT
 # makefile subor

#Parametre prekladaca

CFLAGS=-std=c99 -Wall -Wextra -pedantic  
#pri pridani -std=c++11 mi merlin hlasil cc1plus: error: unrecognized command line option ‘-std=c++11’
#pravdepodobne nanom nieje verzia podporujuca c11, preto som tento flag nepouzil
CPPFLAGS= -pedantic -Wall

LIB_FILES= hash_function.o htab_clear.o htab_foreach.o htab_free.o htab_init.o htab_lookup.o htab_remove.o htab_statistics.o


all: wordcount wordcount-dynamic fold fold2

#fold2
fold2: fold2.o
	g++ $(CPPFLAGS) fold2.o -o fold2

fold2.o: fold2.cc
	g++ $(CPPFLAGS) -c fold2.cc 


#fold 
fold: fold.o
	gcc $(CFLAGS) fold.o -o fold

fold.o: fold.c
	gcc $(CFLAGS) -c fold.c -o fold.o


#static wordcount
wordcount: wordcount.o  libhtable.a
	gcc $(CFLAGS) -o wordcount -static wordcount.o -L. -lhtable

#dynamic wordcount
wordcount-dynamic: wordcount.o libhtable.so
	gcc $(CFLAGS) -o wordcount-dynamic -dynamic wordcount.o -L. -lhtable	


#kniznice

libhtable.so: $(LIB_FILES) htable.h
	gcc -shared -fPIC $(LIB_FILES) -o libhtable.so

libhtable.a: $(LIB_FILES) htable.h
	ar crs libhtable.a $(LIB_FILES)
# obj subory

wordcount.o: wordcount.c io.c htable.h
	gcc $(CFLAGS) -c wordcount.c -o wordcount.o

hash_function.o: hash_function.c htable.h
	gcc $(CFLAGS) -c -fPIC hash_function.c -o hash_function.o

htab_clear.o: htab_clear.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_clear.c -o htab_clear.o

htab_init.o: htab_init.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_init.c -o htab_init.o

htab_lookup.o: htab_lookup.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_lookup.c -o htab_lookup.o

htab_free.o: htab_free.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_free.c -o htab_free.o

htab_foreach.o: htab_foreach.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_foreach.c -o htab_foreach.o

htab_remove.o: htab_remove.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_remove.c -o htab_remove.o

htab_statistics.o: htab_statistics.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_statistics.c -o htab_statistics.o





