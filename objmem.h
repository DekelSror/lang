#ifndef lang_object_memory_h
#define lang_object_memory_h

#include "vector.h"
#include "object.h"

const char objtype_primitive = 0;
const char objtype_list = 1;
const char objtype_dict = 2;
const char objtype_usertype = 3;

typedef enum { mem_primitive, mem_function, mem_list, mem_dict, mem_usertype } objtype_e;

void* obj_mem(objtype_e objtype);

void* more_mem(objtype_e objtype);

void obj_free(object_t*);

extern const vector_t* program_functions;
extern const vector_t* program_apis;

#endif // lang_object_memory_h