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

void table_free(table_t* table)
{
    free(table);
}

void vector_free(vector_t* vector)
{
    free(vector);
}

table_t* program_apis;
table_t* program_functions;

int prepare_objmem(void)
{
    program_apis = Table.create(dict_mem(20), 20);
    program_functions = Table.create(dict_mem(20), 20);

    return 0;
}

void clean_objmem(void)
{
    for (tentry_t* api = program_apis->_entries; api < program_apis->_entries + program_apis->_size; api++)
    {
        if (api->_value != (void*)-1)
        {
            obj_free(api->_value);
        }
    }

    for (tentry_t* fn = program_functions->_entries; fn < program_functions->_entries + program_functions->_size; fn++)
    {
        if (fn->_value != (void* )-1)
        {
            obj_free(fn->_value);
        }
    }

    table_free(program_apis);
    table_free(program_functions);
    
}