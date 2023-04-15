#include <stdio.h>

#include "mem_utils.h"


static const char phrase[] = "Have you ever had a dream that you want him to do you so much you could do anything";

void separate_test(void)
{
    char buf[100] = { 0 };

    printf("%d\n", Memutils.cmp(Memutils.move(buf, phrase, 84), buf, 83));
}



void cmp_test(void)
{
    char a[] = "aaa";
    char* b[] = {"aaa", "", "aaaa"};

    printf("cmp for 10 chars of phrase %d\n", Memutils.cmp(phrase, phrase, 10));
    printf("cmp aaa to aaa %d\n", Memutils.cmp(a, b[0], 10));
    printf("cmp aaa to empty %d\n", Memutils.cmp(a, b[1], 3));
    printf("cmp aaa to aaaa (len 3) %d\n", Memutils.cmp(a, b[2], 3));
    printf("cmp aaa to aaaa (len 4) %d\n", Memutils.cmp(a, b[2], 4));

}

void move_test(void)
{
    char test[] = "abcdefghij";

    char* ptrs[10] = { 0 };

    for (int i = 0; i < 10; i++)
    {
        ptrs[i] = test + i;
    }

    Memutils.move(ptrs + 5, ptrs, sizeof(char*) * 5);
    
    for (int i = 0; i < 10; i++)
    {
        printf("%c", *ptrs[i]);
    }
    printf("\n");
    

}

int main(void)
{
    // cmp_test();
    // separate_test();
    move_test();

    return 0;
}
