#ifndef lang_vector_h
#define lang_vector_h


typedef struct 
{
    long _capacity;
    long _elem_count;
    void* _arr[];
} vector_t;


typedef struct 
{
    vector_t*(*create)(void* mem, unsigned capacity);
    void(*destroy)(vector_t*);
    //
    int(*add)(vector_t*, void*);
    void*(*at)(vector_t*, long index);
    //
    long(*size)(const vector_t* vector);
} vector_api_t;

extern const vector_api_t Vector;

#endif // lang_vector_h