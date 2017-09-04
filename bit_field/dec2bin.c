/*******************************************************************
 > FileName   : /home/ubuntu/test/bit_field/dec2bin.c
 > Function   : 
 > Author     : Fang Tao <Tao.Fang@desay-svautomotive.com>
 > Version    : v1.0 - Thu 15 May 2014 04:35:19 PM HKT
 *******************************************************************/

#include "dec2bin.h"
#include <stdio.h>

void Dec2Bin(int nDec)
{
    printf("[0x%08x]", nDec);
    int i = 0;
    for (i=1; i<33; i++)
    {
        printf("%c", nDec<0 ? '1' : '0');
        if (0 == i%4) printf(" ");
        nDec = nDec<<1;
    }
    printf("\n");
}

