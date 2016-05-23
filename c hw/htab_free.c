 // htab_free.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor htab_free.c

 /* htab_free.c definiton*/
 /* free all listitems (clear) and hash table */ 

#include <stdlib.h>
#include "htable.h"

void htab_free(htab_t *t)
{
	htab_clear(t);
	free(t);
}

