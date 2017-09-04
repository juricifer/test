#include <iostream>
using namespace std;

class Parent
{
public:
    Parent():m_parent(3){}

public:
    int m_parent;
};

class Child : public Parent
{
public:
    Child():m_child(4){}

public:
    int m_child;
};

int main()
{
    Parent* pParent = new Child();
//    cout << pParent->m_child << endl;
    cout << pParent->m_parent << endl;

    Child* pChild = new Child();
    cout << pChild->m_child << endl;
    cout << pChild->m_parent << endl;
    return 0;
}

