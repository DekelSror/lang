
#include "table.h"
#include "objmem.h"
#include "primitives.h"
#include "lp_dict.h"

static object_t* dict_create(void)
{
    object_t* this = obj_mem("dict");
    this->_api = &dict_api;
    this->_value = Table.create(); 

    return this;
}

static object_t* dict_subscribe(object_t* dict, object_t* expr)
{
    if (expr->_api != &string_api)
    {

    }

    const char* key = expr->_value;

    return Table.find(dict->_value, key);
}

object_api_t dict_api = { 0 };