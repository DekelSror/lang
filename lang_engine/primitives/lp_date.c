#include <time.h>

#include "objmem.h"
#include "lp_date.h"


typedef struct {
    object_api_t* _api;
    time_t _value;
} date_impl_t;

object_t* date_create(void* value)
{
    date_impl_t* date = obj_mem();

    date->_api = &date_api;
    if (value != 0)
    {
        date->_value = *(time_t*)value;
    }
    else
    {
        date->_value = time(NULL);
    }


    return date;
}

object_t* date_ago(object_t* date, object_t* ago)
{
    
}


