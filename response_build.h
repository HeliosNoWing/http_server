#ifndef RESP_B_H
#define RESP_B_H
#include <stddef.h>
#include "parser.h"
#include "doc_prep.h"
int response_builder(char response[],httpreq* http_requests,char* mime,payload* resp);
#endif
