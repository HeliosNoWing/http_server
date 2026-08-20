#ifndef DOC_PREP_H
#define DOC_PREP_H
#define FILE_NOT_FOUND -1
#define INVALID_REQ -2
#define REQ_NOT_ALLOWED -3
#define FILE_FOUND -44
#include <stddef.h>
#include "parser.h"
typedef struct payload{
	char* file_buffer;
	int response_code;
	size_t content_length;
}payload;
void doc_prep(httpreq* request, payload*  response);

#endif
