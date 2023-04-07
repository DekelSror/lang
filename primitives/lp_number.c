#include "objmem.h"

#include "lp_number.h"

typedef struct
{
    object_api_t* _api;
    double _value;
} number_impl_t;

static object_t* create_number_literal(double val)
{
    object_t* obj = (object_t*)obj_mem("number");
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

static object_t* number_plus(const object_t* num)
{
    double plus_val = +(*(double*)num->_value);
    return create_number_literal(plus_val);
}

static bool_t number_gt(const object_t* a, const object_t* b)
{
    return *(double*)a > *(double*)b;
}

static bool_t number_lt(const object_t* a, const object_t* b)
{
    return *(double*)a < *(double*)b;
}

static const operators_t number_ops = {
    .plus = number_plus,
    .minus = 0x0,
    .add = number_add,
    .subtract = 0x0,
    .multiply = 0x0,
    .divide = 0x0,
    .mod = 0x0,
    .cmp_eq = 0x0,
    .cmp_lt = number_lt,
    .cmp_gt = number_gt,
    .invoke = 0x0,
    .subscribe = 0x0
};

object_api_t number_api = {
    ._name = "number",
    ._ops = 0,
    ._create = create_number,
    ._destroy = obj_free,
    ._cmp_id = cmp_obj_id,
    ._access = 0x0,
    ._set_attr = 0x0,
    ._copy = 0x0,
    ._methods = 0x0,
    ._attrs = 0x0
};

int lp_number_prepare(void) {
    number_api._ops = number_ops;

    // Table.insert(number_api._methods, "floor", 0);

    return 0;
}

// end number