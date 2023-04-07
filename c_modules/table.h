#ifndef lang_table_h
#define lang_table_h


typedef unsigned long (*hash_fn_64)(const char* key);


typedef struct 
{
    unsigned long _hash_part;
    void* _value;
} tentry_t;


typedef struct 
{
    hash_fn_64 _hash;
    unsigned _size;
    tentry_t _entries[];
} table_t;


typedef struct 
{
    table_t*(*create)(void* mem, unsigned size);
    void(*destroy)(table_t*);
    //
    int(*insert)(table_t* table, const char* key, void* value);
    void*(*find)(const table_t*, const char*);
} table_api_t;


extern const table_api_t Table;

#endif // lang_table_h