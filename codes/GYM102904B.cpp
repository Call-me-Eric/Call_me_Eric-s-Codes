#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f =1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 3e5 + 10;
int n, x;
int p[maxn];

struct BIT{
	int c[maxn];
	inline int lowbit(int x){return x & (-x);}
	int qry(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
	void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] += add;}
}tr;
int lpos, rpos, sum;
void addl(int x){sum += tr.qry(p[x]);tr.upd(p[x], 1);}
void dell(int x){tr.upd(p[x],-1);sum -= tr.qry(p[x]);}
void addr(int x){sum += tr.qry(n) - tr.qry(p[x]);tr.upd(p[x], 1);}
void delr(int x){tr.upd(p[x],-1);sum -= tr.qry(n) - tr.qry(p[x]);}
int calc(int l,int r){
	while(l < lpos)addl(--lpos);
	while(rpos < r)addr(++rpos);
	while(lpos < l)dell(lpos++);
	while(r < rpos)delr(rpos--);
	return sum;
}

int f[maxn];
void solve(int l,int r,int u,int v){
//	printf("%lld %lld %lld %lld\n",l,r,u,v);
	if(l > r)return;int mid = l + r >> 1, pos = u;
	int mn = calc(u + 1,mid) + f[u] + x;
	for(int i = u + 1;i <= v;i++){
		if(calc(i + 1,mid) + f[i] + x < mn){
			mn = calc(i + 1,mid) + f[i] + x;pos = i;
		}
	}
	f[mid] = min(mn,f[mid]);
	solve(l,mid - 1,u,pos);solve(mid + 1,r,pos,v);
}
void CDQ(int l,int r){
//	printf("%lld %lld\n",l,r);
	if(l == r)return;int mid = l + r >> 1;
	CDQ(l,mid);solve(mid + 1,r,l,mid);CDQ(mid + 1,r);
}

signed main(){
	lpos = 1; rpos = 0;sum = 0;
	n = read();x = read();for(int i = 1;i <= n;i++)p[i] = read(), f[i] = calc(1, i) + x;
	CDQ(1, n);printf("%lld\n",f[n]);
	return 0;
}
