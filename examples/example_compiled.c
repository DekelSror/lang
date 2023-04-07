#include "table.h"
#include "object.h"
#include "vector.h"
#include "usertype.h"
#include "primitives.h"
#include "lp_function.h"

/*
usertype Country {

    --- attribute definitions
    name: string = 'sovreign citizen'
    code: string
    flagImage: string
    borders: string[]
    continent: string
    location: {lang: number, long: number, alt: number}
    area: number
    population: number
    seas: string[]
*/


/*
    --- operator overload
    operator lt(a: Country, b: Country) -> number {
        return a.area > b.area
    }

}
*/


/*
    --- method
    fn borders_seas(this/self, countries: Country[]) -> {code: string, mutual_seas: string[]} {
        return this.borders.map(border -> {code: string, mutual_seas: string[]} {
            const b <- countries[.code == border]

            return {code: b.code, mutual_seas: this.seas.intersect(b.seas)}
        })
    }
*/



/*
run {
    const countries: Country[] -< ...

    const albania <- countries[.name == 'Albania']


    albania.borders_seas(countries[albania.borders has .code]) 

}
*/

object_t* Country_op_add(const object_t* a, const object_t* b)
{
    return number_api._ops.add(a->_api->_access(a, "area"), b->_api->_access(b, "area"));
}

object_t* Country_method_borders_seas(call_arg_t* args)
{
    object_t* this = args->_obj;
    object_t* countries = args->_next->_obj;

}

int main(int argc, char const *argv[])
{
// create Country class
    object_api_t country_api;
    // country_api._name = "Country";
    Table.insert(user_types, "Country", &country_api);
    Vector.add(program_apis, &country_api);

// attrs
    add_attr("Country", "name", &string_api, string_api._create("sovreign citizen"));
    add_attr("Country", "area", &number_api, 0);

// define op override
    fn_arg_t cmp_add_b = {
        ._name = "b",
        ._type = "Country",
        ._default_val = 0,
        ._next = 0
    };

    fn_arg_t cmp_add_a = {
        ._name = "a",
        ._type = "Country",
        ._default_val = 0,
        ._next = &cmp_add_b
    };

    lang_fn_t op_cmp_add = {
        ._name = "Country_op_add",
        ._body = Country_op_add,
        ._args = &cmp_add_a,
        ._rv_type = "boolean"
    };

    add_binary_op("Country", add, &Country_op_add);

// methods
    fn_arg_t method_1_arg_2 = {
        ._name = "countries",
        ._type = "list",
        ._default_val = "",
        ._next = 0
    };

    fn_arg_t method_1_arg_1 = {
        ._name = "", // empty for this
        ._type = "Country",
        ._default_val = "", // empty for this
        ._next = &method_1_arg_2
    };

    lang_fn_t method_1 = {
        ._name = "border_seas",
        ._body = Country_method_borders_seas,
        ._rv_type = "list",
        ._args = &method_1_arg_1
    };

    add_method("Country", "border_seas", &method_1);


// run section
    object_t* local_1 = list_api._create(0);
    // set list elem type to Country
    local_1->_api->_set_attr(local_1, "elem_type", "Country");

    object_t* literal_1 = string_api._create("Albania");

    object_t attr_1 = {
        ._api = "subscribe_attr",
        ._value = ".name"
    };

    // my_list[.size > avg(my_list.map(.size))]
    // my_list[3 + 4]
    list_subscribe_expr_t subscribe_expr = {
        ._left = &attr_1,
        ._right = literal_1,
        ._op = "cmp_eq"
    };

    object_t subscribe_expr_obj = {
        ._value = &subscribe_expr
    };

    object_t* found = local_1->_api->_ops.subscribe(local_1, &subscribe_expr_obj);

    object_t* local_2 = country_api._copy(found);

    lang_fn_t* method_fn = Table.find(local_2->_api->_methods, "borders_seas");

    call_arg_t method_call_arg_2 = {
        ._obj = local_1,
        ._next = 0x0
    };

    call_arg_t method_call_arg_1 = {
        ._obj = local_2,
        ._next = &method_call_arg_2
    };

    fn_call(method_fn, &method_call_arg_1);



    return 0;
}
