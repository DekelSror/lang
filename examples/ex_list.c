#include <stdio.h>

#include "primitives.h"
#include "usertype.h"

/*
    run {
        my_list <- [1, 2, 3]


        my_list[]
    }
*/

int simple_ex(void)
{
    static const double number_literals[] = {1.0, 2.0, 3.0};
    prepare_primitives();

    object_t* my_list = list_api._create(0);
    list_api._set_attr(my_list, "elem_type", &number_api);

    object_t* elems[] = {
        number_api._create(number_literals + 0),
        number_api._create(number_literals + 1),
        number_api._create(number_literals + 2),
    };

    list_api._init(my_list, elems);


    return 0;
}

/*
    run {
        my_list <- [
            fn (number x): number { x * 4},
            fn (number x): number { x * 5},
            fn (number x): number { x * 6},
        ]

        res_list <- my_list.map(fn (fn elem) {elem(100)})
    }
*/

static double number_literals[] = {4.0, 5.0, 6.0, 100.0};

object_t* elem_1(call_arg_t* args)
{
    object_t* factor = number_api._create(number_literals + 0);
    return number_api._ops.multiply(args->_obj, factor);
}

object_t* elem_2(call_arg_t* args)
{
    object_t* factor = number_api._create(number_literals + 1);
    return number_api._ops.multiply(args->_obj, factor);
}

object_t* elem_3(call_arg_t* args)
{
    object_t* factor = number_api._create(number_literals + 2);
    return number_api._ops.multiply(args->_obj, factor);
}

object_t* map_fn(call_arg_t* args)
{
    lang_fn_t* elem = args->_obj;
    object_t* factor = args->_next->_obj;

    call_arg_t call_args = {
        ._obj = factor,
        ._next = 0
    };

    return fn_call(elem, &call_args);
}

int ex2(void)
{
    // my_list <- ...
    object_t* my_list = list_api._create(0);
    list_api._set_attr(my_list, "elem_type", &function_api);

    // elem function definition
    fn_arg_t arg_x = {
        ._name = "x",
        ._type = &number_api,
        ._default_val = 0
    };
    
    add_function("elem_1", &number_api, elem_1, 1, &arg_x);
    add_function("elem_2", &number_api, elem_2, 1, &arg_x);
    add_function("elem_3", &number_api, elem_3, 1, &arg_x);

    lang_fn_t* elem_1_fn = Table.find(program_functions, "elem_1");
    lang_fn_t* elem_2_fn = Table.find(program_functions, "elem_2");
    lang_fn_t* elem_3_fn = Table.find(program_functions, "elem_3");

    fn_arg_t map_args[] = {
        {
            ._name = "elem",
            ._type = &function_api,
            ._default_val = 0
        },
        arg_x, 
    };

    object_t* elems[] = {
        elem_1_fn, elem_2_fn, elem_3_fn
    };

    list_api._init(my_list, elems);

    // res_list <- my_list.map(fn (fn elem) {elem(100)})

    // define inner function
    add_function("map_fn", &number_api, map_fn, 2, map_args);

    lang_fn_t* mapmapmap = Table.find(program_functions, "map_fn");

    typedef object_t*(*method_fn)(object_t*, lang_fn_t*, call_arg_t*);

    // call map method
    method_fn map_method = Table.find(list_api._methods, "map");

    call_arg_t cargs = {
        ._obj = number_api._create(number_literals + 3),
        ._next = 0
    };
    
    object_t* res_list = map_method(my_list, mapmapmap, &cargs);

    return 0;
}





