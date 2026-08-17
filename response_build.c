#include "parser.h"
#include "doc_prep.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int response_builder(char response[],httpreq* http_requests,char* mime,size_t content_length,char* payload)
{
	int header_length;
	if(content_length == FILE_NOT_FOUND)
	{
		header_length = sprintf(response,"HTTP/1.1 404 NOT FOUND");
		return header_length;
	}
	header_length = sprintf(response,"%s 200 OK\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n",http_requests->version,mime,content_length);
	return header_length;
}
