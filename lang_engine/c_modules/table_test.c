#include <stdio.h>
#include "table.h"


char table_mem[4096] = { 0 };

typedef struct 
{
    long _num;
    char* _str;
} table_test_t;

table_test_t test_elems[] = {
    {._num = 40, ._str = "smakkal"},
    {._num = 0x4000, ._str = "smallak wallak"},
    {._num = 03454, ._str = "sw"},
    {._num = -99119922, ._str = ""},
};

const char* elem_names[] = {"elem1", "elem2", "elem3", "elem4"};

int main(void)
{
    table_t* table = Table.create(table_mem, 16);


    for (long i = 0; i < 4; i++)
    {
        Table.insert(table, elem_names[i], test_elems + i);
    }
    
    table_test_t* find_elem1 = Table.find(table, "elem1");

    printf("find elem1 %ld '%s'\n", find_elem1->_num, find_elem1->_str);

    
    return 0;
}
