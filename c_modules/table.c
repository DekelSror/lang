#include "table.h"
#include "mhash.h"


static unsigned long strlen(const char* s)
{
    unsigned long len = 0;
    
    while (*s++ != 0) 
        len++;

    return len;
}

static int is_entry_empty(tentry_t* entry)
{
    return entry->_hash_part == (-1UL) && entry->_value == ((void*)-1);
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

    for (long i = 0; i < size; i++)
    {
        this->_entries[i]._hash_part = -1UL;
        this->_entries[i]._value = (void*)-1;
    }
    

    return this;
}

static void table_destroy(table_t* table)
{
    (void)table;
}

static int table_insert(table_t* this, const char* key, void* value)
{
    unsigned long key_hash = this->_hash(key);

    unsigned index = key_hash % this->_size;

    while (!is_entry_empty(this->_entries + index)) {
        index++;

        if (index == this->_size) return 1;
    }

    this->_entries[index]._hash_part = key_hash;
    this->_entries[index]._value = value;

    return 0;
}

static void* table_find(const table_t* this, const char* key)
{
    unsigned long key_hash = this->_hash(key);

    unsigned index = key_hash % this->_size;

    while (this->_entries[index]._hash_part != key_hash) {
        index++;

        if (is_entry_empty(this->_entries + index)) return (void*)0;
        if (index == this->_size) return (void*)0;
    }

    return this->_entries[index]._value;
}

static unsigned long table_find_index(const table_t* table, const char* key)
{
    unsigned long key_hash = table->_hash(key);

    unsigned index = key_hash % table->_size;

    while (table->_entries[index]._hash_part != key_hash) {
        index++;

        if (is_entry_empty(table->_entries + index)) return -1UL;
        if (index == table->_size) return -1UL;
    }

    return index;
}

static int table_delete(table_t* table, const char* key)
{
    unsigned long elem_index = table_find_index(table, key);

    if (elem_index == -1UL)
    {
        return 1;
    }

    table->_entries[elem_index]._hash_part = -1UL;
    table->_entries[elem_index]._value= (void*)-1;

    return 0;
}


const table_api_t Table = {
    .create = table_create,
    .destroy = table_destroy,
    .insert = table_insert,
    .find = table_find,
    .delete = table_delete
};
