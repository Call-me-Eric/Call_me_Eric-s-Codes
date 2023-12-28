#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
int n, m;
const int maxn = 1e5 + 10, mod = 1e9 + 7;
class Segment_tree{
	private:
	struct node{
		int sum, lazytag;int l, r;
	} d[maxn * 4];
	void build(int l,int r,int p){
		if(l == r){d[p].sum = d[p].lazytag = 0;d[p].l = d[p].r =l;return;}
		int mid = (l + r) >> 1;
		build(l,mid,p << 1);build(mid + 1,r,(p << 1) | 1);
		d[p].l = l;d[p].r = r;
		return;
	}
	node mergenode(node a,node b,int p){node tmp;
		tmp.sum = a.sum + b.sum;
		tmp.lazytag = d[p].lazytag;
		tmp.l=d[p].l;tmp.r=d[p].r;
		return tmp;
	}
	void pushdown(int l,int r,int p){
		int mid = (l + r) >> 1;
		if(d[p].lazytag){
			d[p << 1      ].lazytag += d[p].lazytag;
			d[(p << 1) | 1].lazytag += d[p].lazytag;
			d[p << 1      ].sum += d[p].lazytag * (mid - l + 1);
			d[p << 1      ].sum %= mod;
			d[(p << 1) | 1].sum += d[p].lazytag * (r - mid);
			d[(p << 1) | 1].sum %= mod;
			d[p].lazytag = 0;
		}
		return;
	}
	void update(int l,int r,int s,int t,int p,int change){
		if(l <= s && t <= r){
			d[p].sum += change * (t - s + 1);
			d[p].lazytag += change;
			d[p].sum %= mod;
			return;
		}
		int mid = (s + t) >> 1;
		pushdown(s,t,p);
		if(l <= mid)update(l,r,s,mid,p << 1,change);
		if(mid < r)update(l,r,mid + 1,t,(p << 1) | 1,change);
		d[p] = mergenode(d[p << 1],d[(p << 1) | 1],p);
	}
	int query(int l,int r,int s,int t,int p){
		if(l <= s && t <= r)return d[p].sum;
		int mid = (s + t) >> 1;
		pushdown(s,t,p);
		int res = 0;if(l <= mid) res = query(l,r,s,mid,p << 1) % mod; 
		if(mid < r) res += query(l,r,mid + 1,t,(p << 1) | 1);return res % mod;
	}
	public:
	void DEBUG(){
//		puts("DEBUG");
//		for(int i = 1;i <= n * 4;i++){
//			printf("[ %lld , %lld ]:d[%lld].sum = %lld,d[%lld].laz = %lld\n",d[i].l,d[i].r,i,d[i].sum,i,d[i].lazytag);
//		}
	}
	void update(int x,int y){update(x,y,1,n + 1,1,1);update(y + 1,y + 1,1,n + 1,1,-y + x - 1);}
	int query(int x){return query(1,x,1,n + 1,1) % mod;}
	void build(int n){build(1,n + 1,1);}
}tree;
signed main(){
	n = read(); m = read();
	tree.build(n);
	char ch;int x, y;
	for(int i = 1;i <= m;i++){
		ch = getchar();
		while(ch == ' ' || ch == '\n')ch = getchar();
		if(ch == 'C'){
			x = read(); y = read();
			tree.update(x,y);
		}
		else{
			x = read();
			printf("%lld\n",tree.query(x));
		}
		tree.DEBUG();
	}
	return 0;
}
