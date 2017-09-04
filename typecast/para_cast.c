#include <stdio.h>

void print(unsigned char c)
{
    printf("param: '%c'\n", c);
}

int main()
{
    int n = 65;
    print(n);
    return 0;
}

