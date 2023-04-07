#include "vector.h"
#include "objmem.h"

#include "lp_function.h"

#include "lp_number.h"
#include "lp_bool.h"

#include "lp_list.h"


static object_t* create_list(object_t* initializer)
{
    object_t* this = obj_mem("list");
    this->_api = &list_api;
    long initial_length = 0;
    list_api._set_attr(this, "length", &initial_length);

    if (initializer != 0)
    {
        return list_init(this, initializer);
    }

    this->_value = Vector.create();

    return this;
}

static object_t* free_list(object_t* list)
{
    Vector.destroy(list->_value);
    obj_free(list);
}

static object_t* list_subscribe_index(object_t* list, double index)
{
    long ii = (long)index;

    object_t* len = Table.find(list_api._attrs, "length");

    if (ii >= (long)*(double*)(len->_value) || ii < 0) 
    {
        // return empty obj
    }

    return (object_t*)Vector.at(list->_value, ii);
}

static object_t* list_method_filter(const object_t* list, lang_fn_t* fn, call_arg_t* args)
{
    if (fn->_rv_type != &bool_api)
    {
        // throw
    }

    vector_t* res_value = Vector.create();

    for (long i = 0; i < Vector.size(list->_value); i++)
    {
        object_t* elem = (object_t*)Vector.at(list->_value, i);

        call_arg_t fn_arg = {
            ._obj = elem,
            ._next = args
        };

        object_t* fn_res = fn_call(fn, &fn_arg);

        if (is_true(fn_res))
        {
            Vector.add(res_value, elem);
        }
    }

    object_t* rv = create_list(0);
    rv->_value = res_value;

    return rv;
}

static object_t* list_subscribe(object_t* list, object_t* expr)
{
    // two possibilities after brackets evaluated
    // number object or filter (future - range [1:99])
    if (expr->_api == &number_api)
    {
        return list_subscribe_index(list, *(double*)expr->_value);
    }

    // my_list[.age > 20]
    // fn(elem) return elem._api._ops._gt(elem, 20);
    if (expr->_api == &function_api)
    {
        called_fn_t* filter = expr->_value;
        return list_method_filter(list, filter->_fn, filter->_args);
    }
}




static object_t* list_init(object_t* this, object_t* _raw_list) {
    // check the right side exprerssion
    // if another list, call copy
    // if a temp list (such as .map of another list) use the temp
// initialize from literal -> null-terminated C array of pointers
    object_t** raw_list = (object_t**)_raw_list;
    int size = 0;

    for (object_t* elem = raw_list; elem != 0; elem++)
    {
        Vector.add(this->_value, elem);
        size++;
    }

    return this;
}

int lp_list_prepare(void) {
    Table.insert(list_api._attrs, "length", &number_api);

    Table.insert(list_api._methods, "map", 0);
    Table.insert(list_api._methods, "filter", 0);
    Table.insert(list_api._methods, "sort", 0);
    Table.insert(list_api._methods, "reduce", 0);

    return 0;
}

object_api_t list_api = { 
    ._name = "list",
    ._init = list_init,
    ._ops = {
        .subscribe = list_subscribe
    }
};
