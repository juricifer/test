#include <stdio.h>

//#pragma pack(1)    //设置1字节对齐，pragma pack(n)默认为4
typedef struct node
{
    
}S;
 
typedef struct node1
{
    int a;
    char b;
    short c;
}S1;
 
typedef struct node2
{
    char a;
    int b;
    short c;
}S2;
 
typedef struct node3
{
    int a;
    short b;
//    static int c;//c++结构体才允许有静态成员，S3 size为8
}S3;
 
typedef struct node4
{
//    bool a;//标准c中没有bool的定义
    char a;
    S1 s1;
    short b;
}S4;
 
typedef struct node5
{
//    bool a;
    char a;
    S1 s1;
    double b;
    int c;
}S5;

 typedef struct node6
{
    long long a;
    int b;
}S6;
//#pragma pack()     //取消1字节对齐 

int main()
{
    printf("sizeof(S) = %d\n", sizeof(S));   //0
    printf("sizeof(S1) = %d\n", sizeof(S1)); //8
    printf("sizeof(S2) = %d\n", sizeof(S2)); //12
    printf("sizeof(S3) = %d\n", sizeof(S3)); //8
    printf("sizeof(S4) = %d\n", sizeof(S4)); //16//pragma pack(4)
    printf("sizeof(S5）= %d\n", sizeof(S5)); //24//pragma pack(4)
    printf("sizeof(S6）= %d\n", sizeof(S6)); //12//pragma pack(4)

    //打开pragma，输出：0 7 7 6 10 20 12
    //？？？8字节对齐结果同pragma pack(4)，未解
	return 0;
}

