#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    cout << wcslen(L"") << endl;
    cout << wcslen(L"\0") << endl;
    cout << wcslen(L"abc") << endl;
    cout << wcslen(L"abc\0") << endl;
    cout << wcslen(L"0") << endl;

    wchar_t str1[] = L"abc";
    cout << "sizeof(str1) = " << sizeof(str1) << endl;

    return 0;
}

