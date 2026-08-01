#ifndef DOC_PREP_H
#define DOC_PREP_H
#define FILE_NOT_FOUND -1
#define FILE_SUCCESS 1

#include <stddef.h>
size_t doc_prep(const char* path, char* file_buffer);

#endif
