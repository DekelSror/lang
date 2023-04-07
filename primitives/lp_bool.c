#include "lp_bool.h"

const object_t* lang_true = (object_t*)1;
const object_t* lang_false = (object_t*)0;

bool_t is_true(const object_t* obj)
{
    if (obj == &lang_true)
    {
        // object is actually a opinter to lang_true (literals?)
        return 1;
    }

    if (obj->_api == &bool_api && obj->_value == &lang_true)
    {
        // object is a proper bool object and its value is set to lang_true
        return 1;
    }

    return 0;
}


object_api_t bool_api = {
    ._name = "bool",
};