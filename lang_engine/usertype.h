#ifndef lang_user_type_h
#define lang_user_type_h

#include "object.h"
#include "lp_function.h"


// adds type to user types table. Initializes all ops to NULL
int create_usertype(char* name);


int add_attr(const char* type, const char* attr_name, const object_api_t* attr_api, object_t* default_val);

int add_function(const char* fn_name, object_api_t* rv_type, fn_body_t body, long num_args, fn_arg_t* args);
int add_method(const char* type, const char* method_name, lang_fn_t* fn);


typedef object_t*(*unary_op_fn)(const object_t*);
typedef object_t*(*binary_op_fn)(const object_t*, const object_t*);
typedef bool_t(*cmp_op_fn)(const object_t*, const object_t*);

int add_unary_op(const char* type, object_ops_e op, unary_op_fn fn);

int add_binary_op(const char* type, object_ops_e op, binary_op_fn);

int add_cmp_op(const char* type, object_ops_e op, cmp_op_fn fn);

int prepare_usertype(void);

extern table_t* user_types;


#endif // lang_user_type_h