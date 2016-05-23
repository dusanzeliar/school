 // eratosthnes.c
 // Riesenie IJC-DU1, priklad a), 23.3.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor eratosthenes

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "bit-array.h"

/*
 * Eratosthenes function, set 0 bit to all prime numbers from 2 to N
 */


void Eratosthenes(BitArray_t p){
    unsigned long i=2;
	unsigned long n;
	
	while(i<=sqrt(p[0])) {
		if (!GetBit(p,i)){
			n=2;
		    while ((n*i) <=(p[0])) {
			    SetBit(p,n*i,1);
			    n++;}
	        } 
	    i++;
	}

}
