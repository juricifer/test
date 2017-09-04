/*******************************************************************
 > FileName   : b.c
 > Function   : 
 > Author     : Fang Tao <Tao.Fang@desay-svautomotive.com>
 > Version    : v1.0 - Thu 15 May 2014 03:55:50 PM HKT
 *******************************************************************/

#include <stdio.h>

int main()
{
    int i = 0x12345678;
    char* p = (char*)&i;
    printf("i = 0x%x\n", i);
    printf("p = 0x%x\n", p);
    printf("p+1 = 0x%x\n", p+1);
    printf("p[0] = 0x%x\n", p[0]);
    printf("p[1] = 0x%x\n", p[1]);
    for (int j=0; j<4; j++)
    {
        printf("%d: %02x\n", j, p[j]);
    }
    return 0;
}

