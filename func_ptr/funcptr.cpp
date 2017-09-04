#include <stdio.h>

typedef void (*pFunc)(int, int);
typedef int (*pFunc2)(int, int);//type of return value will distinguish function pointers between each other
typedef void* (*PFUNC)(int, void*[]);

int Add(int a, int b)
{
    printf("Add() Called\n");
    return a+b;
}

void Test(int a, int b)
{
    printf("Test Called\n");
}

int main()
{
    pFunc pfunc = &Test;
    printf("pfunc-------->[%p]\n", pfunc);
//    printf("result: %d\n", (int)pfunc(10, 20));

//    pFunc pfunc2 = &Add;//invalid conversion from ‘int (*)(int, int)’ to ‘pFunc {aka void (*)(int, int)}’ [-fpermissive]
//    printf("pfunc2-------->[%p]\n", pfunc2);

    pFunc2 pfunc3 = &Add;
    printf("pfunc3-------->[%p]\n", pfunc3);
    
    return 0;
}

