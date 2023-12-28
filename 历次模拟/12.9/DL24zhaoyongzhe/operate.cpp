#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 5e5 + 10;
int n, m, q;
struct Segment_Tree{
	struct node{
		int tag, sum;
		node(int s = 0,int t = -1):sum(s),tag(t){}
	}d[maxn << 2];
	node mergenode(node l,node r){return node(l.sum + r.sum);}
	void pushdown(int p){
		if(d[p].tag != -1){
			d[p << 1].tag = d[p << 1].sum = d[p].tag;
			d[p << 1 | 1].tag = d[p << 1 | 1].sum = d[p].tag;
			d[p].tag = -1;
		}
	}
	void build(int l = 1,int r = n,int p = 1){
		if(l == r){d[p] = node();return;}
		int mid = l + r >> 1;
		build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
		d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
	}
	void update(int l,int r,int s,int t,int p,int upd){
		if(s <= l && r <= t){d[p].tag = upd;d[p].sum = upd;return;}
		int mid = l + r >> 1;pushdown(p);
		if(s <= mid)update(l,mid,s,t,p << 1,upd);
		if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
		d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
	}
	int query(int l,int r,int pos,int p){
		if(l == r && l == pos)return d[p].sum;
		int mid = l + r >> 1;pushdown(p);
		if(pos <= mid)return query(l,mid,pos,p << 1);
		else return query(mid + 1,r,pos,p << 1 | 1);
	}
	void update(int s,int t,int upd){update(1,n,s,t,1,upd);}
	int query(int l){return query(1,n,l,1);}
	void swapval(int x,int y){
		int vx = query(x), vy = query(y);
		update(x,x,vy);update(y,y,vx);
	}
}tree;
struct opts{
	int opt, l, r,val;
	opts(int o = 0,int l = 0,int r = 0,int v = 0):opt(o),l(l),r(r),val(v){}
}qry[maxn];
signed main(){
	freopen("operate.in","r",stdin);
	freopen("operate.out","w",stdout);
	n = read();m = read(); q =read();int opt, u, v, w;
	for(int i = 1;i <= m;i++){
		opt = read();u = read();
		if(opt == 3){qry[i] = opts(3,u);}
		if(opt == 2){
			v = read(); w = read();
			qry[i] = opts(2,u,v,w);
		}
		if(opt == 1){
			v = read();
			qry[i] = opts(1,u,v);
		}
	}
	for(int i = 1;i <= q;i++){
		u = read(); v = read();
		tree.build();int ans = 0;
		for(int j = u;j <= v;j++){
			if(qry[j].opt == 3)
				ans += tree.query(qry[j].l);
			if(qry[j].opt == 2)
				tree.update(qry[j].l,qry[j].r,qry[j].val);
			if(qry[j].opt == 1)
				tree.swapval(qry[j].l,qry[j].r);
		}
		printf("%d\n",ans);
	}
	return 0;
}
