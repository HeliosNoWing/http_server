#include "doc_prep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define MAX_PATH_SIZE 256

size_t doc_prep(const char* path, char* file_buffer)
{
	FILE* ptr;
	char* jky = file_buffer;
	char complete_path[MAX_PATH_SIZE];
	if(strlen(path) == 1){
		sprintf(complete_path,"%s","index.html"); 
	}
	else{
		sprintf(complete_path,"%s",path); // complete_path = /index.html
 	}
	//fputs(complete_path,stdout); 
	ptr = fopen(complete_path,"rb");
	if(!ptr){
		fputs("couldnt find",stdout);
		return FILE_NOT_FOUND;
	}
	size_t n = 0;
	size_t temp = 0;
	do{
		temp = fread(jky,1,100,ptr);
		jky+=temp;
		n+=temp;
	}while(temp);
	fclose(ptr);
	return n;
}

