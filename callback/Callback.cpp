/*
 * �ص��������ص���������һ��ͨ������ָ����õĺ����������Ѻ�����ָ��(��ַ)��Ϊ�������ݸ���һ�������������ָ�뱻��Ϊ��������ָ��ĺ���ʱ�����Ǿ�˵���ǻص�������
 * ģ��A��һ������foo������ģ��B����foo�ĵ�ַ��Ȼ����B���淢��ĳ���¼�ʱ��ͨ��A���洫������foo��ַ����foo��֪ͨA������ʲô���飬��A������Ӧ��Ӧ����ôfoo�ͳ�Ϊ�ص�������
 */

#include <iostream>
using namespace std;

typedef int(*CallBack)(char *p);//����CallBack ���͵ĺ���ָ��
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
    lpCall(p);    //�����ص���ɵĹ���,Ҳ����A�����������.
    return 0;
}
int main()
{
    char *p = "hello!";
    B(A, p);
    return 0;
}
