#include "parser.h"
#include "doc_prep.h"
#include <stdio.h>
#include <stddef.h>

int response_builder(char response[],httpreq* http_requests,char* mime,payload* resp)
{
	int header_length;
	int resp_code = resp->response_code;
	char temp[100];
	printf("%d",resp_code);
	switch(resp_code)
	{
		case FILE_FOUND:
			sprintf(temp,"HTTP/1.1 200 OK");
			break;
		case FILE_NOT_FOUND:
			sprintf(temp,"HTTP/1.1 404 NOT FOUND");
			break;
		case INVALID_REQ:
			sprintf(temp,"HTTP/1.1 400 BAD REQUEST");
			break;
		case REQ_NOT_ALLOWED:
			sprintf(temp,"HTTP/1.1 405 NOT ALLOWED");
		 	break;
		default:
			sprintf(temp,"HTTP/1.1 500 INTERNAL SERVER ERROR");
			break;
	}
	header_length = sprintf(response,"%s\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n",temp,mime,resp->content_length);
	return header_length;
}
