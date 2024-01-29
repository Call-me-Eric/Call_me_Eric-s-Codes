#include <bits/stdc++.h>
using namespace std;
//typedef long long ll;
typedef uint64_t ll;
#define int uint32_t
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
const int N=707, mod=998244353;
inline void inc(int &x, int y) {x+=y; if (x>=mod) x-=mod;}
inline void dec(int &x, int y) {
	if (x<y) x+=mod-y;
	else x-=y;
	//x-=y; /*x+=x>>31&mod;*/if (x<0) x+=mod;
}
inline void mul(int &x, int y) {x=(ll)x*y%mod;}
inline int qpow(int a, int b) {
	int res=1;
	for (; b; b>>=1, mul(a, a)) if (b&1) mul(res, a);
	return res;
}
int n, Q, A[N*2][N], lst[N], id[N];
vector<int> vec[N<<2];
int c0, c1, a[N][N];
inline void ins(int now) {
	static int b[N];
	for (int i=1; i<=n+1; i++) b[i]=A[now][i];
	for (int i=1; i<=n; i++) {
		if (!b[i]) continue;
		if (!id[i]) {
			id[i]=now;
			int iv=qpow(b[i], mod-2);
			for (int j=i+1; j<=n+1; j++)
				a[i][j]=(ll)b[j]*iv%mod;
			return;
		}
		int x=mod-b[i];
		for (int j=i+1; j<=n+1; j++) b[j]=(b[j]+(ll)a[i][j]*x)%mod;
	}
	if (!b[n+1]) c1++;
	else c0++;
}
inline void del(int now) {
	for (int i=1; i<=n; i++)
		if (id[i]==now) {
			id[i]=0; //, fill(a[i]+1, a[i]+n+2, 0);
			return;
		}
}
#define ls (p<<1)
#define rs (p<<1|1)
void modify(int p, int l, int r, int x, int y, int i) {
	if (x<=l && r<=y) return vec[p].push_back(i);
	int mid=(l+r)/2;
	if (x<=mid) modify(ls, l, mid, x, y, i);
	if (y>mid) modify(rs, mid+1, r, x, y, i);
}
void dfs(int p, int l, int r) {
	int lc1=c1;
	for (auto x:vec[p]) ins(x);
	if (c0) {
		for (int i=l; i<=r; i++) puts("No");
		c0=0;
	} else if (l==r) {
		if (c1) puts("Many");
		else {
			static int x[N];
			for (int i=n; i; i--) {
				x[i]=a[i][n+1];
				for (int j=i+1; j<=n; j++)
					dec(x[i], (ll)x[j]*a[i][j]%mod);
		//			x[i]=(x[i]+(ll)x[j]*a[i][j])%mod;
			}
			for (int i=1; i<=n; i++) printf("%u%c", x[i], " \n"[i==n]);
		}
	} else {
		int mid=(l+r)/2;
		dfs(ls, l, mid), dfs(rs, mid+1, r);
	}
	c1=lc1;
	for (auto x:vec[p]) del(x);
}
#undef ls
#undef rs
signed main() {
	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);
	n=read(), Q=read();
	for (int i=1; i<=n; i++) {
		lst[i]=0, id[i]=i, a[i][i]=1;
		for (int j=1; j<=n+1; j++) A[i][j]=read();
	}
	for (int i=1; i<=Q; i++) {
		int u=read();
		modify(1, 0, Q, lst[u], i-1, id[u]);
		lst[u]=i, id[u]=i+n;
		for (int j=1; j<=n+1; j++) A[i+n][j]=read();
	}
	for (int i=1; i<=n; i++) modify(1, 0, Q, lst[i], Q, id[i]);
	fill(id+1, id+n+1, 0), dfs(1, 0, Q);
	return 0;
}
