 // htab_statistics.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor htab_statistics.c

 /* htab_statistics.c definiton*/
 /* prints length of the longest and number and average of connected listitems */ 


#include "htable.h"
#include <stdio.h>
#include <limits.h>


void  htab_statistics(htab_t *t)
{
	unsigned int list_max=0;        //helpful variables
	unsigned int list_min=INT_MAX;
	unsigned int list_number=0;
	unsigned int total_words=0;
	unsigned int list_length=0;
	
	struct htab_listitem *current;
	
	for (unsigned int i=0; i<t->htab_size; i++){  //starts at first hash table element
		if (t->htab_data[i] != NULL){
			list_number++;
			list_length=0;
			
		    for (current = t->htab_data[i]; current != NULL; current = current->next) list_length++;

			if (list_length < list_min) list_min= list_length;  //set max and min value
			if (list_length > list_max) list_max= list_length;
			total_words+=list_length;
		}
	}
	if (list_number == 0){
		printf("Neobsahuje ziadne slova\n");
		return;
	}
	
	printf("Priemer: %d    Min: %d    Max: %d    Pocet: %d\n",total_words / list_number, list_min, list_max,total_words);	
	
}
