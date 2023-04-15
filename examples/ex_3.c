#include <stdio.h>

#include "object.h"
#include "primitives.h"
#include "usertype.h"

/*
    fn fib(number n) -> number {
        if (n == 0) return 0
        if (n <= 2) return 1

        return fib(n - 1) + fib(n - 2)
    }

    run {

    }

*/

object_t* fn_fib_body(call_arg_t* args)
{
    static long literals[] = {0, 1, 2};

    object_t* locals[] = {
        number_api._create(literals + 0),
        number_api._create(literals + 1),
        number_api._create(literals + 2),
        0
    };

    object_t* n = args->_obj;
    if (n->_api->_ops.cmp_eq(n, locals[0]))
    {
        obj_free(locals[1]);
        obj_free(locals[2]);
        return locals[0];
    }
    if (n->_api->_ops.cmp_le(n, locals[2]))
    {
        obj_free(locals[0]);
        obj_free(locals[2]);
        return locals[1];
    }

    object_t* m1 = n->_api->_ops.subtract(n, locals[1]);
    object_t* m2 = n->_api->_ops.subtract(n, locals[2]);

    call_arg_t m1_args = {
        ._obj = m1,
        ._next = 0
    };

    call_arg_t m2_args = {
        ._obj = m2,
        ._next = 0
    };

    object_t* res_m1 = fn_fib_body(&m1_args);
    object_t* res_m2 = fn_fib_body(&m2_args);

    object_t* rv = number_api._ops.add(res_m1, res_m2);

    for (long i = 0; i < 3; i++)
    {
        obj_free(locals[i]);
    }
    
    obj_free(m1);
    obj_free(m2);
    obj_free(res_m1);
    obj_free(res_m2);

    return rv;
}

void prepare(void)
{
    prepare_objmem();
    prepare_primitives();
    prepare_usertype();
    
    fn_arg_t fib_args[] = {
        {
            ._name = "n",
            ._type = &number_api,
            ._default_val = 0
        }
    };

    add_function("fib", &number_api, fn_fib_body, 1, fib_args);
}

long fib(long n)
{
    if (n == 0) return 0;
    if (n <= 2) return 1;

    return fib(n - 1) + fib(n - 2);
}


struct number_impl 
{
    object_api_t* _api;
    long _val;
};

// 0 1 1 2 3 5 8 13 21 34
int main(void)
{
    static long literals[] = {8};
    prepare();

    lang_fn_t* fn_fib = Table.find(program_functions, "fib");

    object_t* locals[] = {
        number_api._create(literals + 0)
    };

    call_arg_t fn_fib_cargs = {
        ._obj = locals[0],
        ._next = 0
    };

    object_t* res = fn_call(fn_fib, &fn_fib_cargs);

    printf("fib of 8 is %ld\n", ((struct number_impl*)res)->_val);

    obj_free(locals[0]);
    obj_free(res);
    
    clean_objmem();

    return 0;
}

