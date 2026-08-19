#include "doc_prep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define MAX_PATH_SIZE 256
#define REQ_NOT_ALLOWED -3
#define INVALID_REQ -2
#define FILE_NOT_FOUND -1
void doc_prep(httpreq* request,payload* resp)
{
	FILE* ptr;
	char* jky = resp->file_buffer;
	char complete_path[MAX_PATH_SIZE];
	char methods[5][6] = {"GET","HEAD","POST","PUT","DELETE"}; //POST PUT DELETE are in not allowed
	char Mehtods_Not_Allowed[3][6] = {"POST","PUT","DELETE"};
	if(strlen(request->path) == 1)
	{
		sprintf(complete_path,"%s","index.html");
	}
	else
	{
		sprintf(complete_path,"%s",request->path); // complete_path = /index.html
 	}

	for(int i = 0; i<5; i++)
	{
		if(strcmp(request->method,methods[i]) == 0)
		{
			if(i == 2 || i == 3 || i == 4)
			{
				sprintf(complete_path,"%s","REQ_NOT_ALLOWED.html"); 
				resp->response_code = REQ_NOT_ALLOWED;
			}
			break;
		}
		sprintf(complete_path,"%s","INVALID_REQUEST.html");
		resp->response_code = INVALID_REQ;
	}

	ptr = fopen(complete_path,"rb");
	fputs(complete_path,stdout);
	if(!ptr)
	{
		fputs("couldnt find",stdout);
		ptr = fopen("file_not_found.html","rb");
		resp->response_code = FILE_NOT_FOUND;
	}

	size_t temp = 0;
	do{
		temp = fread(jky,1,100,ptr);
		jky+=temp;
		resp->content_length+=temp;
	}while(temp);

	fclose(ptr);
	return;
}

