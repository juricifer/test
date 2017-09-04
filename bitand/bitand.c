#include <stdio.h>

typedef unsigned char BYTE;
#define byte BYTE

int main()
{
    BYTE s = 0x73;
    byte a = 0x13;
    printf("s&a: 0x%0x\n", s&a);
    return 0;
}

