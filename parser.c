#include "parser.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int parser(httpreq* HttpRequest,const char* buffer)
{
	sscanf(buffer,"%15s %255s %15s",HttpRequest->method,HttpRequest->path,HttpRequest->version);
	return 0;
}
char* doc_prep(const char* path){
	FILE* ptr;
	char complete_path[1000];
	char* file_buffer = (char*)malloc(sizeof(char)*4096);
	if(strlen(path) == 1) sprintf(complete_path,"%s","index.html"); 
	else sprintf(complete_path,"%s",path); // complete_path = /index.html 
	//fputs(complete_path,stdout); 
	ptr = fopen(complete_path,"r");
	if(!ptr) fputs("couldnt find",stdout);
	fgets(file_buffer,sizeof(char)*4096,ptr);
	fputs(file_buffer,stdout);
	return file_buffer;
}

