 // steg-decode.c
 // Riesenie IJC-DU1, priklad b), 23.3.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor steg-decode.c

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#include "eratosthenes.c"
#include "ppm.h"

#define data_limit (3*1000*1000)

int main(int argc, char **argv)
{
	/*Variable declaraton*/
	
	struct ppm *message=NULL;
	unsigned long data_size;
	unsigned char decode_char=0,char_end=1;
	int bit_loaded=0;
	
	/*Pass picture name from first parameter*/
	
	if ( argc!=2 ){
		FatalError("Zle zadany pocet argumentov\n");
		return 1;
	}

	if ( argc==2 && ( (message=ppm_read(argv[1]) ) )==NULL){
		free(message);
		FatalError("Chyba citania suboru %s\n",argv[1]);
		return 1;
	}
		
	/*Inicialize BitArray and apply Eratosthenes algorithm */
		
	data_size=message->xsize*message->ysize*3+1;
	BitArray(array,data_limit);
	Eratosthenes(array);

	/*Print hidden message by chars */
			
		for(unsigned long i=2;((i<data_size) && (char_end !='\0'));i++){
			if (!(GetBit(array,i))){
				
				decode_char |= ((DU1__GET_BIT(message->data,((i)*8+7)) << bit_loaded));
				
				/*after 8 loaded bits, print char*/
				if ( bit_loaded==7 ){
					if ( isprint(decode_char) ){
						printf("%c",decode_char);
					}
					else if(decode_char!='\0'){
						free(message);
						FatalError("Chyba, %s obsahuje netisknutelny znak\n",argv[1]);
					}
				 		
				 	/*end decoding message when '/0' is reached*/		
					if (decode_char==0) char_end=0;
					
					bit_loaded=0;
					decode_char=0;
				}
			    else{
				    bit_loaded++;
				}
			}
		}
		
		/*Check last character for '\0' char */
		if (char_end!=0){
			free(message);
			FatalError("Chyba, %s neobsahuje '\0'\n",argv[1]);
		}
	
	free(message);	
	
	return 0;
}

