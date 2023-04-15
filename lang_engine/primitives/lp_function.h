#ifndef lang_primitives_function_h
#define lang_primitives_function_h

#include "object.h"

typedef struct fn_arg_s fn_arg_t;
typedef struct call_arg_s call_arg_t;
typedef object_t*(*fn_body_t)(call_arg_t* args);

struct fn_arg_s
{
    const char* _name;
    object_api_t* _type;
    object_t* _default_val;
};

typedef struct
{
    const char* _name;
    object_api_t* _rv_type;
    fn_body_t _body;
    long _num_args;
    fn_arg_t _args[];
} lang_fn_t;


struct call_arg_s
{
    object_t* _obj;
    call_arg_t* _next;
};


typedef struct 
{
    lang_fn_t* _fn;
    call_arg_t* _args;
} called_fn_t;

object_t* fn_call(lang_fn_t* fn, call_arg_t* args);

extern object_api_t function_api;

#endif // lang_primitives_function_h