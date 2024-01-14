#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10, INF = 0x3f3f3f3f;
int n;
int p[maxn];
struct Segment_Tree{
	struct node{
		int maxx, tag, active;
		node(int maxx = -INF,int act = 0,int tag = 0
			):maxx(maxx),tag(tag),active(act){}
	}d[maxn << 2];
	node mergenode(node l,node r){return node(max(l.maxx,r.maxx),l.active + r.active);}
	void pushdown(int p){
		if(d[p].tag != 0){
			d[p << 1].tag += d[p].tag;
			d[p << 1 | 1].tag += d[p].tag;
			d[p << 1].maxx += d[p].tag;
			d[p << 1 | 1].maxx += d[p].tag;
			d[p].tag = 0;
		}
	}
	void build(int l,int r,int p){
		if(l == r){d[p] = node((l & 1) + (l - 1) - 1 - INF);return;}
		int mid = l + r >> 1;
		build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
		d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
	}
	void update(int l,int r,int s,int t,int p,int val){
		if(s <= l && r <= t){d[p].maxx += val;d[p].tag += val;return;}
		int mid = l + r >> 1;pushdown(p);
		if(s <= mid)update(l,mid,s,t,p << 1,val);
		if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,val);
		d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
	}
	void update(int l,int r,int pos,int p){
		if(l == r && l == pos){d[p].maxx += INF;d[p].active = 1;return;}
		int mid = l + r >> 1;pushdown(p);
		if(pos <= mid)update(l,mid,pos,p << 1);
		else update(mid + 1,r,pos,p << 1 | 1);
		d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
	}
	node query(int l,int r,int s,int t,int p){
		if(s <= l && r <= t)return d[p];
		int mid = l + r >> 1;pushdown(p);
		if(t <= mid)return query(l,mid,s,t,p << 1);
		if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
		return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
	}
	int findr(int l,int r,int p){
		if(l == r)return l; int mid = l + r >> 1;
		if(d[p << 1].active == mid - l + 1)return findr(mid + 1,r,p << 1 | 1);
		else return findr(l,mid,p << 1);
	}
	int findr(){return findr(1,n,1);}
	void update(int l,int r,int upd){if(r < l)return;update(1,n,l,r,1,upd);}
	void active(int pos){if(pos < 1 || pos > n)return;update(1,n,pos,1);}
	int query(int l,int r){if(r < l)return 0;return query(1,n,l,r,1).maxx;}
}tree;
void solve(){
	n = read();tree.build(1,n,1);
	for(int i = 1;i <= n;i++){p[read()] = i;}
	int ans = 0;
	for(int i = 1;i <= n;i++){
		tree.update(p[i] + 1,n,-1);//puts("111111111");
		tree.update(1,p[i],1); tree.active(p[i]);//puts("22222222");
		int t = (tree.d[1].active == n) ? (n + 1) : (tree.findr());//puts("33333333");
		ans = max(ans,tree.query(t,n));
	}
	printf("%d\n",ans);
}
signed main(){
	int T = read();
	while(T--){solve();}
	return 0;
}
