#include <stdio.h>

int main()
{
    int n = 65;
    printf("(char)n: %c\n", (char)n);
    printf("n<<24: %c\n", n<<24);
    
    unsigned char c = 'A';
    int x = c;
    printf("x = %d\n", x);
    int y = (int)c;
    printf("y = %d\n", y);
    char s = (char)y;
    printf("s = '%c'\n", s);

    return 0;
}

