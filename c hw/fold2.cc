 // fold2.cc
 // Riesenie IJC-DU2, priklad 1 b), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: g++ 4.7.3
 // .cc subor fold2.cc

 /* fold2.cc.c definiton*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
using namespace std;

//function to load arguments from command line, return index to argv for source, or -1 if error
int load_arguments(int argc, char *argv[], int * line_length, int * cut)
{
	int index=0,w=0;
	int c=*cut;
   for (int i=1; i < argc; i++){
     if (strcmp(argv[i], "-c") == 0) {
		 if (c == 0) { *cut =1; c=1; }
		   else return -1;
		}
		else
		if (strcmp(argv[i], "-w") == 0) {
			if (w != 0) { return -1; }
			
			i++;
			if (i < argc) {
				char* end;
                *line_length = strtol(argv[i], &end, 10);  
                if (*end) return -1; 
			}
			else return -1;
		   }
		   else 
		   if ( index == 0 ) { index = i; } 
		     else return -1;	   
   }
   
  return index;       
}


int main (int argc, char **argv) {
//variables	
  string line; 	
  string word;
  string source;
  int word_length;
  int space;
  int line_length=80;
  int position=0;
  int cut=0;
  int firstcut=0;
  string print_line;
  filebuf myfile;

  //load arguments
  int index=load_arguments(argc,argv,&line_length, &cut);
  if (index == -1){
	   cerr << "Nepodarilo sa nacitat argumenty \n";
	   return 1;
  }
  //source file was set, try to open and redirect as cin
  if (index != 0) {
  myfile.open (argv[index],ios::in);
  if (!myfile.is_open()) {
    cerr << "Could not open input file \n";
    return 1;
  } else {
    istream is(&myfile);
    cin.rdbuf(is.rdbuf());
  }
  }  
   
	   
  //read file by line
    while ( getline (cin,line) )
    {
		if (line.empty())
		{
			if (position != 0){
				cout << print_line << '\n';
				position=0;
			}
			cout << '\n';
			print_line="";
		}
		else{
		istringstream iss(line);
		//read line word by word
		while (iss >> word)
		{
			//check if word is first in line
			word_length=word.length();
			if (position == 0){
				space= 1;
			}else space=0;
			
			//if it fits line, add it
			if (position + word_length < line_length + space)
			{
				if (position != 0){
					print_line += ' ';
					position++;
				}
				print_line += word;
				position +=word_length;
			}else{
			
			//bigger then line, print to new line
			if (position != 0) cout << print_line << '\n';
			
			position=0;
			print_line=word;
			if (word_length > line_length)
			{
				//check if -c argument is set
				if (cut == 0){
				
				cout << print_line << '\n';
				print_line="";
			    }
			    else
			      {
					  if (firstcut == 0){
						  cerr << "slovo bolo orezane\n";
						  firstcut=1;
					  }
					  print_line.erase (line_length,word_length);  
					  cout << print_line << '\n';
				      print_line="";
				  }
			  
					  
			}else position=word_length;
			
		   }
			
		}
	  }
    }
    if (position !=0) cout << print_line << '\n'; //print buffer if is not empty

  if (index !=0) myfile.close();
  
  return 0;
}
