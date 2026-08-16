#ifndef RESP_B_H
#define RESP_B_H
#include <stddef.h>
#include "parser.h"
void response_builder(char response[],httpreq* http_requests,char* mime,size_t content_length,char* payload);
#endif
