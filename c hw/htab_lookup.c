 // htab_lookup.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor htab_lookup.c

 /* htab_lookup.c definiton*/
 /* search key in all listitems of hash table index set by hash function */ 
 /* if key was found, incrment his number and return pointer and returns pointer*/
 /* if key was not fount, allocate new listitem*/
 /* on fail return NULL*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"

struct htab_listitem * htab_lookup(htab_t *t, const char *key)
{
	if ( (t == NULL) || (key == NULL) ) return NULL;
	
	unsigned int index=hash_function(key,t->htab_size);
	
	struct htab_listitem *current =t->htab_data[index];
	struct htab_listitem *previous =t->htab_data[index];
	
	while( current != NULL){ //search throught listitems
		if ( strcmp(current->key, key) == 0 ) { //key found, increment and return pointer
			current->data++;
			return current;
		}
		previous=current;
		current=current->next;
	}
	
        //malloc new listitem  
	struct htab_listitem *new= malloc(sizeof(struct htab_listitem));
	if (new == NULL) return NULL;		
	
	int word_size=(strlen(key) +1);
	new->key= malloc(word_size);
	if (new->key == NULL) {
		free(new);
		return NULL;
	}
	
	new->key=strncpy(new->key, key,word_size);
	new->data=1;
	new->next=NULL;
	
        //if it was first element,change hash table pointer
	if (previous == current) {
		t->htab_data[index]=new;
	}
	  else previous->next=new;
	
	return new;	
}
