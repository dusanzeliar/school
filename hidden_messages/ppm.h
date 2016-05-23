 // ppm.h
 // Riesenie IJC-DU1, priklad b), 23.3.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .h subor ppm.h

#ifndef PPM_H
#define PPM_H

/*PPM structere */
struct ppm { 
	unsigned xsize; 
	unsigned ysize;
	char data[]; 
	};
	
/*
 * Function prototypes
*/		
int ppm_write(struct ppm *p, const char * filename);	

struct ppm * ppm_read(const char * filename);

#endif
