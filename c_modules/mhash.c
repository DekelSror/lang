#include "mhash.h"



/*-----------------------------------------------------------------------------
// MurmurHash2, 64-bit versions, by Austin Appleby
//
// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment 
// and endian-ness issues if used across multiple platforms.
//
// 64-bit hash for 64-bit platforms
*/

unsigned long MurmurHash64( const void * key, int len, unsigned long seed )
{
    const unsigned long m = 0xc6a4a7935bd1e995ULL;
    const int r = 47;

    unsigned long h = seed ^ (len * m);

    const unsigned long * data = (const unsigned long *)key;
    const unsigned long * end = data + (len/8);

    while(data != end)
    {
        unsigned long k = *data++;

        k *= m; 
        k ^= k >> r; 
        k *= m; 

        h ^= k;
        h *= m; 
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch(len & 7)
    {
        case 7: h ^= ((unsigned long) data2[6]) << 48;
        case 6: h ^= ((unsigned long) data2[5]) << 40;
        case 5: h ^= ((unsigned long) data2[4]) << 32;
        case 4: h ^= ((unsigned long) data2[3]) << 24;
        case 3: h ^= ((unsigned long) data2[2]) << 16;
        case 2: h ^= ((unsigned long) data2[1]) << 8;
        case 1: h ^= ((unsigned long) data2[0]);
                h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
} 


