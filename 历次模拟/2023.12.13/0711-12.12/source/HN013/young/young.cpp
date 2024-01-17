#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getc() {
	static char *p1, *p2, buf[1<<20];
	return p1==p2?(p2=(p1=buf)+fread(buf, 1, 1<<20, stdin), p1==p2?10:*p1++):*p1++;
}
inline int read() {
	int f=1, r=0; char c=getc();
	while (!isdigit(c)) f^=c=='-', c=getc();
	while (isdigit(c)) r=r*10+c-48, c=getc();
	return f?r:-r;
}
const int N=66, mod=998244353;
int n, m, ans, Q, K, a[N], b[N];
inline int dis(int _n=n) {
	int res=0;
	for (int i=1; i<=max(_n, m); i++) res+=abs(a[i]-b[i]);
	return res;
}
void dfs(int x, int n) {
	int d=dis(n);
	if (d>K-x+1) return;
	if (x==K+1) {ans++; return;}
	for (int i=1; i<=n+1; i++)
		if (a[i]<a[i-1])
			a[i]++, dfs(x+1, max(n, i)), a[i]--;
	for (int i=1; i<=n; i++)
		if (a[i]>a[i+1])
			a[i]--, dfs(x+1, n-(i==n && !a[i])), a[i]++;
	
}
int main() {
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
	n=read(), a[0]=1e9;
	for (int i=1; i<=n; i++) a[i]=read();
	m=read();
	for (int i=1; i<=m; i++) b[i]=read();
	Q=read();
	while (Q--) {
		K=read();
		if ((dis()^K)&1) {puts("0"); continue;}
		ans=0, dfs(1, n);
		printf("%d\n", ans);
	}
	return 0;
}
