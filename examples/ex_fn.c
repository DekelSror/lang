#include <stdio.h>
#include "primitives.h"
#include "lp_function.h"
#include "usertype.h"

/*
    fn my_func (number a, number b) -> number {
        a - b
    }

    run {
        my_func(10, 20)
    }
*/




void prepare()
{
    prepare_primitives();
}


object_t* my_func(call_arg_t* call_args)
{
    object_t* a = call_args->_obj;
    object_t* b = call_args->_next->_obj;

    return a->_api->_ops.add(a, b);
}

typedef struct
{
    object_api_t* _api;
    double _value;
} number_impl_t;

int main(void)
{
    prepare();
// define my_func
    fn_arg_t args[2] = {
        {
            ._name = "a",
            ._type = &number_api,
            ._default_val = 0,
        },
        {
            ._name = "b",
            ._type = &number_api,
            ._default_val = 0,
        }
    };


// register function
    add_function("my_func", &number_api, &my_func, 2, args);
    
// call my_func
    double nums[2] = {10, 20};

    object_t* numa = number_api._create(nums);
    object_t* numb = number_api._create(nums + 1);

    call_arg_t carg2 = {
        ._obj = numb,
        ._next = 0
    };

    call_arg_t carg1 = {
        ._obj = numa,
        ._next = &carg2
    };

    lang_fn_t* fn = Table.find(program_functions, "my_func");

    object_t* res = fn_call(fn, &carg1);

    number_impl_t* dres = (number_impl_t*)res;

    printf("res is %lf \n", dres->_value);
    
    return 0;
}
