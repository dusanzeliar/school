 // htab_remove.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor htab_remove.c

 /* htab_remove.c definiton*/
 /* search for key in list elements, on succes free that element */ 


#include "htable.h"
#include <stdlib.h>
#include <string.h>

void htab_remove(htab_t *t, const char *key)
{
	unsigned int index=hash_function(key,t->htab_size);
	
	struct htab_listitem *current =t->htab_data[index]; //helpful pointers
	struct htab_listitem *previous =t->htab_data[index];
	
	while( current != NULL){
		if ( strcmp(current->key, key) == 0 ) {
			if (previous  == current){
				 t->htab_data[index]=current->next;
			 }else previous->next=current->next;
			free(current->key);
			free(current);
			return;
		}
		previous=current;
		current=current->next;
	}
	return;
	
}
