#include "objmem.h"
#include "table.h"
#include "mhash.h"

static int table_insert_from_hash(table_t* table, unsigned long key_hash, void* value);

static unsigned long strlen(const char* s)
{
    unsigned long len = 0;
    
    while (*s++ != 0) 
        len++;

    return len;
}

static int is_entry_empty(const tentry_t* entry)
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
    return table_insert_from_hash(this, this->_hash(key), value);
}

static int table_insert_from_hash(table_t* table, unsigned long key_hash, void* value)
{
    unsigned index = key_hash % table->_size;

    while (!is_entry_empty(table->_entries + index)) {
        if (table->_entries[index]._hash_part == key_hash)
        {
            // update or ignore?
            // could be a flag in ctor
            break;
        }

        if (index == table->_size) return 1;
        index++;
    }

    table->_entries[index]._hash_part = key_hash;
    table->_entries[index]._value = value;

    return 0;
}

static void* table_find(const table_t* this, const char* key)
{
    unsigned long key_hash = this->_hash(key);

    unsigned index = key_hash % this->_size;

    while (this->_entries[index]._hash_part != key_hash) {
        if (is_entry_empty(this->_entries + index)) return (void*)0;
        if (index == this->_size) return (void*)0;

        index++;
    }

    return this->_entries[index]._value;
}

static unsigned long table_find_index(const table_t* table, const char* key)
{
    unsigned long key_hash = table->_hash(key);

    unsigned index = key_hash % table->_size;

    while (table->_entries[index]._hash_part != key_hash) {
        if (is_entry_empty(table->_entries + index)) return -1UL;
        if (index == table->_size) return -1UL;

        index++;
    }

    return index;
}

static int table_compress_from(table_t* table, unsigned long from_index, unsigned long from_hash)
{
    tentry_t* empty_entry = table->_entries + from_index;
    unsigned long entry_index = from_index + 1;

    while (!is_entry_empty(table->_entries + entry_index))
    {
        if (entry_index == table->_size)
        {
            break;
        }
        if (table->_entries[entry_index]._hash_part < from_hash)
        {
            tentry_t* from_entry = table->_entries + from_index;
            tentry_t* entry = table->_entries + entry_index;

            unsigned long entry_hash = entry->_hash_part;
            // copy to empty entry
            from_entry->_hash_part = entry->_hash_part;
            from_entry->_value = entry->_value;

            entry->_hash_part = -1UL;
            entry->_value = (void*)-1;

            // call from this index which would be empty
            return table_compress_from(table, entry_index, entry_hash);
        }

        entry_index++;
    }

}

static int table_delete(table_t* table, const char* key)
{
    unsigned long elem_hash = table->_hash(key);
    unsigned long elem_index = table_find_index(table, key);

    if (elem_index == -1UL)
    {
        return 1;
    }

    table->_entries[elem_index]._hash_part = -1UL;
    table->_entries[elem_index]._value= (void*)-1;

    table_compress_from(table, elem_index, elem_hash);


    return 0;
}


static int table_copy(table_t* dest, table_t* src)
{
    for (long i = 0; i < src->_size; i++)
    {
        tentry_t* src_entry = src->_entries + i;
        if (!is_entry_empty(src_entry))
        {
            int status = table_insert_from_hash(dest, src_entry->_hash_part, src_entry->_value);

            if (status != 0)
            {
                return status;
            }
        }
    }

    return 0;
    
}


static table_t* table_enlarge(table_t* src)
{
    table_t* dest = table_create(dict_mem(src->_size * 2), src->_size * 2);

    if (dest != 0)
    {
        int copy_res = table_copy(dest, src);
    }

    return dest;
}

const table_api_t Table = {
    .create = table_create,
    .destroy = table_destroy,
    .insert = table_insert,
    .find = table_find,
    .delete = table_delete
};
