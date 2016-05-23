 // htable.h
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .h subor htable.h

 /* htable.h definiton*/
 /* header file for hash table functions and structure */ 

#ifndef HTABLE_H
#define HTABLE_H

#include <stdio.h>

//listitems 
struct htab_listitem {
    char * key;
    int data;
    struct htab_listitem *next;
};

//hash table
typedef struct {
    unsigned int htab_size;
    struct htab_listitem *htab_data[];
} htab_t;

//functions prototypes

unsigned int hash_function(const char *str, unsigned htab_size);
void  htab_statistics(htab_t *t);
htab_t *htab_init(unsigned int size);
struct htab_listitem * htab_lookup(htab_t *t, const char *key);
void htab_foreach(htab_t *t, void (* funct_ptr)(struct htab_listitem *current));
void htab_remove(htab_t *t, const char *key);
void htab_clear(htab_t *t);
void htab_free(htab_t *t);

#endif
