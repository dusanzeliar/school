 // io.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor io.c

 /* io.c definiton*/
 /* gets one word from file, skipps white chars */ 


#include <ctype.h>
#include <stdio.h>

#define max_limit 127

int fgetw(char *s, int max, FILE *f)
{
        if (max>max_limit) max=max_limit;
        max--; //decrement max to be on index level
	if (f == NULL || max < 1){  //check pointer and max value
		s[0]=0;
		return EOF;
	}
	char c;
	int position=0;
	
	while ((c = fgetc(f)) != EOF && isspace(c)); //skip white chars
	if (c == EOF){
		s[0]=0;
		return EOF;
	}
	
	int over_limit=0;
	
	do   //read file char by char
	{
		if (position < max){
		    s[position]=c;
		    position++;
		} 
		else over_limit=1;
		
		c=fgetc(f);	
	}
	while (c != EOF && !(isspace(c)));  //until end of file or white char
	
	s[position]=0;
	
	if (over_limit ==  1) return ++position; // if word is over limit, return +1 bigger value (for error print)
	
	if (c == EOF) {return EOF;} 
	else return position;
	
}
