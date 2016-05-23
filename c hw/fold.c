 // fold.c
 // Riesenie IJC-DU2, priklad 1 a), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor fold.c

 /* fold.c definiton*/
 /* inspired by linux fold -s */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define line_limit 4096

//structure to pass easier variables
typedef struct {
	char buf[line_limit];
	char loaded_char;
	int position;
	int state;
	int print;
	int line;
	int arg_c;
	int chars_left;
	int first_word;
	char * input;
	
} BUFFER_STRUCT;

//prototypes

int load_arguments(int argc, char *argv[], BUFFER_STRUCT *buffer);
void new_line(BUFFER_STRUCT *buffer);
void print_array(BUFFER_STRUCT *buffer);
void white_char(BUFFER_STRUCT *buffer);
void on_word(BUFFER_STRUCT *buffer);
void print(BUFFER_STRUCT *buffer);


int main(int argc, char **argv)
{
	//initialization
	BUFFER_STRUCT buffer = {.loaded_char = 1, .position = 0, .state = 1, .print = 0, .line = 80, .arg_c = 0, .first_word = 1 };	 	
	FILE *fr;
	
	int error_arg;
	int stream=0;
	int over_limit=0;
	
	 if ( ( error_arg=load_arguments(argc, argv, &buffer)) == 1 ){
	    fputs("Program bol spusteny s chybnymi parametrami\n", stderr);
		return 1;   
	   }
    
    if ( strcmp(buffer.input, "stdin") != 0 ) {	
      if ((fr=fopen(buffer.input,"r"))==NULL){
		fprintf( stderr, "Subor \"%s\" sa nepodarilo otvorit\n",buffer.input );
        return 1;
	   }
	   stream=3;   
	}
    
    
    while (buffer.state != 0){  //iterate until EOF
    
    if (buffer.loaded_char == EOF) buffer.state=0;
    
    //load  word char by char
    if (stream == 0) { buffer.loaded_char=fgetc(stdin); }
      else
      buffer.loaded_char=fgetc(fr);
    
    if (buffer.loaded_char == EOF) {   //if we reach eof
		if (buffer.position != 0){
			print(&buffer);
			buffer.state=0;
		}
	   }
    else
    if ( !(isspace(buffer.loaded_char)) ) {             //read chars to array
		if (buffer.position > line_limit){
			if (over_limit == 0){
				over_limit=1;
				fputs("Slovo je vecsie akko 4096 znakov", stderr);}
		}
		else{
		buffer.first_word=0;
		buffer.buf[buffer.position]=buffer.loaded_char;
		buffer.position=buffer.position +1;
	    }
	}
	else
	  if (buffer.position !=0) {
		  buffer.first_word=0;
		  print(&buffer);
		  buffer.position=0;
	  }
	  if (buffer.loaded_char == '\n') {        //print empty lines
			if ( buffer.first_word == 0){
				buffer.first_word = 1;
			}
			else 
			  if (buffer.first_word == 1){
				  buffer.first_word =2;
				  print(&buffer);
				  buffer.first_word =1;
			  }
		  }
  }
    

	if (stream == 3) fclose(fr);
	printf("\n");
	return 0;
}

void print(BUFFER_STRUCT *buffer)  //function to print and process buffer
{
    
    if (buffer-> arg_c == 1){              //on first longer word print to std err 
		if (buffer->position > buffer->line ) {
			 fputs("Doslo k orezaniu slova", stderr); 
			 buffer->arg_c = 2;
		 }
	 }
	
    
    if (buffer->first_word == 2){             //new line
		if (buffer->chars_left != buffer->line ){
			putchar('\n');
			putchar('\n');
			buffer->chars_left=buffer->line;
		}
		else {
			putchar('\n');
			buffer->chars_left=buffer->line;
		}
	}
	else    //first word on line
	  if (buffer->chars_left == buffer->line ){
		 print_array(buffer);
         buffer->chars_left=buffer->chars_left - buffer->position;
	  }
	  else
	    if (buffer->chars_left > buffer->position){  //print space and then word
			putchar(' ');
			print_array(buffer);
			buffer->chars_left = buffer->chars_left - buffer->position -1;
		}
		else {
			putchar('\n');
			print_array(buffer);
			if (buffer->position < buffer->line){
				buffer->chars_left=buffer->line - buffer->position;}
				else buffer->chars_left=0;
			}
}


void print_array(BUFFER_STRUCT *buffer) //function to print buffer
{
	if (buffer->arg_c > 0){
	  for (int i=0; ( (i < buffer->position) && (i < buffer->line) ); i++)
	    {
		  putchar(buffer->buf[i]);
	    }	
	}
	else
    for (int i=0; i < buffer->position; i++)
	 {
		putchar(buffer->buf[i]);
	 }  
}


int load_arguments(int argc, char *argv[], BUFFER_STRUCT *buffer) //load arguments function
{
	int index=0,w=0;
   for (int i=1; i < argc; i++){
     if (strcmp(argv[i], "-c") == 0) {
		 if (buffer->arg_c == 0) { buffer->arg_c =1; }
		   else return 1;
		}
		else
		if (strcmp(argv[i], "-w") == 0) {
			if (w != 0) { return 1; }
			
			i++;
			if (i < argc) {
				char* end;
                buffer->line = strtol(argv[i], &end, 10);  
                if (*end) return 1; 
                if  ( (buffer->line < 1) || (buffer->line > line_limit ) ) return 1;
			}
			else return 1;
		   }
		   else 
		   if ( index == 0 ) { index = i; } 
		     else return 1;	   
   }
   
   buffer->chars_left=buffer->line;
   if (index == 0) {buffer->input="stdin";}
   else buffer->input=argv[index];
   
  return 0;       
}
