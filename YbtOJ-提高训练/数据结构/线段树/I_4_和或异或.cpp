#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
int n, Q;
const int maxn = (1 << 17) + 10;
class Segment_tree{
	private:
	struct node{int sum;bool tag;}d[maxn * 4];//tag = 0 <=> | (when merge to other same level); tag = 1 <=> ^
	node mergenode(node a,node b){return (node){a.tag ? (a.sum ^ b.sum) : (a.sum | b.sum),!a.tag};}
	void build(int l,int r,int p){
		if(l == r){d[p] = {a[l],0};return;}
		int mid = (l + r) >> 1;build(l,mid,p << 1);build(mid + 1,r,(p << 1) | 1);
		d[p] = mergenode(d[p << 1],d[(p << 1) | 1]);
	}
	void update(int x,int s,int t,int p,int change){
		if(s == t){d[p].sum = change;return;}
		int mid = (s + t) >> 1;
		if(x <= mid)update(x,s,mid,p << 1,change);
		else update(x,mid + 1,t,(p << 1) | 1,change);
		d[p] = mergenode(d[p << 1],d[(p << 1) | 1]);
	}
	node query(int l,int r,int s,int t,int p){
		if(l <= s && t <= r)return d[p];
		int mid = (s + t) >> 1;
		if(mid < l)return query(l,r,mid + 1,t,(p << 1) | 1);
		else if(r <= mid)return query(l,r,s,mid,p << 1);
		else return mergenode(query(l,r,s,mid,p << 1),query(l,r,mid + 1,t,(p << 1) | 1));
	}
	public:
	void build(int n){build(1,n,1);}
	void update(int x,int y){update(x,1,n,1,y);}
	int query(int l,int r){return query(l,r,1,n,1).sum;}
	int a[maxn];
}tree;
signed main(){
	n = read(); Q = read();n = (1 << n);
	for(int i = 1;i <= n;i++)tree.a[i] = read();
	int x, y;			tree.build(n);
	while(Q--){
		x = read(); y = read();
		tree.update(x,y);
		printf("%d\n",tree.query(1,n));
	}
	return 0;
}
