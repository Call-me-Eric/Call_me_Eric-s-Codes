#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	return x * f;
}
int n, m;
const int maxn = 5e5 + 10, maxm = 1e5 + 10;
class Segment_tree{
	private:
struct node{
	int lmax,rmax,maxx,sum;
}d[maxn * 4];
node mergenode(node a,node b){
	node tmp;
	tmp.lmax = max(a.lmax,a.sum + b.lmax);
	tmp.rmax = max(b.rmax,b.sum + a.rmax);
	tmp.maxx = max(max(a.maxx,b.maxx),a.rmax + b.lmax);
	tmp.sum = a.sum + b.sum;
	return tmp;
}
void build(int l,int r,int p){
	if(l == r){d[p].lmax = d[p].rmax = d[p].maxx = d[p].sum = a[l];return;}
	int mid = (l + r) >> 1;build(l,mid,p << 1);build(mid + 1,r,(p << 1) | 1);
	d[p] = mergenode(d[p << 1],d[(p << 1) | 1]);
}
void update(int x,int s,int t,int p,int change){
	if(s == t && s == x){d[p] = {change,change,change, change};return;}
	int mid = (s + t) >> 1;
	if(mid >= x)update(x,s,mid,p << 1,change);
	else update(x,mid + 1,t,(p << 1) | 1,change);
	d[p] = mergenode(d[p << 1],d[(p << 1) | 1]);
}
node query(int l,int r,int s,int t,int p){
	if(l <= s && t <= r)return d[p];
	int mid = (s + t) >> 1;
	if(mid >= r)return query(l,r,s,mid,p << 1);
	else if(mid < l)return query(l,r,mid + 1,t,(p << 1) | 1);
	else return mergenode(query(l,r,s,mid,p << 1),query(l,r,mid + 1,t,(p << 1) | 1));
}
public:
int a[maxn];
void build(int n){build(1,n,1);}
void update(int pos,int change){update(pos,1,n,1,change);}
int query(int x,int y){if(x > y)swap(x,y);return query(x,y,1,n,1).maxx;}
}tree;
signed main(){
	n = read(); m = read();
	for(int i = 1;i <= n;i++){tree.a[i] = read();}
	tree.build(n); int op, x, y;
	for(int i = 1;i <= m;i++){
		op = read(); x = read(); y = read();
		if(op == 1)printf("%d\n",tree.query(x,y));
		else tree.update(x,y);
	}
	return 0;
}
