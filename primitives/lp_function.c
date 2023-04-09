

#include "lp_function.h"


void validate_args(lang_fn_t* fn, call_arg_t* call_args)
{
    call_arg_t* call_arg = call_args;
    
    for (long i = 0; i < fn->_num_args; i++)
    {
        fn_arg_t* fn_arg = fn->_args + i;

        if (call_arg == 0)
        {
            // less args than expected 
            break;
        }

        if (fn_arg->_type != call_arg->_obj->_api)
        {
            // this is a mismatch
        }


        // check nullables and default vals
        call_arg = call_arg->_next;
    }

    if (call_arg != 0)
    {
        // more args than expected
    }
}


object_t* fn_call(lang_fn_t* fn, call_arg_t* args)
{
    validate_args(fn, args);
    return fn->_body(args); 
}


object_api_t function_api = {
    ._name = "function"
};