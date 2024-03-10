#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0 , f  = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 5e5 + 10, maxk = 110, mod = 1e9 + 7;
int n, m, k;
int pw[maxn];
class Segment_Tree{
private:
	struct node{
		int sum; bool son;
		int pos, add;
		int l, r;
		node(int s = 0,int l = 0,int r = 0,bool so = 0,int p = 0,int a = 0):sum(s),pos(p),add(a),son(so),l(l),r(r){}
	}d[maxn << 2];
	void pushdown(int p){
		if(d[p].pos){
			if(!d[p << 1].son && d[p << 1].pos)pushdown(p << 1);
			if(d[p << 1].son)d[p << 1].sum = (d[p << 1].sum + d[p].add * pw[d[p << 1].l - d[p].pos + 1]);
			if(!d[p << 1 | 1].son && d[p << 1 | 1].pos)pushdown(p << 1 | 1);
			if(d[p << 1 | 1].son)d[p << 1 | 1].sum = (d[p << 1 | 1].sum + d[p].add * pw[d[p << 1 | 1].l - d[p].pos + 1]);
			d[p].pos = d[p].add = 0;
		}
	}
	node mergenode(node l,node r){return node(0,l.l,r.r,0);}
	void build(int l,int r,int p){
		if(l == r){d[p] = node(0,l,l,1);return;}
		int mid = l + r >> 1;
		build(l,mid,p << 1); build(mid + 1,r,p << 1 | 1);
		d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
	}
	void update(int l,int r,int s,int t,int p,int pos,int add){
		if(s <= l && r <= t){
			pushdown(p);
			d[p].pos = pos;d[p].add = add;
			if(d[p].son)d[p].sum = (d[p].sum + pw[d[p].l - pos + 1] * d[p].add) % mod;
			return;
		}
		pushdown(p);
		int mid = l + r >> 1;
		if(s <= mid)update(l,mid,s,t,p << 1,pos,add);
		if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,pos,add);
	}
	int query(int l,int r,int goal,int p){
		if(l == r && l == goal)return d[p].sum;
		int mid = l + r >> 1;pushdown(p);
		if(goal <= mid)return query(l,mid,goal,p << 1);
		else return query(mid + 1,r,goal,p << 1 | 1);
	}
public:
	void update(int l,int r,int pos,int add){update(1,n,l,r,1,pos,add);}
	int query(int pos){return query(1,n,pos,1);}
	void build(){build(1,n,1);}
}tree;
int qpow(int x,int a){
	int res = 1;
	while(a){
		if(a & 1)res = (res * x) % mod;
		x = (x * x) % mod;a >>= 1;
	}
	return res;
}
struct BIT{
	int c[maxn << 2];
	void upd(int x,int add){for(;x <= n;x += (x & (-x)))c[x] = (c[x] + add) % mod;}
	int query(int x){int ans = 0;for(;x;x -= (x & (-x)))ans = (ans + c[x]) % mod;return ans;}
}tr;
signed main(){
	freopen("ruby.in","r",stdin);
	freopen("ruby.out","w",stdout);
	n = read(); m = read(); k = read();
if(k != 1){
	int tmp1 = 1, tmp2 = 1;
	for(int i = 1;i < k;i++){
		tmp1 = tmp1 * i;
		tmp2 = tmp2 * i;
	}
	tmp2 = qpow(tmp2,mod - 2) % mod;
//	printf("tmp2 = %lld\n",tmp2);
	for(int i = 1;i <= n;i++){
		pw[i] = tmp1 * tmp2 % mod;
		tmp1 = tmp1 * (i + k - 1) * qpow(i,mod - 2) % mod;
	}
//	for(int i = 1;i <= n;i++)printf("%lld ",pw[i]);
	tree.build();
	int opt, u, v;
	for(int i = 1;i <= m;i++){
		opt = read(); u = read();
		if(!opt){
			v = read();
			tree.update(u,n,u,v);
		}
		else{
			printf("%lld\n",tree.query(u) % mod);
		}
	}
}
else{
	int opt, u, v;
	for(int i = 1;i <= m;i++){
		opt = read(); u = read();
		if(!opt){v = read();tr.upd(u,v);}
		else printf("%lld\n",tr.query(u));
	}
}
	return 0;
}
/*
  4 11 3
  0 1 1
  0 3 1
  1 1
  1 2
  1 3
  1 4
  0 3 1
  1 1
  1 2
  1 3
  1 4

 */
