#include <stdlib.h> // malloc, free

#include "objmem.h"


static void* list_mem(long size)
{
    return malloc(sizeof(vector_t) + size * sizeof(void*));
}

static void* function_mem(void)
{
    
}

void* obj_mem(objtype_e objtype)
{
    switch (objtype)
    {
    case mem_primitive:
        return;
    case mem_function:
        return;
    case mem_list:
        return;
    case mem_dict:
        return;
    case mem_usertype:
        return malloc(sizeof(object_t));
    default:
        return 0;
    }
}



void obj_free(object_t* obj)
{
    free(obj);
}