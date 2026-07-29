#include "doc_prep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int doc_prep(const char* path, char* file_buffer)
{
	FILE* ptr;
	char complete_path[256];
	char* str_ptr = file_buffer;
	if(strlen(path) == 1){
		sprintf(complete_path,"%s","index.html"); 
	}
	else{
		sprintf(complete_path,"%s",path); // complete_path = /index.html
 	}
	//fputs(complete_path,stdout); 
	ptr = fopen(complete_path,"r");
	if(!ptr){
		fputs("couldnt find",stdout);
		return FILE_NOT_FOUND;
	}
	int i = 0;
	do
	{
		i += strlen(str_ptr);
	}
	while(fgets(&str_ptr[i],sizeof(char)*4096,ptr)) ; 
	fclose(ptr);
	return FILE_SUCCESS;
}

