 // error.c
 // Riesenie IJC-DU1, priklad b), 23.3.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor error.c

#include <stdio.h>
#include <stdarg.h>
#include "error.h"
#include <stdlib.h>

//prints to stderr
void Warning(const char *fmt, ...){
	va_list args;
	va_start(args,fmt);
	
	fprintf( stderr, "CHYBA: " );
    vfprintf( stderr, fmt, args );
    va_end( args );	
    return;	
}

//prints to stderr, call exit
void FatalError(const char *fmt, ...){
	va_list args;
	va_start(args,fmt);
	
	fprintf( stderr, "CHYBA: " );
    vfprintf( stderr, fmt, args );
    va_end( args );	
    exit(1);
    return;	
}

