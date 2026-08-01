#include "parser.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int parser(httpreq* HttpRequest,const char* buffer)
{
	char temp[255]; 
	char temp2[255];
	sscanf(buffer,"%15s %255s %15s",HttpRequest->method,HttpRequest->path,HttpRequest->version,temp);
	char* ptr = strstr(buffer,"Accept");
	sscanf(ptr,"%*[^:]:%254[^\r\n]",HttpRequest->content_type);
	fputs(HttpRequest->content_type,stdout);
	return 0;
}



