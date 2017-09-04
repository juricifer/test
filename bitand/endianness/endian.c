/*******************************************************************
 > FileName   : endian.c
 > Function   : 
 > Author     : Fang Tao <Tao.Fang@desay-svautomotive.com>
 > Version    : v1.0 - Wed 14 May 2014 05:23:01 PM HKT
 *******************************************************************/

#include "endian.h"
#include <stdio.h>

typedef union u {
    int n;
    char c;
} un;

int main()
{
    un u;
    u.n = 1;
    printf("%s\n", 1==u.c ? "little-endian" : "big-endian"); 
    return 0;
}

