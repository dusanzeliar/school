 // ppm.c
 // Riesenie IJC-DU1, priklad b), 23.3.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor obsahuje funckcie write a read

#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "error.h"

#define data_limit (1000*1000*3)


int ppm_write(struct ppm *p, const char * filename){
	FILE *fw;
	unsigned data_size;
	
	if ((fw=fopen(filename,"wb"))==NULL){
	  Warning("Subor %s sa nepodarilo otvorit \n",filename);
	  return -1;
    }
	
	if ((fprintf(fw, "%s \n%u %u \n%u", "P6",p->xsize,p->ysize,255))<0){
	  Warning("Zapis do suboru %s sa nepodaril \n",filename);
	  fclose(fw);
	  return -1;
    }		
	
	data_size=p->xsize*p->ysize*3+1;
	
	if ((fwrite(p->data,1, data_size, fw ))!=data_size){
	  Warning("Zapis pixelov do suboru %s sa nepodaril \n",filename);
	  fclose(fw);
	  return -1;
    }					
	
	fclose(fw);
	return 0;
}
	


struct ppm * ppm_read(const char * filename){
	FILE *fr;
	char p;
	unsigned six;
	unsigned color;
	unsigned xsize;
	unsigned ysize;
	unsigned data_size;
	struct ppm * picture=NULL;
	
	if ((fr=fopen(filename,"rb"))==NULL){
	  Warning("Subor %s sa nepodarilo otvorit \n",filename);
	  return NULL;
    }
	
	if ((fscanf(fr,"%c %u %u %u %u",&p,&six,&xsize,&ysize,&color)) != 5){
		Warning("Subor %s ma nekorektne zadanu hlavicku suboru \n",filename);
		fclose(fr);
		return NULL;
	}
	
	if ((p!='P') || (six!=6)) {
		Warning("Subor %s nieje typu P6 \n",filename);
		fclose(fr);
		return NULL;
	} 	
	
	if (color!=255) {
		Warning("Subor %s neobsahuje farby od 0..255 \n",filename);
		fclose(fr);
		return NULL;
	}
	
	data_size=xsize*ysize*3+1;
	if (data_size > data_limit) {
		Warning("Subor %s presahuje limit velkosti",filename);
		fclose(fr);
		return NULL;
	}
	
	if ((picture=(struct ppm *) malloc(sizeof(struct ppm)+data_size))==NULL) {
		Warning("Nepodarilo sa alokovat strukturu \n");
		fclose(fr);
		return NULL;
	}
	
	picture->xsize=xsize;
	picture->ysize=ysize;
		
	if ((fread(&picture->data,1,data_size,fr))!=data_size) {
		Warning("Subor %s nema korektne data pixelov\n",filename);
		fclose(fr);
		free(picture);
		return NULL;
	}

	fclose(fr);
	return picture;
}
