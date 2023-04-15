#ifndef utils
#define utils


typedef struct 
{
    char*(*move)(char* dest, const char* src, unsigned long size);
    int(*cmp)(const char* a , const char* b, unsigned long size);
    int(*set)(void* buf, char mask, unsigned length);
} memutils_t;

extern const memutils_t Memutils;

#endif // utils