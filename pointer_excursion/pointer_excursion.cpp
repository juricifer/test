#include <stdio.h>

class A{
    //…
    int a;
};

class B{
    //…
    char c;
};

class C : public A, public B{
    //…
};

int main()
{
    C* c = new C;
    A* a = (A*)c;
    B* b = (B*)c;
    printf("c_address: %x\n", c);
    printf("a_address: %x\n", a);
    printf("b_address: %x\n", b);
    
    void* pVoid = (void*)c;
    b = (B*)pVoid;
    printf("pVoid_address: %x\n", pVoid);
    printf("b_address: %x\n", b);

    printf("static_cast: %x\ndynamic_cast: %x\nreinterpret_cast: %x\n", \
        static_cast<B*>(c), dynamic_cast<B*>(c), reinterpret_cast<B*>(c));

    return 0;
}

