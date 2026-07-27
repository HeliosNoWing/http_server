#include "doc_prep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

char* doc_prep(const char* path)
{
	FILE* ptr;
	char complete_path[256];
	char* file_buffer = (char*)malloc(sizeof(char)*4096);
	if(strlen(path) == 1){
		sprintf(complete_path,"%s","index.html"); 
	}
	else{
		sprintf(complete_path,"%s",path); // complete_path = /index.html
 	}
	//fputs(complete_path,stdout); 
	ptr = fopen(complete_path,"r");
	if(!ptr) fputs("couldnt find",stdout);
	fgets(file_buffer,sizeof(char)*4096,ptr);
	return file_buffer;
}

