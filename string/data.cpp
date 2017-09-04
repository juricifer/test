#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{
    string str = "1234";
    char p[5] = {0};
    strcpy(p, str.data());
    printf("p->%s\n", p);
    return 0;
}

