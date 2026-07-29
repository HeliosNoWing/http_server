#include "parser.h"
#include <stdio.h> 


int parser(httpreq* HttpRequest,const char* buffer)
{
	sscanf(buffer,"%15s %255s %15s",HttpRequest->method,HttpRequest->path,HttpRequest->version);
	fputs(buffer,stdout);
	return 0;
}



