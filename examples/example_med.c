#include "table.h"

#include "object.h"
#include "primitives.h"
#include "usertype.h"

// #include "compiler.h"

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

    add_attr("Person", "name", &string_api, string_api._create("Steve"));
    add_attr("Person", "age", &number_api, 0);
    
// people list
    people = list_api._create(0);
    list_api._set_attr(people, "elem-type", "Person");

    double ages[] = {94.0, 20.0, 4.0, 53.0};

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

}

object_t* filter_age_lt(call_arg_t* args)
{
    object_t* elem = args->_obj;
    const long min_age = (long)*(double*)args->_next->_obj->_value;

    object_api_t* person_api = Table.find(user_types, "Person");

    long person_age = (long)*(double*)Table.find(elem->_api->_attrs, "age");

    char res = person_age > min_age;

    return res ? &lang_true : &lang_false;
}

int main(int argc, char const *argv[])
{
    prepare();


    // define filter function
    fn_arg_t filter_arg[] = {{
        ._name = "1",
        ._type = &number_api,
        ._default_val = 0
    }};

    add_function("people_filter", &bool_api, filter_age_lt, 1, filter_arg);


    call_arg_t filter_call_arg = {
        ._obj = number_api._create(20),
        ._next = 0    
    };

    lang_fn_t* filter_fn = Table.find(program_functions, "prople_filter");

    called_fn_t invoked_fn = { 
        ._fn = filter_fn, 
        ._args = &filter_call_arg
    }; 


    list_api._ops.subscribe(people, &invoked_fn);

    return 0;
}


