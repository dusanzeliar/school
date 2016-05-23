 // hash_function.c
 // Riesenie IJC-DU2, priklad 2), 28.4.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 // Přeloženo: gcc 4.6.4
 // .c subor hash_function.c

 /* hash_function.c definiton*/
 /* process string and returns index to hash table*/ 


unsigned int hash_function(const char *str, unsigned htab_size) 
{
	  unsigned int h=0;
	  const unsigned char *p;
	  for(p=(const unsigned char*)str; *p!='\0'; p++)
	     h = 65599*h + *p; 
	  return h % htab_size; 
}
