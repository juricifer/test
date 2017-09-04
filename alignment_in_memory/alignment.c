#include <stdio.h>

int main()
{
    struct A {
        char c;
        double d;
    } a;
    struct B {
        double d;
        char c;
    } b;

    printf("sizeof(a) = %d\n", sizeof a);
    printf("sizeof(b) = %d\n", sizeof b);
    return 0;
}

