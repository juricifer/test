#include <iostream>
using namespace std;

typedef void (*pFunc)();
typedef void (*pFn)(void*);

void Caller(pFunc func)
{
	(*func)();
}

void Caller(void* p, pFn func)
{
	(*func)(p);
}

void CallBack()
{
	std::cout << "CallBack() called." << endl;
}

void CallBackWithParam(int* param)
{
	std::cout << "CallBack() called with param " << *param << endl;
}

int main()
{
	pFunc pf = CallBack;
	Caller(pf);
	pFn pfn = CallBackWithParam;
	int n = 5;
	Caller(&n, pfn);
	return 0;
}

