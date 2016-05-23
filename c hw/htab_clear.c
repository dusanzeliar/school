 // htab_clear.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor htab_clear.c

 /* htab_clear.c definiton*/
 /* delete all hash table listitems and reset hash table to default */ 


#include <stdlib.h>
#include "htable.h"

void htab_clear(htab_t *t)
{
	struct htab_listitem *current;   //helpful pointers
	struct htab_listitem *next_item;
	
	for (unsigned int i=0; i<t->htab_size; i++){		
		for (current = t->htab_data[i]; current != NULL; current = next_item){
			next_item=current->next;
			free(current->key);    //free char*
			free(current);         //free listitem   
		}
		t->htab_data[i]=NULL;
    }	
    return;
}

