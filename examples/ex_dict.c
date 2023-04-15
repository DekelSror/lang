
#include <stdio.h>

#include "lp_string.h"
#include "lp_number.h"
#include "lp_dict.h"


/*
    run {
        users <- {
            joe: 4,
            frank: 1,
            nick: 9
        }

        users['rich'] <- 7

        print(users['frank' | 'nick'])
    }

*/

static char dict_mem[0x1000] = { 0 };
static const double number_literals[] = {4.0, 1.0, 9.0, 7.0};
static const char* string_literals[] = {"joe", "frank", "nick", "rich"};

int main(void)
{
    lp_dict_prepare();
    
    object_t* dict = dict_api._create(dict_mem);
    // this is not good
    // insert initial entries

    // object_t* slit_0 = string_api._create(string_literals + 0);
    // object_t* slit_1 = string_api._create(string_literals + 1);
    // object_t* slit_2 = string_api._create(string_literals + 2);

    Table.insert(dict->_value, string_literals + 0, number_literals + 0);
    Table.insert(dict->_value, string_literals + 1, number_literals + 1);
    Table.insert(dict->_value, string_literals + 2, number_literals + 2);

    // object_t* nlit_0 = number_api._create(number_literals + 3);
    
    Table.insert(dict->_value, string_literals + 3, number_literals + 3);

    // subscribe filter fn ['frank' | 'nick']

    return 0;
}
