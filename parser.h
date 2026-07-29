#ifndef PARSER_H
#define PARSER_H

typedef struct {
	char method[16];
	char path[256];
	char version[16];
}httpreq;

int parser(httpreq* HttpRequest, const char* buffer);
#endif

