#include <stdio.h>

#include "vector.h"


static char vector_mem[4096] = { 0 };

typedef struct 
{
    long _num;
    char* _str;
} vector_test_t;

vector_test_t test_elems[] = {
    {._num = 40, ._str = "smakkal"},
    {._num = 0x4000, ._str = "smallak wallak"},
    {._num = 03454, ._str = "sw"},
    {._num = -99119922, ._str = ""},
};

int main(void)
{
    vector_t* vector = Vector.create(vector_mem, 20);

    for (long i = 0; i < 4; i++)
    {
        int res = Vector.add(vector, test_elems + i);
    }

    for (long i = 0; i < 4; i++)
    {
        vector_test_t* elem = Vector.at(vector, i);

        printf(" vector[%ld] is %ld '%s' \n", i, elem->_num, elem->_str);
    }
    
    

    return 0;
}
