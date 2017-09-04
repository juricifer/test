/*
 * 回调函数：回调函数就是一个通过函数指针调用的函数。如果你把函数的指针(地址)作为参数传递给另一个函数，当这个指针被用为调用它所指向的函数时，我们就说这是回调函数。
 * 模块A有一个函数foo，它向模块B传递foo的地址，然后在B里面发生某种事件时，通过A里面传过来的foo地址调用foo，通知A发生了什么事情，让A作出相应反应，那么foo就称为回调函数。
 */

#include <iostream>
using namespace std;

typedef int(*CallBack)(char *p);//声明CallBack 类型的函数指针
int A(char *p)
{
    cout << "A" << endl;
    cout << p << endl;
    return 0;
}
int B(CallBack lpCall, char *p)
{
    cout << "B" << endl;
    cout << p << endl;
    lpCall(p);    //借助回调完成的功能,也就是A函数来处理的.
    return 0;
}
int main()
{
    char *p = "hello!";
    B(A, p);
    return 0;
}
