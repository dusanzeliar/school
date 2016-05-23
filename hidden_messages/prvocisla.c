 // prvocisla.c
 // Riesenie IJC-DU1, priklad a), 23.3.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor prvocisla.c
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "bit-array.h"
#include "eratosthenes.c"

#define N 101000000


int main(void){
   
    BitArray(array,N);
    Eratosthenes(array);
   

       //print last 10 prime numbers
       unsigned long prime_count=0;
       unsigned long prime[10];
      
          for (unsigned long i=array[0];(i>=2)&&(prime_count<10);i--){
                if (!(GetBit(array,i))){
                   prime[prime_count]=i;
                   prime_count++;}
        }
        
        while (prime_count>0){
        prime_count--;
        printf("%ld\n",prime[prime_count]);
        } 

        return 0;
}


