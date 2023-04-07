#include "table.h"
#include "mhash.h"


static unsigned long strlen(const char* s)
{
    unsigned long len = 0;
    
    while (*s++ != 0) 
        len++;

    return len;
}

static unsigned long murmurhash_64(const char* key)
{
    static const unsigned long seed = 11UL;

    return MurmurHash64(key, strlen(key), seed);
}

static table_t* table_create(void* mem, unsigned size)
{
    table_t* this = mem;
    this->_size = size;
    this->_hash = murmurhash_64;

    return this;
}

static void table_destroy(table_t* table)
{
    (void)table;
}

static int table_insert(table_t* this, const char* key, void* value)
{
    unsigned long key_hash = this->_hash(key);

    unsigned raw_index = key_hash % this->_size;

    while (this->_entries[raw_index]._hash_part != 0ul) {
        raw_index++;

        if (raw_index == this->_size) return 1;
    }

    this->_entries[raw_index]._hash_part = key_hash;
    this->_entries[raw_index]._value = value;

    return 0;
}

static void* table_find(const table_t* this, const char* key)
{
    unsigned long key_hash = this->_hash(key);

    unsigned raw_index = key_hash % this->_size;

    // this is very bad, my brother in christ
    while (this->_entries[raw_index]._hash_part != key_hash) {
        raw_index++;

        if (raw_index == this->_size) return (void*)0;
    }

    return this->_entries[raw_index]._value;
}


const table_api_t Table = {
    .create = table_create,
    .destroy = table_destroy,
    .insert = table_insert,
    .find = table_find
};
