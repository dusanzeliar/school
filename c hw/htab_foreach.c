 // htab_foreach.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor htab_foreach.c

 /* htab_foreach.c definiton*/
 /* calls passed function for each hash table elemetn */ 

#include "htable.h"
#include <stdio.h>


void htab_foreach(htab_t *t, void (* funct_ptr)(struct htab_listitem *current) )
{
    struct htab_listitem *current;                  //pointer on hash table element
    for (unsigned int i=0; i<t->htab_size; i++){    //call funtion until last element is fount(NULL)
           for (current = t->htab_data[i]; current !=NULL; current = current->next)
             funct_ptr(current);
	}
    return;
}
