#ifndef lang_object_memory_h
#define lang_object_memory_h

#include "vector.h"
#include "object.h"


void* obj_mem(void);
void* function_mem(long num_args);
void* list_mem(long size);
void* dict_mem(long size);
void* usertype_mem(void);

void obj_free(object_t*);

extern const table_t* program_functions;
extern const table_t* program_apis;

#endif // lang_object_memory_h