/*
 * static_cast
 * dynamic_cast
 * reinterpret_cast
 */

#include <stdio.h>

int main()
{
    char c = 0x01;
    unsigned char uc = 0x01;
    printf("%20s\tc\tuc\n%20s\t====\t====\n", "", "");
    printf("%20s\t%x\t%x\n", "", c, uc);
    printf("%20s\t%x\t%x\n", "(int)", (int)c, (int)uc);
    printf("%20s\t%x\t%x\n", "(char)(int)", (char)(int)c, (char)(int)uc);
    printf("%20s\t%x\t%x\n", "static_cast", static_cast<int>(c), static_cast<int>(uc));
//    printf("%20s\t%x\t%x\n", "reinterpret_cast", reinterpret_cast<int>(c), reinterpret_cast<int>(uc)); // 编译错误
    return 0;
}

