 // error.h
 // Riesenie IJC-DU1, priklad b), 23.3.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .h subor error.h

#ifndef ERROR_H
#define ERROR_H

/*
 * Function prototypes
*/
void Warning(const char *fmt, ...);
		
void FatalError(const char *fmt, ...);	

#endif

