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
            b <- countries[.code == border]

            return {code: b.code, mutual_seas: .seas.intersect(b.seas)}
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

object_t* filter_by_code(call_arg_t* args)
{
    object_t* border = string_api._create();
    return args->_obj->_api->_ops.cmp_eq(args->_obj);
}

object_t* Country_method_borders_seas(call_arg_t* args)
{
    object_t* this = args->_obj;
    object_t* countries = args->_next->_obj;

    lang_fn_t* list_filter = Table.find(list_api._methods, "filter");

    call_arg_t args = {
        ._obj = countries,
        ._next = 0
    };

    object_t* uservar_b = fn_call(list_filter, args);

    object_t* res = dict_api._create(0);
}

int main(int argc, char const *argv[])
{
    create_usertype("Country");
    object_api_t* country_api = Table.find(user_types, "Country");

// attrs
    add_attr("Country", "name", &string_api, string_api._create("sovreign citizen"));
    add_attr("Country", "area", &number_api, 0);

// op overload
    add_binary_op("Country", add, &Country_op_add);

// methods
    fn_arg_t args[2] = {
        {
            ._name = "a",
            ._type = country_api,
            ._default_val = 0
        },
        {
            ._name = "b",
            ._type = country_api,
            ._default_val = 0
        }
    };

    add_function("Country_borders_seas", &list_api, &Country_method_borders_seas, 2, args);
    lang_fn_t* method = Table.find(program_functions, "Country_borders_seas");

    add_method("Country", "borders_seas", method);


    return 0;
}
