 // wordcount.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor wordcount.c

 /* wordcount.c definiton*/
 /* prints number of words got from stdin  */ 

#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "io.c"
 /** Velkost hash tabulky zavisi od poctu prvkov v nej ulozenych.
 ** V idealnom pripade je casova zlositost vyhladavania logaritmicka, co
 ** vyzaduje velkost hash tabulky > pocet prvkov v nej. Idealny pomer je 0.75.
 ** Kedze dopredu nevime velkost prvov v nej, mozeme len hadat priemerny pocet slov.
 ** Ja som si zvolil hranicu medzi malymi subormi a velkymi, co moze by napriklad 2039. 
 **/

#define TAB_SIZE 2048
#define maximum 300

void htab_print(struct htab_listitem *current);

void htab_print(struct htab_listitem *current)
{
	printf("%s\t%d\n",current->key,current->data); //prints key and its number
        return;
}


int main()
{
	htab_t *t;        
	t=htab_init(TAB_SIZE); //initialization
	char word[maximum]={'\0'};
	int cut,print_error=0;
	
	while ( (cut=fgetw(word,maximum,stdin)) != EOF){
             
                //checks, if value returned is bigger then should be chars loaded
                //if maximum is bigger then limit (127), check for thaht value
                
                if (maximum> 127){
                  if ((cut == 127) && (print_error == 0) ){
                     print_error=1;
                     fprintf(stderr, "Slovo bolo orezane\n"); 
                  }
                }else if ( (cut == maximum) && (print_error == 0) ){
                   print_error=1;
                   fprintf(stderr, "Slovo bolo orezane\n");
                }
                  
                //loading words to hashtable
		if (htab_lookup(t,word) == NULL){ 
			fprintf(stderr, "Pamet sa nepodarila alokovat\n");
			htab_clear(t);
			return 1;
		}
	}
        if (print_error == 1) fprintf(stderr, "Slovo bolo orezane\n"); 
	
	htab_foreach(t,&htab_print);  // call for each list item function print
		
	htab_free(t);
	
	
	return 0;
}

