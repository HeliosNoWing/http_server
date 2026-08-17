#ifndef RESP_B_H
#define RESP_B_H
#include <stddef.h>
#include "parser.h"
int response_builder(char response[],httpreq* http_requests,char* mime,size_t content_length,char* payload);
void payload_process();
#endif
