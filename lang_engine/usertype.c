#include "objmem.h"
#include "table.h"
#include "mem_utils.h"
#include "usertype.h"

static char user_types_mem[4096] = { 0 };
table_t* user_types;

int create_usertype(char* name)
{
    object_api_t* api = usertype_mem();
    api->_attrs = dict_mem(20);
    api->_methods = dict_mem(20);
    api->_name = name;

    return Table.insert(user_types, name, api);
}

int add_attr(const char* type, const char* attr_name, const object_api_t* attr_api, object_t* default_val)
{
    object_api_t* api = Table.find(user_types, type);
    
    return Table.insert(api->_attrs, attr_name, attr_api);
}

int add_method(const char* type, const char* method_name, lang_fn_t* fn)
{
    object_api_t* api = Table.find(user_types, type);

    return Table.insert(api->_methods, method_name, fn);
}

int add_unary_op(const char* type, object_ops_e op, unary_op_fn fn)
{
    object_api_t* api = Table.find(user_types, type);

    switch (op)
    {
    case plus:
        api->_ops.plus = fn;
        break;
    case minus:
        api->_ops.minus = fn;
        break;
    default:
        break;
    }
}

int add_binary_op(const char* type, object_ops_e op, binary_op_fn fn)
{
    object_api_t* api = Table.find(user_types, type);

    switch (op)
    {
    case add:
        api->_ops.add = fn;
        break;
    
    case subtract:
        api->_ops.subtract = fn;
        break;
    
    case multiply:
        api->_ops.multiply = fn;
        break;
    
    case divide:
        api->_ops.divide = fn;
        break;
    
    case mod:
        api->_ops.mod = fn;
        break;
    default:
        break;
    }

}

int add_cmp_op(const char* type, object_ops_e op, cmp_op_fn fn)
{
    object_api_t* api = Table.find(user_types, type);
    
    switch (op)
    {
    case cmp_eq:
        api->_ops.cmp_eq = fn;
        break;
    
    case cmp_ge:
        api->_ops.cmp_ge = fn;
        break;
    
    case cmp_gt:
        api->_ops.cmp_gt = fn;
        break;
    
    case cmp_le:
        api->_ops.cmp_le = fn;
        break;
    
    case cmp_lt:
        api->_ops.cmp_lt = fn;
        break;
    
    default:
        break;
    }
}

int add_function(const char* fn_name, object_api_t* rv_type, fn_body_t body, long num_args, fn_arg_t* args)
{
    lang_fn_t* fn = function_mem(num_args);

    fn->_name = fn_name;
    fn->_rv_type = rv_type;
    fn->_body = body;
    fn->_num_args = num_args;

    Memutils.move(fn->_args, args, sizeof(fn_arg_t) * num_args);
    
    return Table.insert(program_functions, fn_name, fn);
}

int prepare_usertype(void)
{
    user_types = Table.create(user_types_mem, 20);


    return 0;
}


int clean_usertype(void)
{
    table_free(user_types);
}