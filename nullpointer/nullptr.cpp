#include <stdio.h>

int main()
{
    int i = 10;
    int* pi = NULL;
    printf("pi-------->[%p]\n", pi);
    void* pv = pi;
    printf("pv-------->[%p]\n", pv);
    int n = *static_cast<int*>(pv);
    printf("&n-------->[%p]\n", &n);
    return 0;
}

