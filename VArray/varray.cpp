//文件名: array01.cpp
#include<iostream>
using namespace std;

int main()
{
    int len;
    cout << "请输入数组长度：" << endl;
    cin >> len;
    //用指针p指向new动态分配的长度为len*sizeof(int)的内存空间
    int *p = new int[len];
    cout << "sizeof(p): " << sizeof(p) << endl;
    cout << "sizeof(arr): " << sizeof(int[len]) << endl;
    delete[] p;
    return 0;
}

