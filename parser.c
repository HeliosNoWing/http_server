#include "parser.h"
#include <stdio.h> 

int parser(httpreq* HttpRequest,const char* buffer)
{
	sscanf(buffer,"%15s %255s %15s",HttpRequest->method,HttpRequest->path,HttpRequest->version);
	return 0;
}
