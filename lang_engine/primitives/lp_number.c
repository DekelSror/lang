#include "objmem.h"

#include "lp_number.h"

typedef struct
{
    object_api_t* _api;
    double _value;
} number_impl_t;

static object_t* create_number_literal(double val)
{
    object_t* obj = (object_t*)obj_mem();
    obj->_api = &number_api;
    ((number_impl_t*)obj)->_value = val;

    return obj;
}

static object_t* create_number(void* val)
{
    return create_number_literal(*(double*)val);
}


static object_t* number_add(const object_t* a, const object_t* b)
{
    number_impl_t* n1 = (number_impl_t*)a;
    number_impl_t* n2 = (number_impl_t*)b;
    
    double add_val = n1->_value + n2->_value;

    return create_number_literal(add_val);
}

static object_t* number_subtract(const object_t* a, const object_t* b)
{
    number_impl_t* n1 = (number_impl_t*)a;
    number_impl_t* n2 = (number_impl_t*)b;
    
    double add_val = n1->_value - n2->_value;

    return create_number_literal(add_val);
}

static object_t* number_plus(const object_t* num)
{
    double plus_val = +(*(double*)num->_value);
    return create_number_literal(plus_val);
}

static bool_t number_gt(const object_t* a, const object_t* b)
{
    return ((number_impl_t*)a)->_value > ((number_impl_t*)b)->_value;
}

static bool_t number_lt(const object_t* a, const object_t* b)
{
    return ((number_impl_t*)a)->_value < ((number_impl_t*)b)->_value;
}

static bool_t number_ge(const object_t* a, const object_t* b)
{
    return ((number_impl_t*)a)->_value >= ((number_impl_t*)b)->_value;
}

static bool_t number_le(const object_t* a, const object_t* b)
{
    return ((number_impl_t*)a)->_value <= ((number_impl_t*)b)->_value;
}

static bool_t number_eq(const object_t* a, const object_t* b)
{
    return ((number_impl_t*)a)->_value == ((number_impl_t*)b)->_value;
}



static const operators_t number_ops = {
    .plus = number_plus,
    .minus = 0x0,
    .add = number_add,
    .subtract = number_subtract,
    .multiply = 0x0,
    .divide = 0x0,
    .mod = 0x0,
    .cmp_eq = number_eq,
    .cmp_lt = number_lt,
    .cmp_gt = number_gt,
    .cmp_le = number_le,
    .cmp_ge = number_ge,
    .invoke = 0x0,
    .subscribe = 0x0
};

object_api_t number_api;

int lp_number_prepare(void) {
    number_api._ops = number_ops;
    number_api._name = "number";
    number_api._create = create_number;
    number_api._destroy = obj_free;
    number_api._cmp_id = cmp_obj_id;

    // Table.insert(number_api._methods, "floor", 0);

    return 0;
}

// end number