#include "mime_chk.h" 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

char* mime_extract(char* file_path)
{
	char*s = (char*)malloc(sizeof(char)*1);
	if(!strcmp(file_path,"/")) return ".html";
	sscanf(file_path,"%*[^.].%10s",s);
	return s;
}
char* mime_lookup(char* mime)
{
	return"";
} 
