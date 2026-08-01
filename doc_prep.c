#include "doc_prep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define PATH_SIZE 256

size_t doc_prep(const char* path, char* file_buffer)
{
	FILE* ptr;
	char complete_path[PATH_SIZE];
	char* temp_char_buffer = (char*)malloc(sizeof(char)*PATH_SIZE);
	char* jky = file_buffer;
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
	size_t n = fread(temp_char_buffer,1,100,ptr);
	memcpy(file_buffer,temp_char_buffer,n);
	fclose(ptr);
	return n;
}

