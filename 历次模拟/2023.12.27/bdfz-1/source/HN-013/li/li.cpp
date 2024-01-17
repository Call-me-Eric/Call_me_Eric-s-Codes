#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getc() {
	static char *p1, *p2, buf[1<<20];
	if (p1==p2) p2=(p1=buf)+fread(buf, 1, 1<<20, stdin);
	return p1==p2?10:*p1++;
}
inline int read() {
	int f=1, r=0; char c=getc();
	while (!isdigit(c)) f^=c=='-', c=getc();
	while (isdigit(c)) r=r*10+c-48, c=getc();
	return f?r:-r;
}
template<class T> inline void ckmax(T &x, T y) {if (x<y) x=y;}
const int N=2e5+7;
int n, m, deg[N], pa[N], sz[N], mx[N]; bool fl[N];
int find(int x) {return pa[x]^x?pa[x]=find(pa[x]):x;}
inline void unin(int x, int y) {
	x=find(x), y=find(y);
	if (x==y) {fl[x]=true; return;}
	if (sz[x]>sz[y]) swap(x, y);
	sz[y]+=sz[x], pa[x]=y, fl[y]|=fl[x];
}
int main() {
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	n=read(), m=read();
	for (int i=1; i<=n; i++) pa[i]=i, sz[i]=1;
	while (m--) {
		int x=read(), y=read();
		unin(x, y), deg[x]++, deg[y]++;
	}
	for (int i=1; i<=n; i++) ckmax(mx[find(i)], deg[i]);
	ll s0=0; int s1=0;
	for (int i=1; i<=n; i++) {
		if (find(i)!=i) continue;
		if (mx[i]>=3) {
			if (mx[i]>3 || sz[i]>4 || fl[i]) puts("-1"), exit(0);
			s1+=3;
		} else if (fl[i]) s1+=sz[i];
		else s0+=(ll)sz[i]*(sz[i]+1)/2;
	}
	if (s1) printf("1 %d\n", s1);
	else printf("0 %lld\n", s0);
	return 0;
}
