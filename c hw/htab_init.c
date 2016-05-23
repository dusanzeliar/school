 // htab_init.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor htab_init.c

 /* htab_init.c definiton*/
 /* initialize new hash table and set all pointers to NULL, return pointer to new table of NULL (if failed) */ 


#include <stdlib.h>
#include <string.h>
#include "htable.h"

htab_t *htab_init(unsigned int size)
{
    htab_t *newtable= malloc( sizeof(htab_t) + size*sizeof(struct htab_listitem *)); //malloc htab_t and array multipled by number of elements
    if ( newtable == NULL) return NULL;  
    
    newtable->htab_size=size;
    
    for (unsigned int i=0; i<size; i++){
		newtable->htab_data[i]=NULL;
	}
     return newtable;  
    
}
