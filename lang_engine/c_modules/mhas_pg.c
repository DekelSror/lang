#include <stdio.h>
#include "mhash.h"



int main(void)
{
    unsigned long seed = 0x12bb45a0a;

    unsigned long hash = 0;


    hash = MurmurHash64("users", 5, seed);
    printf("hash for users: %lu mod 100 %lu mod 1000 %lu\n", hash, hash % 100, hash % 1000);
    

    hash = MurmurHash64("data", 4, seed);
    printf("hash for users: %lu mod 100 %lu mod 1000 %lu\n", hash, hash % 100, hash % 1000);


    hash = MurmurHash64("api", 3, seed);
    printf("hash for users: %lu mod 100 %lu mod 1000 %lu\n", hash, hash % 100, hash % 1000);



    hash = MurmurHash64("service", 7, seed);
    printf("hash for users: %lu mod 100 %lu mod 1000 %lu\n", hash, hash % 100, hash % 1000);
    

    hash = MurmurHash64("manager", 7, seed);
    printf("hash for users: %lu mod 100 %lu mod 1000 %lu\n", hash, hash % 100, hash % 1000);
    

    hash = MurmurHash64("accounts", 8, seed);
    printf("hash for users: %lu mod 100 %lu mod 1000 %lu\n", hash, hash % 100, hash % 1000);
    
    return 0;
}
