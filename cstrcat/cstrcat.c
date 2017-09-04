#include <string.h>
#include <stdio.h>
#include <assert.h>

int main()
{
    char str[] = "xyz";
    char* q = "123";
    printf("str: %s\n", strcat(str, q));
    char* p = "abc";
    *p = 'e';
   // *(p+4) = 'd';
   // printf("str: %s\n", strcat(p, q));//error
    return 0;
}

