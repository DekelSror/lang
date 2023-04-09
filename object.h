#ifndef lang_object_h
#define lang_object_h

#include "table.h"

typedef char bool_t;

typedef struct lang_object_api_s object_api_t;

typedef struct lang_object_s
{
    // consider api_number that corresponds to apis vector index
    // this will free up 32 bits for gc and other purposes
    // while still allowing for 4 objects in a cache line
    object_api_t* _api;
    void* _value;
} object_t;


struct object
{
    unsigned short _api_index; // hack - save one for functions without really conforming
    char _object_type; // object, function, primitive (mainly for dict) ?
    char _marked; // use last bit (&0x1) for garbage collection
    int _future; // pad to 16 bytes
    void* _value;
};

/*
    object would be {
        ._api_index - index in object_api_t vector
        ._object_type - object
        ._value - bool / number / date are on the pointer
                - string, list, dict needs to be defined
                - usertype objects
    }

    fn would be {
        ._api_index - some magic number that indicates it's a function
        ._value - pointer (or index) to functions vector
    }
*/


typedef enum { 
    plus,
    minus,
    add,
    subtract,
    multiply,
    divide,
    mod,
    cmp_eq,
    cmp_lt,
    cmp_gt,
    cmp_le,
    cmp_ge,
    invoke,
    subscribe 
} object_ops_e;

typedef struct lang_operators_s
{
    object_t*(*plus)(const object_t*); // +a
    object_t*(*minus)(const object_t*); // -a
    //
    object_t*(*add)(const object_t* a, const object_t* b); // a + b
    object_t*(*subtract)(const object_t* a, const object_t* b); // a - b
    object_t*(*multiply)(const object_t* a, const object_t* b); // a * b
    object_t*(*divide)(const object_t* a, const object_t* b); // a / b
    object_t*(*mod)(const object_t* a, const object_t* b); // a % b
    //
    bool_t(*cmp_eq)(const object_t* a, const object_t* b); // a == b
    bool_t(*cmp_lt)(const object_t* a, const object_t* b); // a < b
    bool_t(*cmp_gt)(const object_t* a, const object_t* b); // a > b
    bool_t(*cmp_le)(const object_t* a, const object_t* b); // a <= b
    bool_t(*cmp_ge)(const object_t* a, const object_t* b); // a >= b
    //
    object_t*(*invoke)(object_t* obj); // a()
    object_t*(*subscribe)(object_t* obj, object_t* expr); //a[expr]
} operators_t;


struct lang_object_api_s
{
    char* _name;

    // customizable ops
    operators_t _ops;
    // create also initializes
    object_t*(*_create)(void* val);
    // user doesn't free
    void(*_destroy)(object_t*);
    //
    // core ops - cannot be customized
    // for copy operations
    object_t*(*_init)(object_t* raw, object_t* initializer);
    // cmp address
    bool_t(*_cmp_id)(const object_t* a, const object_t* b); // a is b
    object_t*(*_access)(const object_t* obj, const char* attr); // a.attr
    object_t*(*_set_attr)(object_t* obj, const char* attr_name, void* val);
    object_t*(*_copy)(const object_t* obj);
    //
    table_t* _methods;
    table_t* _attrs;
    //
} ;



bool_t cmp_obj_id(const object_t* a, const object_t* b);

#endif // lang_object_h