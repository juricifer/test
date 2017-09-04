#include <stdio.h>
#include <queue>
using namespace std;

typedef struct _MSG {
    _MSG(){printf("object created\n");}
    ~_MSG(){printf("object destroyed\n");}
} Msg;

int main()
{
    queue<Msg*> que;
    Msg* m = new Msg();// Msg* m;--just declare a pointer with type Msg, it will not call constructor
    printf("m:addr------>[0x%x]\n", m);
    printf("m:addr------>[%p]\n", m);
    que.push(m);
    while (!que.empty())
    {
        Msg* t = que.front();
        printf("m:addr------>[0x%x]\n", t);
        delete t;
//        delete que.front();
        que.pop();
    }
    printf("que empty\n");
    return 0;
}

