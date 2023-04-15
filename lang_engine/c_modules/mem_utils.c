#include "mem_utils.h"

static char* move(char* dest, const char* src, unsigned long n, int reverse);

static char* mem_move(char* dest, const char* src, unsigned long n)
{
    return move(dest, src, n, dest > src && dest < src + n);
}

static char* move(char* dest, const char* src, unsigned long n, int reverse)
{
    char* og_dest = dest;

    const int big_chunk = reverse ? -8 : 8;
    int fix = n >= 8 ? 8 : 1;

    char* dest_directed = reverse ? dest + n - fix : dest;
    const char* src_directed = reverse ? src + n - fix : src;

    while (n >= 8)
    {
        *(long*)dest_directed = *(const long*)src_directed;
        src_directed += big_chunk;
        dest_directed += big_chunk;
        n -= 8;
    }
    while (n > 0)
    {
        *dest_directed = *src_directed;
        src_directed += (big_chunk / 8);
        dest_directed += (big_chunk / 8);
        n--;
    }
    return og_dest;

}


static int mem_cmp(const char* a, const char* b, unsigned long n)
{
    while (n >= 8)
    {
        long la = *(long*)a;
        long lb = *(long*)b;

        if (la != lb) return 1;
        n -= 8;
    }

    while (n > 0)
    {
        if (*a != *b) return 1;
        --n;
    }

    return 0;
}

int mem_set(void* buf, char c, unsigned n)
{
    char* cbuf = buf;
    short m2 = (short)c << 8 | c;
    int m4 = (int)m2 << 16 | m2;
    long m8 = (long)m4 << 32 | m4;

    while (n >= 8)
    {
        *(long*)cbuf = m8;
        cbuf += 8;

        n -= 8;
    }

    while (n > 0)
    {
        *cbuf = c;
        ++cbuf;
        --n;
    }

    return 0;
}



const memutils_t Memutils = { mem_move, mem_cmp, mem_set };