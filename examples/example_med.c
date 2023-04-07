#include "table.h"

#include "object.h"
#include "primitives.h"
#include "usertype.h"

#include "compiler.h"

/*
usertype Person {
    name: string = "Steve"
    age: number
}

people: Person[] <- [
    {name: 'Abe', age: 94},
    {name: 'Lit', age: 20},
    {name: 'Dob', age: 4},
    {name: 'Fior', age: 53},
]

run {
    // people older than avg
    // hard - people[.age > avg(people.map(.age))]
    people[.age > 20)]

    // all names in one string
    people.reduce(res, person -> number {
        return res + person.name + ' '
    })
}
*/


object_t* people;

void prepare() {
// Person usertype
    object_api_t person_api;
    person_api._name = "Person";
    
    Table.insert(user_types, "Person", &person_api);

    add_attr("Person", "name", &string_api, "Steve");
    add_attr("Person", "age", &number_api, 0);
    
// people list
    people = list_api._create(0);
    list_api._set_attr(people, "elem-type", "Person");

    double ages[] = {94, 20, 4, 53};

    object_t* p1 = person_api._create(0);
    person_api._set_attr(p1, "name", "Abe");
    person_api._set_attr(p1, "age", number_api._create(ages));

    object_t* p2 = person_api._create(0);
    person_api._set_attr(p2, "name", "Lit");
    person_api._set_attr(p2, "age", number_api._create(ages + 1));

    object_t* p3 = person_api._create(0);
    person_api._set_attr(p3, "name", "Dob");
    person_api._set_attr(p3, "age", number_api._create(ages + 2));

    object_t* p4 = person_api._create(0);
    person_api._set_attr(p4, "name", "Fior");
    person_api._set_attr(p4, "age", number_api._create(ages + 3));

    object_t** raw_list = { p1, p2, p3, p4, 0 };

    list_api._init(people, raw_list);
}

object_t* cmp_age_gt_20(object_t* elem, call_arg_t* args)
{
    const long twenty = (long)*(double*)args->_obj->_value;

    object_api_t* person_api = Table.find(user_types, "Person");

    long person_age = (long)*(double*)Table.find(elem->_api->_attrs, "age");

    char res = person_age > twenty;

    return res ? &lang_true : &lang_false;
}

int main(int argc, char const *argv[])
{
    prepare();


    // people older than 20
    // people[.age > 20)]

    fn_arg_t filter_arg = {
        ._type = &number_api,
        ._next = 0
    };

    lang_fn_t filter_fn = {
        ._name = "people_filter",
        ._body = cmp_age_gt_20,
        ._rv_type = &bool_api,
        ._args = &filter_arg
    };

    object_t arg_val = {
        ._api = &number_api,
        ._value = 20
    };

    call_arg_t filter_call_arg = {
        ._obj = &arg_val,
        ._next = 0    
    };

    called_fn_t invoked_fn = { 
        ._fn = &filter_fn, 
        ._args = &filter_call_arg
    }; 

    object_t actual_filter = {
        ._api = &function_api,
        ._value = &invoked_fn
    };

    list_api._ops.subscribe(people, &invoked_fn);

    return 0;
}


