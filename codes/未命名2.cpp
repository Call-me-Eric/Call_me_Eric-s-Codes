#include <iostream>
#include <cstdio>
#include <list>
#include <cstdlib>
using namespace std;
list <int> l;
bool in[100001];
typedef list<int>::iterator listp;
void DEBUG() {
	for (listp it = l.begin(); it!=l.end(); it++)
		printf("%d ",*it);
	system("pause");
}
int main () {
	#ifdef local
	freopen("testdata (1).in","r",stdin);
	#endif
	int m,n;
	scanf ("%d",&n);
	l.push_back(1);
	for (int i = 2; i<=n; ++i) {
		in[i] = true;
		int k,p;
		scanf ("%d %d",&k,&p);
		listp q = l.begin();
		while(*q != k) q++;
		if (p == 1) q++;
		l.insert(q,i);
	}

	scanf ("%d",&m);
	for (int i = 1; i<=m; ++i) {
		int x;
		scanf ("%d",&x);
		if (!in[x]) continue;
		listp it = l.begin();
		while (*it != x) it++;
		l.erase(it);
		in[x] = false;
	}
	listp it;
	for (it = l.begin(); it!=l.end(); it++)
		printf("%d ",*it);
	puts(" ");
	return 0;
}


