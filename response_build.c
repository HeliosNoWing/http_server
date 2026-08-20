#include "parser.h"
#include "doc_prep.h"
#include <stdio.h>
#include <stddef.h>

int response_builder(char response[],httpreq* http_requests,char* mime,payload* resp)
{
	int header_length;
	int resp_code = resp->response_code;
	printf("%d",resp_code);
	switch(resp_code)
	{
		case FILE_FOUND:
			break;
		case FILE_NOT_FOUND:
			header_length = sprintf(response,"HTTP/1.1 404 NOT FOUND");
			return header_length;
		case INVALID_REQ:
			header_length = sprintf(response,"HTTP/1.1 400 BAD REQUEST");
			return header_length;
		case REQ_NOT_ALLOWED:
			header_length = sprintf(response,"HTTP/1.1 405 NOT ALLOWED");
		 	return header_length;
		default:
			header_length = sprintf(response,"HTTP/1.1 500 INTERNAL SERVER ERROR");
			return header_length;
	}
	header_length = sprintf(response,"%s 200 OK\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n",http_requests->version,mime,resp->content_length);
	return header_length;
}
