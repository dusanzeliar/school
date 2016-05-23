 // bit-array.h
 // Riesenie IJC-DU1, priklad a), 23.3.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .h subor bit-array.h
/* bit-array.h definiton*/

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "error.h"

/*typedef to pass argument to inline functions*/

typedef unsigned long BitArray_t[];

/* initializtion of BitArray, first element of array includes size in bits*/

#define BitArray(array, SIZE)  unsigned long array[array_size(SIZE)] = {SIZE, 0 }

/* Helpful macros that return size of unsigned long in bits and number of array's elemetns */

#define ul_size ( (sizeof( unsigned long)) *8)

#define array_size(SIZE) ((SIZE % ul_size) ? (SIZE/ul_size +2) : (SIZE/ul_size +1)) 
 
/* Macros without INLINE functions*/ 
 
#ifndef USE_INLINE 
                            
                            
/* returns size of array in bits*/                            
#define BitArraySize(array) (array[0])

        
/* Set bit on INDEX to 0 or 1
 *
 * Check arrays boards 
*/
#define SetBit(array,INDEX,SIGN) (INDEX>array[0]) ?                                       \
          /*Calls fatal erron in case index is out of array*/                             \
         (FatalError("Index %ld mimo S rozsah 0..%ld", (long)INDEX, (long)array[0]), 0) :   \
                                                                                          \
          /* Check bit sign ( 0 or 1) and set bit */                                      \
         ((SIGN) ?                                                                        \
               /* Set 1*/                                                                 \
              (array[INDEX / ul_size +1] |=((unsigned long) 1<<(ul_size-1-(INDEX % ul_size)))) :\
               /* Set 0*/                                                                  \
              (array[INDEX / ul_size +1] &=((~(unsigned long) 0) ^ ((unsigned long) 1<<(ul_size-1-(INDEX % ul_size))))))         
        

/* Return value of INDEX bit, 0 or 1
 *    Check arrays boards */      
#define GetBit(array, INDEX)  ((INDEX>array[0]) ?                                          \
          /*Calls fatal erron in case index is out of array*/                             \
         (FatalError("Index %ld mimo G rozsah 0..%ld", (long)INDEX, (long)array[0]), 1) : \
         /*Return bit sign */                                                             \
         (( array[INDEX / ul_size +1] >> (ul_size-1-(INDEX % ul_size))) & 1))




#endif
                                     
/* 
 * Macros to set and get bit of undefined array
 */       
 
#define  DU1__GET_BIT(p,i) (( p[i / (sizeof(p[0])*8) +1] >> (sizeof(p[0])*8-1-(i % (sizeof(p[0])*8)))) & 1)    

#define DU1__SET_BIT(p,i,b) (b) ? \
        (array[i / (sizeof(p[0])*8)] |=( 1<<(sizeof(p[0])*8-1-(i % (sizeof(p[0])*8))))) : \
        (array[i / (sizeof(p[0])*8)] &=((~0) ^ (1<<(sizeof(p[0])*8-1-(i % (sizeof(p[0])*8)))))) 


/*
 *INLINE functions 
 */
 
#ifdef USE_INLINE   

/* returns size of array in bits*/     	
static inline unsigned long BitArraySize(BitArray_t array) {return array[0];}
           
/* Return value of INDEX bit, 0 or 1*/  
static inline unsigned long GetBit(BitArray_t array, unsigned long INDEX) {
	if (INDEX>array[0]) FatalError("Index %ld mimo rozsah 0..%ld", (long)INDEX, (long)array[0]);
	
	return  ( array[INDEX / ul_size +1] >> (ul_size-1-(INDEX % ul_size))) & 1;
	}

/* Set bit on INDEX to 0 or 1*/ 
static inline void SetBit( BitArray_t array, unsigned long INDEX, unsigned long SIGN){
	if (INDEX>array[0]) FatalError("Index %ld mimo rozsah 0..%ld", (long)INDEX, (long)array[0]);
	
      if (SIGN) 
        array[INDEX / ul_size +1] |=((unsigned long) 1<<(ul_size-1-(INDEX % ul_size)));
        else
        array[INDEX / ul_size +1] &=((~(unsigned long) 0) ^ ((unsigned long) 1<<(ul_size-1-(INDEX % ul_size))));
        return;  
    }
	      
#endif        	                              

#endif
