#include <stdio.h>

int main()
{
    printf("int: %d\n", 1u<<4);
    printf("char: %c\n", 1u<<4);
    int n = 0x16;
    printf("n = %d\n", n);
    printf("hex: %x\n", 16);
    return 0;
}

