#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	return x * f;
}
int n, m;
const int maxn = 1e5 + 10;
class Segment_tree{
	private:
	struct node{int maxx, sum;}d[maxn * 4];
	node mergenode(node a,node b){return (node){max(a.maxx,b.maxx),a.sum + b.sum};}
	void build(int l,int r,int p){
		if(l == r){d[p] = {a[l],a[l]};return;}
		int mid = (l + r) >> 1;build(l,mid,p << 1);build(mid + 1,r,(p << 1) | 1);
		d[p] = mergenode(d[p << 1],d[(p << 1) | 1]);
	}
	void updmod(int l,int r,int s,int t,int p,int mod){
		if(d[p].maxx < mod)return;
		if(s == t){d[p].maxx = d[p].sum = (d[p].sum % mod);return;}
		int mid = (s + t) >> 1;
		if(l <= mid)updmod(l,r,s,mid,p << 1,mod);
		if(mid < r)updmod(l,r,mid + 1,t,(p << 1) | 1,mod);
		d[p] = mergenode(d[p << 1], d[(p << 1) | 1]);
	}
	void update(int x,int s,int t,int p,int change){
		if(s == t){d[p].sum = change;d[p].maxx = change;return;}
		int mid = (s + t) >> 1;
		if(x <= mid)update(x,s,mid,p << 1,change);
		else update(x,mid + 1,t,(p << 1) | 1,change);
		d[p] = mergenode(d[p << 1],d[(p << 1) | 1]);
	}
	node getsum(int l,int r,int s,int t,int p){
		if(l <= s && t <= r)return d[p];int mid = (s + t) >> 1;
		if(r <= mid)return getsum(l,r,s,mid,p << 1);
		else if(mid < l)return getsum(l,r,mid + 1,t,(p << 1) | 1);
		else return mergenode(getsum(l,r,s,mid,p << 1), getsum(l,r,mid + 1,t,(p << 1) | 1));
	}
	public:
	int a[maxn];
	void build(int n){build(1,n,1);}
	void updmod(int l,int r,int mod){updmod(l,r,1,n,1,mod);}
	int getsum(int l,int r){return getsum(l,r,1,n,1).sum;}
	void update(int x,int change){update(x,1,n,1,change);}
}tree;
signed main(){
	n = read(); m = read();
	for(int i = 1;i <= n;i++)tree.a[i] = read();
	int op, x, y, z;
	tree.build(n);
	for(int i = 1;i <= m;i++){
		op = read(); x = read(); y = read();
		if(op == 2){z = read();tree.updmod(x,y,z);}
		else if(op == 1){printf("%lld\n",tree.getsum(x,y));}
		else {tree.update(x,y);}
	}
	return 0;
}
