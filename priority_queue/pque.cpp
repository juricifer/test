/* 
 * priority_queue.cpp
 * output:
 * pq: 33 11 10 7 2 
 * pqm: ddd bbb aaa eee ccc 
 */

#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

// must be defined outside the function
typedef struct _MSG{
	int priority;
	char msg[128];

	friend bool operator < (_MSG m, _MSG n)
	{
		return m.priority > n.priority;
	}
} MSG;

int main()
{
	int a[5] = {10, 2, 33, 7, 11};
	priority_queue<int> pq;

	for (int i=0; i<5; i++)
	{
		pq.push(a[i]);
	}

	cout << "pq: ";
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;

	MSG M[5];
	M[0].priority = 3;
	strcpy(M[0].msg, "aaa");
	M[1].priority = 2;
	strcpy(M[1].msg, "bbb");
	M[2].priority = 5;
	strcpy(M[2].msg, "ccc");
	M[3].priority = 1;
	strcpy(M[3].msg, "ddd");
	M[4].priority = 4;
	strcpy(M[4].msg, "eee");
	priority_queue<MSG> pqm;
	for (int i=0; i<5; i++)
	{
		pqm.push(M[i]);
	}

	cout << "pqm: ";
	while (!pqm.empty())
	{
		cout << pqm.top().msg << " ";
		pqm.pop();
	}
	cout << endl;
	return 0;
}

