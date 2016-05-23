/*
 * Projekt 2 IOS
 * Autor: Dusan Zeliar,xzelia00, FIT
 * Prelozene: gcc 4.6.4
 * Datum: 3.5.2014
 */


/*
 * H FILES
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

/*
 * Globalne premenne pre lahsie prevedie funcii
 */
sem_t *sem_molo,*sem_molo_serf,*sem_molo_hacker,*sem_memory,*sem_lod,*sem_clen;
sem_t *sem_vystup,*sem_continue,*sem_finish;
int *serf,*hacker,*p_done,*write_index,*finish;
int shm_1,shm_2,shm_3,shm_4,shm_5;
FILE *out;

/*
 * Prototypy
 */
 int load_arguments(int argc, char *argv[], int * P, int * H, int * S, int * R );
 int sem_initialize();
 int shm_initialize();
 void shm_free();
 void sem_free();
 void proces_finish(char * proces, int i, int P);
 int sem_member(char faza, char * proces, int i, sem_t * semafor);
 void sem_captain(char faza, char * proces, int i,sem_t * semafor);
 void proces_started(char * proces, int i);
 void proces_molo_queue(char * proces, int i, char person, char * clen);
 void terminate();
 
/*
 * Main
 */ 
int main(int argc, char **argv)
{
	int P,H,S,R;
	char * proces;
	char person;
	char clen='C';
	
	//Nacitanie argumentov
	if ( load_arguments(argc,argv,&P,&H,&S,&R) != 0){
		fprintf (stderr, "Zle zadane argumenty");
		exit (1);
	}
	
	//Inicializacia semaforov
	if (sem_initialize() == 1){
		terminate();
	}
	
	//Inicializacia zdielanej pamete
	if (shm_initialize() == 1){
		terminate();
	}
    	
    //Otvorenie vystupneho suboru	
	if ((out = fopen ("rivercrossing.out", "w+")) == NULL){
		fprintf (stderr, "Praca so suborom rivercrossing.out zlyhala");
		terminate();
	}
	
	setbuf(out,NULL);
	
	//child make_hacker
    proces="hacker";
    person='H';
    pid_t pid = fork();
    
    //Parent nastavime na serf, s timto nastavenim vytvorime child make_serf
    if (pid != 0) { proces="serf"; person='S';}
    if (pid != 0) pid = fork();
    
    //Child make_hacker/ make_serf
    if (pid == 0){		

        //Vytvaranie procesov 
		for (int i=1; i<=P ; i++)
		{
			 if (person == 'H'){
				 if (H > 0) usleep((rand() % (H + 1)));
			 }
			 if (person == 'S') {
				 if (S > 0) usleep((rand() % (S + 1)));
			 }
			 pid = fork();
			 
			 if (pid>0) {
				 continue;
			 } else if (pid == 0){
				 
				 //proces zacal
				 proces_started(proces,i);
				 
				 //proces caka na vstup na molo
				 proces_molo_queue(proces, i, person, &clen);
				 
				 //Posadka  - member
				 if ( clen == 'M') {
	
					 /*CAKANIE NA BOARDING*/
					 if (sem_member('B',proces,i,sem_lod) == 3) sem_post(sem_continue);					 
					 
					/*CAKANIE NA VYPIS CLENOV*/				 					 
					 
					 if (sem_member('C',proces,i,sem_clen) == 3) sem_post(sem_continue);				
					 
					/*CAKANIE NA PRISTATIE*/						 
					 
					 if (sem_member('L',proces,i,sem_vystup) == 3) sem_post(sem_continue);
					 
				 }
				 else  //Kapitan -capitan
				 {
                      
                     /*CAKANIE NA BOARDING*/ 
					 sem_captain('B',proces,i,sem_lod);				 				
					 
					 /*CAKANIE NA VYPIS CLENOV*/
					 sem_captain('C',proces,i,sem_clen);									
					 
					 /*PLAVBA*/
					 if (R > 0) usleep((rand() % (R + 1)));
					 
					 /*CAKANIE NA PRISTATIE*/
					 sem_captain('L',proces,i,sem_vystup);					 					 
					 
					 //odomkne molo
					 sem_post(sem_molo);
				 }
				
				//Cakanie na posledny proces
				proces_finish(proces, i, P);
				 
				 exit(0);
			 }
		 }
		 
		 //Cakanie na vsetky child procesy vytvorene procesom make_serf /make_hacker
		 for (int i=1; i<=P ; i++) wait(NULL);	 			
	}else {
		//Parent caka na ukoncenie make_serf /make_hacker
		wait(NULL);
		wait(NULL);}
	
	//Zatvorenie suboru a uvolnenie pameti
	fclose(out);		
	sem_free();
	shm_free();

	return 0;
}

/*
 * load_arguments
 * nacitanie argumentov z prikazoveho riadku
 */  
int load_arguments(int argc, char *argv[], int * P, int * H, int * S, int * R ){

	if (argc != 5) return -1;
	
	char* end;
	
    *P = strtol(argv[1], &end, 10);  
    if (*end || *P < 2 || *P % 2) return -1;
    
    *H = strtol(argv[2], &end, 10);  
    if (*end || *H < 0 || *H > 5000) return -1;
    
    *S = strtol(argv[3], &end, 10);  
    if (*end || *S < 0 || *S > 5000) return -1;
    
    *R = strtol(argv[4], &end, 10);  
    if (*end || *R < 0 || *R > 5000) return -1;
    
    return 0;	
}

/*
 * sem_initialize
 * inicializacia semaforov
 */ 
int sem_initialize(){
	 if ((sem_molo = sem_open("/xzelia00_sem_molo", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 if ((sem_molo_serf = sem_open("/xzelia00_sem_molo_serf", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 if ((sem_molo_hacker = sem_open("/xzelia00_sem_molo_hacker", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 if ((sem_memory = sem_open("/xzelia00_sem_memory", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 if ((sem_lod = sem_open("/xzelia00_sem_lod", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 if ((sem_clen = sem_open("/xzelia00_sem_clen", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 if ((sem_vystup = sem_open("/xzelia00_sem_vystup", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 if ((sem_continue = sem_open("/xzelia00_sem_continue", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 if ((sem_finish = sem_open("/xzelia00_sem_finish", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
		 perror("semaphore initilization");
		 return 1;
	 }
	 return 0;
 }		

/*
 * shm_initialize
 * inicializacia shared memory
 */ 	
int shm_initialize(){
	//shm_open
	if ((shm_1 = shm_open("/xzelia00_sharedMemory1", O_CREAT | O_EXCL | O_RDWR, 0644)) == -1) {
		perror("memory initilization");
		return 1;
	 }
	if ((shm_2 = shm_open("/xzelia00_sharedMemory2", O_CREAT | O_EXCL | O_RDWR, 0644)) == -1) {
		perror("memory initilization");
		return 1;
	 }
	if ((shm_3 = shm_open("/xzelia00_sharedMemory3", O_CREAT | O_EXCL | O_RDWR, 0644)) == -1) {
		perror("memory initilization");
		return 1;
	 }
	if ((shm_4 = shm_open("/xzelia00_sharedMemory4", O_CREAT | O_EXCL | O_RDWR, 0644)) == 1) {
		perror("memory initilization");
		return 1;
	 }
	if ((shm_5 = shm_open("/xzelia00_sharedMemory5", O_CREAT | O_EXCL | O_RDWR, 0644)) == 1) {
		perror("memory initilization");
		return 1;
	 }
    //ftruncate
	if ((ftruncate(shm_1, sizeof(int))) == -1) {
		perror("memory initilization");
		return 1;
	}
	if ((ftruncate(shm_2, sizeof(int))) == -1) {
		perror("memory initilization");
		return 1;
	}
	if ((ftruncate(shm_3, sizeof(int))) == -1) {
		perror("memory initilization");
		return 1;
	}
	if ((ftruncate(shm_4, sizeof(int))) == -1) {
		perror("memory initilization");
		return 1;
	}
	if ((ftruncate(shm_5, sizeof(int))) == -1) {
		perror("memory initilization");
		return 1;
	}
	//mmap
	if ((serf = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_1, 0)) == MAP_FAILED) {
		 perror("memory initilization initilization");
		 return 1;
	 }
	if ((hacker = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_2, 0)) == MAP_FAILED) {
		 perror("memory initilization initilization");
		 return 1;
	 }
	if ((p_done = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_3, 0)) == MAP_FAILED) {
		 perror("memory initilization initilization");
		 return 1;
	 }
	if ((write_index = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_4, 0)) == MAP_FAILED) {
		 perror("memory initilization initilization");
		 return 1;
	 }
	if ((finish = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_5, 0)) == MAP_FAILED) {
		 perror("memory initilization initilization");
		 return 1;
	 }
	return 0;
}	

/*
 * shm_free
 * uvolnenie shared memory
 */ 	
void shm_free(){	
	munmap(serf, sizeof(int));
    munmap(hacker, sizeof(int));
    munmap(write_index, sizeof(int));
    munmap(p_done, sizeof(int));
    munmap(finish, sizeof(int));
    shm_unlink("/xzelia00_sharedMemory1");
    shm_unlink("/xzelia00_sharedMemory2");
    shm_unlink("/xzelia00_sharedMemory3");
    shm_unlink("/xzelia00_sharedMemory4");
    shm_unlink("/xzelia00_sharedMemory5");
    close(shm_1);
    close(shm_2);
    close(shm_3);
    close(shm_4);		
    close(shm_5);
    return;		
}

/*
 * sem_free
 * uvolnenie semaforov
 */ 
void sem_free(){
	
	sem_close(sem_molo);
	sem_unlink("/xzelia00_sem_molo");
	
	sem_close(sem_molo_serf);
	sem_unlink("/xzelia00_sem_molo_serf");
	
	sem_close(sem_molo_hacker);
	sem_unlink("/xzelia00_sem_molo_hacker");
	
	sem_close(sem_memory);
	sem_unlink("/xzelia00_sem_memory");	
	
	sem_close(sem_lod);
	sem_unlink("/xzelia00_sem_lod");	
	
    sem_close(sem_vystup);
	sem_unlink("/xzelia00_sem_vystup");	
	
    sem_close(sem_continue);
	sem_unlink("/xzelia00_sem_continue");	
	
	sem_close(sem_clen);
	sem_unlink("/xzelia00_sem_clen");			
	
	sem_close(sem_finish);
	sem_unlink("/xzelia00_sem_finish");		
	return;			
}

/*
 * proces_sinish
 * cakanie child procesov, pokial vsetky dokoncia plavbu a spolu sa ukoncia
 */ 
void proces_finish(char * proces, int i, int P) {
	
	sem_wait(sem_memory);
	(*finish)++;
	int ended=(*finish);	 				 
	sem_post(sem_memory);
	
	//ak je hodnota finish v shared memory rovna poctu procesov, povol finish, inak cakaj			
	if (ended == (2*P)) {
		for (int j=1; j < (2*P); j++) sem_post(sem_finish);
	}else sem_wait(sem_finish);
				
	sem_wait(sem_memory);
	(*write_index)++;
	fprintf(out,"%d: %s: %d: finished\n",(*write_index),proces,i);
	sem_post(sem_memory);
	return;		
}

/*
 * sem_member
 * riadenie plavby member procesov
 */ 	
int sem_member(char faza, char * proces, int i, sem_t * semafor) {
	
	//cakanie na semafor(odomyka captain)
	sem_wait(semafor);
	
	//podla fazy vypise aktivitu procesu
	sem_wait(sem_memory);
	(*write_index)++;
	switch (faza){
		case 'B':
		  fprintf(out,"%d: %s: %d: boarding: %d: %d\n",(*write_index),proces,i,(*hacker),(*serf));
		  break;
		case 'C':
		  fprintf(out,"%d: %s: %d: member\n",(*write_index),proces,i);
		  break;
		case 'L':
		  fprintf(out,"%d: %s: %d: landing: %d: %d\n",(*write_index),proces,i,(*hacker),(*serf));
		  break;
		default:
		break;
	}
	
	(*p_done)++;
	int proces_done=(*p_done);
	sem_post(sem_memory);
	//vrati pocet member procesov ktore uz touto fazou presli
	return proces_done;	
}

/*
 * sem_captain
 * riadenie plavby captain procesu
 */ 
void sem_captain(char faza, char * proces, int i,sem_t * semafor){
	
	//nastavenie poctu member procesov, ktore presli touto fazou na 0
	sem_wait(sem_memory);
	(*p_done)=0;
	sem_post(sem_memory);
					 
	// otvorenie fazy 3 member procesom
	sem_post(semafor);
	sem_post(semafor);
	sem_post(semafor);
					 
	//podla fazy vypise aktivitu procesu				 
	sem_wait(sem_memory);
	(*write_index)++;
		switch (faza){
		case 'B':
		  fprintf(out,"%d: %s: %d: boarding: %d: %d\n",(*write_index),proces,i,(*hacker),(*serf));
		  break;
		case 'C':
		  fprintf(out,"%d: %s: %d: captain\n",(*write_index),proces,i);
		  break;
		case 'L':
		  fprintf(out,"%d: %s: %d: landing: %d: %d\n",(*write_index),proces,i,(*hacker),(*serf));
		  break;
		default:
		break;
	}
	sem_post(sem_memory);
	
	//cakanie na semafor ktory sa odomkne po ukonceni fazy vsetkymi 3 member procesmi
	sem_wait(sem_continue);
	return;			
}

/*
 * sem_started
 * zaciatok procesu
 */ 	
void proces_started(char * proces, int i){
	
	sem_wait(sem_memory);
	(*write_index)++;
	fprintf(out,"%d: %s: %d: started\n",(*write_index), proces,i);
	sem_post(sem_memory);
	return;
}

/*
 * proces_molo_queue
 * zaciatok cakania procesu na nastup na molo
 */ 
void proces_molo_queue(char * proces, int i, char person, char * clen){	
	
	
	sem_wait(sem_molo);
	
	//zvysenie poctu hackerov/serfov na mole			 
	sem_wait(sem_memory);
	if (person == 'H') {
		(*hacker)++;
	}
	else if (person == 'S') {
		(*serf)++;
	}
	
	//prejde kombinacie 4:0 2:2 0:4, ak sa daju vytvorit, tak sa nastavi proces ako captain,inak member			 				 				 
	if ((*serf) == 4) {
		(*write_index)++;
		fprintf(out,"%d: %s: %d: waiting for boarding: %d: %d\n",(*write_index),proces,i,(*hacker),(*serf));
		(*serf)=0;
		sem_post(sem_memory);
					 
		for (int j=1; j<4; j++) sem_post(sem_molo_serf);
	}
	else if ((*hacker) == 4) {
		(*write_index)++;
		fprintf(out,"%d: %s: %d: waiting for boarding: %d: %d\n",(*write_index),proces,i,(*hacker),(*serf));
		(*hacker)=0;
		sem_post(sem_memory);
					 
		for (int j=1; j<4; j++) sem_post(sem_molo_hacker);					 
	}
      else if (((*serf) > 1) && ((*hacker) > 1)){			   
		(*write_index)++;
		fprintf(out,"%d: %s: %d: waiting for boarding: %d: %d\n",(*write_index),proces,i,(*hacker),(*serf));
		(*hacker)-=2;
		(*serf)-=2;
		sem_post(sem_memory);
					 
		if (person == 'H') sem_post(sem_molo_serf);
			else sem_post(sem_molo_hacker);
		sem_post(sem_molo_serf);
		sem_post(sem_molo_hacker);
		}
		else {
			(*write_index)++;
			fprintf(out,"%d: %s: %d: waiting for boarding: %d: %d\n",(*write_index),proces,i,(*hacker),(*serf));
			sem_post(sem_memory);

			sem_post(sem_molo);
            
            //cakanie na vtup, hacker aj serf ma vlasny semafor
			if (person == 'H') sem_wait(sem_molo_hacker);
			if (person == 'S') sem_wait(sem_molo_serf);
			*clen='M';
	}
	return;		

}

/*
 * terminate
 * ukoncenie programu v pripade vyskytu chyby
 */ 
void terminate(){
	sem_free();
    shm_free();
	exit (2);
}
