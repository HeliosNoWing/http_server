#include "parser.h"
#include "doc_prep.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void response_builder(char response[],httpreq* http_requests,char* mime,size_t content_length,char* payload)
{
	if(content_length == FILE_NOT_FOUND)
	{
		sprintf(response,"HTTP/1.1 404 NOT FOUND");
	}
	sprintf(response,"%s 200 OK \r\nContent-type = %s \r\nContent-length = %zu \r\n\r\n%s",http_requests->version,mime,content_length,payload);
}  
