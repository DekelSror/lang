#include <stdlib.h> // malloc, free


#include "lp_function.h"
#include "objmem.h"


void* list_mem(long size)
{
    return malloc(sizeof(vector_t) + size * sizeof(void*));
}

void* dict_mem(long size)
{
    return malloc(sizeof(table_t) + size * sizeof(tentry_t));
}

void* function_mem(long num_args)
{
    return malloc(sizeof(lang_fn_t) + sizeof(fn_arg_t) * num_args);
}

void* obj_mem(void)
{
    return malloc(sizeof(object_t));
}

void* usertype_mem(void)
{
    return malloc(sizeof(object_api_t));
}


void obj_free(object_t* obj)
{
    free(obj);
}