#ifndef MURMUR_PLATFORM_H
#define MURMUR_PLATFORM_H

// void SetAffinity ( int cpu );
// #include <stdint.h>
// #include <strings.h>

// unsigned int rotl32 ( unsigned int x, unsigned char r ){ return (x << r) | (x >> (32 - r)); }
// unsigned long rotl64 ( unsigned long x, unsigned char r ){ return (x << r) | (x >> (64 - r)); }
// unsigned int rotr32 ( unsigned int x, unsigned char r ){ return (x >> r) | (x << (32 - r)); }
// unsigned long rotr64 ( unsigned long x, unsigned char r ){ return (x >> r) | (x << (64 - r)); }
// unsigned long long int rdtsc(){ unsigned long long int x; __asm__ volatile ("rdtsc" : "=A" (x)); return x; }

// #define	ROTL32(x,y)	rotl32(x,y)
// #define ROTL64(x,y)	rotl64(x,y)
// #define	ROTR32(x,y)	rotr32(x,y)
// #define ROTR64(x,y)	rotr64(x,y)
// #define BIG_CONSTANT(x) (x##LLU)
// #define _stricmp strcasecmp




unsigned long MurmurHash64(const void * key, int len, unsigned long seed );

#endif /* MURMUR_PLATFORM_H */
