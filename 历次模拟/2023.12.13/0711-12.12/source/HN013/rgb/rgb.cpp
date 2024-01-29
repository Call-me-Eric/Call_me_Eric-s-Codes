#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getc() {
	static char *p1, *p2, buf[1<<20];
	return p1==p2?(p2=(p1=buf)+fread(buf, 1, 1<<20, stdin), p1==p2?10:*p1++):*p1++;
}
inline char gc() {
	char c;
	while (!isalpha(c=getc()));
	return c;
}
inline int read() {
	int f=1, r=0; char c=getc();
	while (!isdigit(c)) f^=c=='-', c=getc();
	while (isdigit(c)) r=r*10+c-48, c=getc();
	return f?r:-r;
}
mt19937 RAND(random_device{}());
const int N=257, M=N*(N-1)/2+7;
int r, g, b, n, m;
struct edge {int u, v, id;};
vector<edge> e0, e1, e2;
struct dsu {
	int pa[N];
	inline void init() {iota(pa+1, pa+n+1, 1);}
	int find(int x) {return pa[x]^x?pa[x]=find(pa[x]):x;}
	inline void unin(int x, int y) {pa[find(x)]=find(y);}
	inline bool chk(int x, int y) {return find(x)!=find(y);}
} d;
inline bool chkb(dsu d) {
	int c=0;
	for (auto x:e2) {
		if (c==b) break;
		if (d.chk(x.u, x.v)) d.unin(x.u, x.v), c++;
	}
	return c==b;
}
inline bool chkg(dsu d) {
	int c=0;
	for (auto x:e1) {
		if (c==g) break;
		if (d.chk(x.u, x.v)) {
			dsu t=d; t.unin(x.u, x.v);
			if (chkb(t)) d=t, c++;
		}
	}
	return c==g;
}
int main() {
	freopen("rgb.in", "r", stdin);
	freopen("rgb.out", "w", stdout);
	r=read(), g=read(), b=read(), n=r+g+b+1, m=read();
	for (int i=0; i<m; i++) {
		int x=read(), y=read(); char c=gc();
		(c=='r'?e0:(c=='g'?e1:e2)).push_back({x, y, i});
	}
	shuffle(e0.begin(), e0.end(), RAND);
	shuffle(e1.begin(), e1.end(), RAND);
	shuffle(e2.begin(), e2.end(), RAND);
	//cerr<<1<<endl;
	string ans(m, 48); int c=0; d.init();
	for (auto x:e0) {
		if (c==r) break;
		if (d.chk(x.u, x.v)) {
			dsu t=d; t.unin(x.u, x.v);
			if (chkg(t)) d=t, c++, ans[x.id]=49;
		}
	}
	//cerr<<2<<endl;
	if (c!=r) puts("NO"), exit(0);
	c=0;
	for (auto x:e1) {
		if (c==g) break;
		if (d.chk(x.u, x.v)) {
			dsu t=d; t.unin(x.u, x.v);
			if (chkb(t)) d=t, c++, ans[x.id]=49;
		}
	}
	//cerr<<3<<endl;
	if (c!=g) puts("NO"), exit(0);
	c=0;
	for (auto x:e2) {
		if (c==b) break;
		if (d.chk(x.u, x.v)) d.unin(x.u, x.v), c++, ans[x.id]=49;
	}
	//cerr<<4<<endl;
	if (c!=b) puts("NO"), exit(0);
	cout<<"YES"<<endl<<ans<<endl;
	return 0;
}
