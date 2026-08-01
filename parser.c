#include "parser.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int parser(httpreq* HttpRequest,const char* buffer)
{
	char temp[255]; 
	char temp2[255];
	sscanf(buffer,"%15s %255s %15s %1024s",HttpRequest->method,HttpRequest->path,HttpRequest->version,temp);
	//fputs(HttpRequest->method,stdout);
	//fputs(HttpRequest->path,stdout);
	//fputs(HttpRequest->version,stdout);
	//fputs(temp,stdout);
	char* ptr = strstr(buffer,"Accept");
	sscanf(ptr,"%30[^:]s %254[^/r/n]s",temp,temp2);
	fputs(temp,stdout); 
	fputs(temp2,stdout);
	return 0;
}



