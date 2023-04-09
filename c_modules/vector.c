

#include "vector.h"




static vector_t* vector_create(void* mem, unsigned capacity)
{
    vector_t* this = (vector_t*)mem;
    this->_elem_count = 0;
    this->_capacity = capacity;

    return this;
}

static void vector_destroy(vector_t* vector)
{

}

static long vector_add(vector_t* vector, void* elem)
{
    if (vector->_capacity == vector->_elem_count)
    {
        return -1;
    }

    vector->_arr[vector->_elem_count] = elem;
    vector->_elem_count++;

    return vector->_elem_count;
}

static void* vector_at(vector_t* vector, long index)
{
    return vector->_arr[index];
}

static long vector_size(const vector_t* vector)
{
    return vector->_elem_count;
}


const vector_api_t Vector = {
    .create = vector_create,
    .destroy = vector_destroy,
    .add = vector_add,
    .at = vector_at,
    .size = vector_size
};